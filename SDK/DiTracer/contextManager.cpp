#include "contextManager.h"

using namespace optix;
using namespace sutil;

ContextManager::ContextManager() :
	glutInitArgs()
{
	initRendering();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

ContextManager::ContextManager(int argc, char** argv) {
	glutInitArgs.argc = argc;
	glutInitArgs.argv = argv;

	initRendering();
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

void ContextManager::initRendering() {
	context = new RTcontext();
	outputBuffer = new OutputBuffer();
	scene = new Scene();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::createContext() {
	RT_CHECK_ERROR(rtContextCreate(context));
	RT_CHECK_ERROR(rtContextSetPrintEnabled(*context, true));
	RT_CHECK_ERROR(rtContextSetPrintBufferSize(*context, PRINT_BUFFER_SIZE));
	RT_CHECK_ERROR(rtContextSetRayTypeCount(*context, 1));
	RT_CHECK_ERROR(rtContextSetEntryPointCount(*context, 1));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::renderBegin() {
	createContext();

	outputBuffer->createBuffer(context);

	scene->setupCameraForRendering(context);
	scene->setupCubeForRendering(context);
	scene->setupConstantMaterialForRendering(context);
	scene->setupEnvironmentForRendering(context);

	scene->createOptiXSceneGraph(context);

	initGlut(&glutInitArgs.argc, glutInitArgs.argv);

	RT_CHECK_ERROR(rtContextValidate(*context));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::renderEnd() {
	RT_CHECK_ERROR(rtContextDestroy(*context));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ContextManager::render() {
	renderBegin();

	RT_CHECK_ERROR(rtContextLaunch2D(*context, 0, BUFFER_WIDTH, BUFFER_HEIGHT));
	displayBufferGlut(glutInitArgs.argv[0], *getOutputBuffer()->getBuffer());

	renderEnd();
}
