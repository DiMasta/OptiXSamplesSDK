#include "contextManager.h"

using namespace optix;

ContextManager::ContextManager() {
	context = new RTcontext();
	outputBufferObj = new RTbuffer();

}

//**************************************************************************************************************************
//**************************************************************************************************************************

ContextManager::~ContextManager() {
	if (context) {
		delete context;
		context = NULL;
	}

	if (outputBufferObj) {
		delete outputBufferObj;
		outputBufferObj = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RTcontext* ContextManager::getContext() {
	return context;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RTbuffer* ContextManager::getOutputBufferObj() {
	return outputBufferObj;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::createContext() {
	RTprogram rayGenerationProgram;
	RTprogram missProgram;

	RTvariable outputBuffer;
	RTvariable eye;
	RTvariable U;
	RTvariable V;
	RTvariable W;
	RTvariable bgColor;

	RT_CHECK_ERROR(rtContextCreate(context));
	RT_CHECK_ERROR(rtContextSetPrintEnabled(*context, true));
	RT_CHECK_ERROR(rtContextSetPrintBufferSize(*context, PRINT_BUFFER_SIZE));
	RT_CHECK_ERROR(rtContextSetRayTypeCount(*context, 1));
	RT_CHECK_ERROR(rtContextSetEntryPointCount(*context, 1));

	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "outputBuffer", &outputBuffer));

	RT_CHECK_ERROR(rtBufferCreate(*context, RT_BUFFER_OUTPUT, outputBufferObj));
	RT_CHECK_ERROR(rtBufferSetFormat(*outputBufferObj, RT_FORMAT_UNSIGNED_BYTE4));
	RT_CHECK_ERROR(rtBufferSetSize2D(*outputBufferObj, BUFFER_WIDTH, BUFFER_HEIGHT));
	RT_CHECK_ERROR(rtVariableSetObject(outputBuffer, *outputBufferObj));

	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, PINHOLE_CAMERA_PTX, "pinholeCamera", &rayGenerationProgram));
	RT_CHECK_ERROR(rtContextSetRayGenerationProgram(*context, 0, rayGenerationProgram));
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "eye", &eye));
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "U", &U));
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "V", &V));
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "W", &W));

	float3 camEye = { .0f, .0f, 5.f };
	float3 lookat = { .0f, .0f, .0f };
	float3 up = { .0f, 1.f, .0f };
	float hfov = 60.f;
	float aspectRatio = (float)BUFFER_WIDTH / (float)BUFFER_HEIGHT;
	float3 cameraU, cameraV, cameraW;

	sutil::calculateCameraVariables(
		camEye, lookat, up, hfov, aspectRatio,
		cameraU, cameraV, cameraW);

	RT_CHECK_ERROR(rtVariableSet3fv(eye, &camEye.x));
	RT_CHECK_ERROR(rtVariableSet3fv(U, &cameraU.x));
	RT_CHECK_ERROR(rtVariableSet3fv(V, &cameraV.x));
	RT_CHECK_ERROR(rtVariableSet3fv(W, &cameraW.x));

	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, MISS_PTX, "miss", &missProgram));
	RT_CHECK_ERROR(rtProgramDeclareVariable(missProgram, "bgColor", &bgColor));
	RT_CHECK_ERROR(rtVariableSet3f(bgColor, 1.f, .0f, .0f));
	RT_CHECK_ERROR(rtContextSetMissProgram(*context, 0, missProgram));
}