#include "scene.h"

Scene::Scene() {
	camera = new Camera();
	cube = new Cube();
	constantMaterial = new ConstantMaterial();
	environment = new Environment();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Scene::~Scene() {
	if (camera) {
		delete camera;
		camera = NULL;
	}

	if (cube) {
		delete cube;
		cube = NULL;
	}

	if (constantMaterial) {
		delete constantMaterial;
		constantMaterial = NULL;
	}

	if (environment) {
		delete environment;
		environment = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Camera* Scene::getCamera() const {
	return camera;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Cube* Scene::getCube() const {
	return cube;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

ConstantMaterial* Scene::getConstantMaterial() const {
	return constantMaterial;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Environment* Scene::getEnvironment() const {
	return environment;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::setCamera(Camera* camera) {
	this->camera = camera;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::setCube(Cube* cube) {
	this->cube = cube;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::setConstantMaterial(ConstantMaterial* constantMaterial) {
	this->constantMaterial = constantMaterial;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::setEnvironment(Environment* environment) {
	this->environment = environment;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::setupCameraForRendering(RTcontext* context) {
	camera->setCamEye(DEFAULT_CAEMRA_EYE);
	camera->setLookAt(DEFAULT_CAMERA_LOOK_AT);
	camera->setUpVector(DEFAULT_CAMERA_UP_VECTOR);
	camera->setFov(DEFAULT_CAMERA_FOV);

	camera->computeAspectRatio();

	camera->prepareGPUVariables(context);
	camera->prepareGPUPrograms(context);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::setupCubeForRendering(RTcontext* context) {
	cube->setBottom(CUBE_BOTTOM);
	cube->setTop(CUBE_TOP);

	cube->createGeometry(context);
	cube->prepareGPUVariables(context);
	cube->prepareGPUPrograms(context);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::setupConstantMaterialForRendering(RTcontext* context) {
	constantMaterial->setColor(CONSTANT_MATERIAL_COLOR);

	constantMaterial->createMaterial(context);
	constantMaterial->prepareGPUVariables(context);
	constantMaterial->prepareGPUPrograms(context);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::setupEnvironmentForRendering(RTcontext* context) {
	environment->setBackgroundColor(ENVIRONMENT_COLOR);

	environment->prepareGPUPrograms(context);
	environment->prepareGPUVariables(context);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::createInstance(RTcontext* context) {
	RTgeometrygroup geometrygroup;
	RTvariable topObject;
	RTacceleration acceleration;
	RTgeometryinstance instance;

	RTgeometry* rtGeoemetry = cube->getRTGeometry();
	RTmaterial* rtMaterial = constantMaterial->getRTMaterial();

	/* Create geometry instance */
	RT_CHECK_ERROR(rtGeometryInstanceCreate(*context, &instance));
	RT_CHECK_ERROR(rtGeometryInstanceSetGeometry(instance, *rtGeoemetry));
	RT_CHECK_ERROR(rtGeometryInstanceSetMaterialCount(instance, 1));
	RT_CHECK_ERROR(rtGeometryInstanceSetMaterial(instance, 0, *rtMaterial));

	/* Create acceleration */
	RT_CHECK_ERROR(rtAccelerationCreate(*context, &acceleration));
	RT_CHECK_ERROR(rtAccelerationSetBuilder(acceleration, "NoAccel"));

	/* Create geometry group */
	RT_CHECK_ERROR(rtGeometryGroupCreate(*context, &geometrygroup));
	RT_CHECK_ERROR(rtGeometryGroupSetChildCount(geometrygroup, 1));
	RT_CHECK_ERROR(rtGeometryGroupSetChild(geometrygroup, 0, instance));
	RT_CHECK_ERROR(rtGeometryGroupSetAcceleration(geometrygroup, acceleration));

	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "topObject", &topObject));
	RT_CHECK_ERROR(rtVariableSetObject(topObject, geometrygroup));
}
