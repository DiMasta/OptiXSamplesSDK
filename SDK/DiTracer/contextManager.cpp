#include "contextManager.h"

using namespace optix;

ContextManager::ContextManager() {
	context = new RTcontext();
	outputBuffer = new OutputBuffer();
	scene = new Scene();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

ContextManager::~ContextManager() {
	if (context) {
		delete context;
		context = NULL;
	}

	if (outputBuffer) {
		delete outputBuffer;
		outputBuffer = NULL;
	}

	if (scene) {
		delete scene;
		scene = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Scene* ContextManager::getScene() const {
	return scene;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

OutputBuffer* ContextManager::getOutputBuffer() const {
	return outputBuffer;
}

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

void ContextManager::setOutputBuffer(OutputBuffer* outputBuffer) {
	this->outputBuffer = outputBuffer;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::setContext(RTcontext* context) {
	this->context = context;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::createContext() {
	RT_CHECK_ERROR(rtContextCreate(context));
	RT_CHECK_ERROR(rtContextSetPrintEnabled(*context, true));
	RT_CHECK_ERROR(rtContextSetPrintBufferSize(*context, PRINT_BUFFER_SIZE));
	RT_CHECK_ERROR(rtContextSetRayTypeCount(*context, 1));
	RT_CHECK_ERROR(rtContextSetEntryPointCount(*context, 1));

	outputBuffer->createBuffer(context);

	scene->setupCameraForRendering(context);
	scene->setupCubeForRendering(context);
	scene->setupConstantMaterialForRendering(context);
	scene->setupEnvironmentForRendering(context);

	// TODO: separate classes for grom groups and instances
	scene->createInstance(context);
}