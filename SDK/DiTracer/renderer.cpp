#include "renderer.h"

using namespace optix;
using namespace sutil;

Renderer::Renderer() :
	glutInitArgs()
{
	initRendering();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Renderer::Renderer(int argc, char** argv) {
	glutInitArgs.argc = argc;
	glutInitArgs.argv = argv;

	initRendering();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Renderer::~Renderer() {
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

	if (glutManager) {
		delete glutManager;
		glutManager = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Scene* Renderer::getScene() const {
	return scene;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

OutputBuffer* Renderer::getOutputBuffer() const {
	return outputBuffer;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RTcontext* Renderer::getContext() const {
	return context;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::setScene(Scene* scene) {
	this->scene = scene;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::setOutputBuffer(OutputBuffer* outputBuffer) {
	this->outputBuffer = outputBuffer;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::setContext(RTcontext* context) {
	this->context = context;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::initRendering() {
	context = new RTcontext();
	outputBuffer = new OutputBuffer();
	scene = new Scene();
	glutManager = new GLUTManager();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::createContext() {
	RT_CHECK_ERROR(rtContextCreate(context));
	RT_CHECK_ERROR(rtContextSetPrintEnabled(*context, true));
	RT_CHECK_ERROR(rtContextSetPrintBufferSize(*context, PRINT_BUFFER_SIZE));
	RT_CHECK_ERROR(rtContextSetRayTypeCount(*context, 1));
	RT_CHECK_ERROR(rtContextSetEntryPointCount(*context, 1));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::renderBegin() {
	createContext();

	outputBuffer->createBuffer(context);

	setupSceneForRendering();

	glutManager->init(&glutInitArgs.argc, glutInitArgs.argv);

	RT_CHECK_ERROR(rtContextValidate(*context));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::renderEnd() {
	RT_CHECK_ERROR(rtContextDestroy(*context));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::render() {
	renderBegin();

	RT_CHECK_ERROR(rtContextLaunch2D(*context, 0, BUFFER_WIDTH, BUFFER_HEIGHT));

	glutManager->display(WINDOW_TITLE, outputBuffer->getBuffer());

	renderEnd();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Renderer::setupSceneForRendering() {
	scene->setupCameraForRendering(context);
	scene->setupCubeForRendering(context);
	scene->setupConstantMaterialForRendering(context);
	scene->setupEnvironmentForRendering(context);

	scene->createOptiXSceneGraph(context);
}
