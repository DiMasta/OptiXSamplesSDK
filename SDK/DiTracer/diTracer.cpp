#include <iostream>
#include <optix.h>
#include <sutil.h>

using namespace std;

const int BUFFER_WIDTH = 1024;
const int BUFFER_HEIGHT = 768;

//**************************************************************************************************************************
//**************************************************************************************************************************

void createContext(RTcontext* context, RTbuffer* outputBufferObj) {
	RTvariable outputBuffer;
	RTprogram rayGenerationProgram;

	RTvariable eye;
	RTvariable U;
	RTvariable V;
	RTvariable W;

	char pathToPTX[512];

	RT_CHECK_ERROR(rtContextCreate(context));
	RT_CHECK_ERROR(rtContextSetRayTypeCount(*context, 1));
	RT_CHECK_ERROR(rtContextSetEntryPointCount(*context, 1));

	RT_CHECK_ERROR(rtBufferCreate(*context, RT_BUFFER_OUTPUT, outputBufferObj));
	RT_CHECK_ERROR(rtBufferSetFormat(*outputBufferObj, RT_FORMAT_UNSIGNED_BYTE4));
	RT_CHECK_ERROR(rtBufferSetSize2D(*outputBufferObj, BUFFER_WIDTH, BUFFER_HEIGHT));
	RT_CHECK_ERROR(rtVariableSetObject(outputBuffer, *outputBufferObj));

	sprintf(pathToPTX, "%s%s", sutil::samplesDir(), "diTracer_generated_pinholeCamera.cu.ptx");
	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, pathToPTX, "pinholeCamera", &rayGenerationProgram));
	RT_CHECK_ERROR(rtContextSetRayGenerationProgram(*context, 0, rayGenerationProgram));
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "eye", &eye));
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "U", &U));
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "V", &V));
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "W", &W));

	optix::float3 camEye = { .0f, .0f, 5.f };
	optix::float3 lookat = { .0f, .0f, .0f };
	optix::float3 up = { .0f, 1.f, .0f };
	float hfov = 60.f;
	float aspectRatio = (float)BUFFER_WIDTH / (float)BUFFER_HEIGHT;
	optix::float3 cameraU, cameraV, cameraW;

	sutil::calculateCameraVariables(
		camEye, lookat, up, hfov, aspectRatio,
		cameraU, cameraV, cameraW);

	RT_CHECK_ERROR(rtVariableSet3fv(eye, &camEye.x));
	RT_CHECK_ERROR(rtVariableSet3fv(U, &cameraU.x));
	RT_CHECK_ERROR(rtVariableSet3fv(V, &cameraV.x));
	RT_CHECK_ERROR(rtVariableSet3fv(W, &cameraW.x));

	sprintf(pathToPTX, "%s/%s", sutil::samplesPTXDir(), "");
	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, pathToPTX, "miss", &missProgram));
	RT_CHECK_ERROR(rtProgramDeclareVariable(missProgram, "bgColor", &bgColor));
	RT_CHECK_ERROR(rtVariableSet3f(bgColor, 1.f, .0f, .0f));
	RT_CHECK_ERROR(rtContextSetMissProgram(*context, 0, missProgram));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

int main (int argc, char* argv[]) {
	RTcontext context = 0;
	RTbuffer outputBufferObj;

	createContext(&context, &outputBufferObj);

	//sutil::initGlut(&argc, argv);
	//sutil::displayBufferGlut(argv[0], outputBuffer);

	cout << "Hello, world!" << endl;

	return 0;
}