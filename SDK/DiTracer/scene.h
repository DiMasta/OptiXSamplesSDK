#ifndef __SCENE_H__
#define __SCENE_H__

#include "geometryGroup.h"
#include "camera.h"
#include "cube.h"
#include "constantMaterial.h"
#include "environment.h"

class Scene {
public:
	Scene();
	~Scene();

	DiGeometryGroup* getGeometryGroup() const;
	Camera* getCamera() const;
	Cube* getCube() const;
	ConstantMaterial* getConstantMaterial() const;
	Environment* getEnvironment() const;

	void setCamera(Camera* camera);
	void setCube(Cube* cube);
	void setConstantMaterial(ConstantMaterial* constantMaterial);
	void setEnvironment(Environment* environment);
	void setGeoemetryGroup(DiGeometryGroup* geometryGroup);

	void setupCameraForRendering(RTcontext* context);
	void setupCubeForRendering(RTcontext* context);
	void setupConstantMaterialForRendering(RTcontext* context);
	void setupEnvironmentForRendering(RTcontext* context);

	void createInstance(RTcontext* context);
	void createGeometryGroup(RTcontext* context);
	void createGeoemetryInstnaces(RTcontext* context);
	void createTopObject(RTcontext* context);
	void createOptiXSceneGraph(RTcontext* context);

private:
	DiGeometryGroup* geometryGroup;

	Camera* camera;
	Cube* cube;
	ConstantMaterial* constantMaterial;
	Environment* environment;
};

#endif //__SCENE_H__