#include "contextManager.h"

using namespace optix;

ContextManager::ContextManager() {
	context = new RTcontext();
	outputBufferObj = new RTbuffer();
	scene = new Scene();
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

	if (scene) {
		delete scene;
		scene = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RTbuffer* ContextManager::getOutputBufferObj() const {
	return outputBufferObj;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Scene* ContextManager::getScene() const {
	return scene;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RTcontext* ContextManager::getContext() const {
	return context;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::setScene(Scene* scene) {
	this->scene = scene;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::setOutputBufferObj(RTbuffer* outputBufferObj) {
	this->outputBufferObj = outputBufferObj;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::setContext(RTcontext* context) {
	this->context = context;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::createContext() {
	RTprogram missProgram;

	RTvariable outputBuffer;
	RTvariable bgColor;

	RT_CHECK_ERROR(rtContextCreate(context));
	RT_CHECK_ERROR(rtContextSetPrintEnabled(*context, true));
	RT_CHECK_ERROR(rtContextSetPrintBufferSize(*context, PRINT_BUFFER_SIZE));
	RT_CHECK_ERROR(rtContextSetRayTypeCount(*context, 1));
	RT_CHECK_ERROR(rtContextSetEntryPointCount(*context, 1));

	// TODO: separate class for the buffer
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "outputBuffer", &outputBuffer));

	RT_CHECK_ERROR(rtBufferCreate(*context, RT_BUFFER_OUTPUT, outputBufferObj));
	RT_CHECK_ERROR(rtBufferSetFormat(*outputBufferObj, RT_FORMAT_UNSIGNED_BYTE4));
	RT_CHECK_ERROR(rtBufferSetSize2D(*outputBufferObj, BUFFER_WIDTH, BUFFER_HEIGHT));
	RT_CHECK_ERROR(rtVariableSetObject(outputBuffer, *outputBufferObj));

	scene->setupCameraForRendering(context);

	// TODO: separate class : Scene element for environment
	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, MISS_PTX, "miss", &missProgram));
	RT_CHECK_ERROR(rtProgramDeclareVariable(missProgram, "bgColor", &bgColor));
	RT_CHECK_ERROR(rtVariableSet3f(bgColor, 1.f, .0f, .0f));
	RT_CHECK_ERROR(rtContextSetMissProgram(*context, 0, missProgram));
}