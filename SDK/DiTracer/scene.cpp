#include "scene.h"

Scene::Scene() {
	geometryGroup = new DiGeometryGroup();
	camera = new Camera();
	cube = new Cube();
	constantMaterial = new ConstantMaterial();
	environment = new Environment();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Scene::~Scene() {
	if (geometryGroup) {
		delete geometryGroup;
		geometryGroup = NULL;
	}

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

DiGeometryGroup * Scene::getGeometryGroup() const {
	return geometryGroup;
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

void Scene::setGeoemetryGroup(DiGeometryGroup* geometryGroup) {
	this->geometryGroup = geometryGroup;
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

void Scene::createGeoemetryInstnaces(RTcontext* context) {
	geometryGroup->addGeometryInstance(cube, constantMaterial);
	geometryGroup->getGeometryInstanceByIdx(0)->create(context);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::createGeometryGroup(RTcontext* context) {
	RTgeometrygroup* rtGeometryGroup = geometryGroup->getGeometryGroup();
	RT_CHECK_ERROR(rtGeometryGroupCreate(*context, rtGeometryGroup));

	int geometryInstancesCount = geometryGroup->getGeometryInstancesCount();
	RT_CHECK_ERROR(rtGeometryGroupSetChildCount(*rtGeometryGroup, geometryInstancesCount));

	for (int geomInstIdx = 0; geomInstIdx < geometryInstancesCount; ++geomInstIdx) {
		DiGeometryInstnace* diGeometryInstnace = geometryGroup->getGeometryInstanceByIdx(geomInstIdx);
		RTgeometryinstance* rtGeometryInstnace = diGeometryInstnace->getRTGeometryInstance();
		RT_CHECK_ERROR(rtGeometryGroupSetChild(*rtGeometryGroup, geomInstIdx, *rtGeometryInstnace));
	}

	RTacceleration acceleration;
	RT_CHECK_ERROR(rtAccelerationCreate(*context, &acceleration));
	RT_CHECK_ERROR(rtAccelerationSetBuilder(acceleration, "NoAccel"));
	RT_CHECK_ERROR(rtGeometryGroupSetAcceleration(*rtGeometryGroup, acceleration));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::createTopObject(RTcontext* context) {
	RTvariable topObject;
	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "topObject", &topObject));

	RTgeometrygroup* rtGeometryGroup = geometryGroup->getGeometryGroup();
	RT_CHECK_ERROR(rtVariableSetObject(topObject, *rtGeometryGroup));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Scene::createOptiXSceneGraph(RTcontext* context) {
	createGeoemetryInstnaces(context);
	createGeometryGroup(context);
	createTopObject(context);
}
