#ifndef __SCENE_H__
#define __SCENE_H__

#include "camera.h"
#include "cube.h"
#include "constantMaterial.h"
#include "environment.h"

class Scene {
public:
	Scene();
	~Scene();

	Camera* getCamera() const;
	Cube* getCube() const;
	ConstantMaterial* getConstantMaterial() const;
	Environment* getEnvironment() const;

	void setCamera(Camera* camera);
	void setCube(Cube* cube);
	void setConstantMaterial(ConstantMaterial* constantMaterial);
	void setEnvironment(Environment* environment);

	void setupCameraForRendering(RTcontext* context);
	void setupCubeForRendering(RTcontext* context);
	void setupConstantMaterialForRendering(RTcontext* context);
	void setupEnvironmentForRendering(RTcontext* context);

	void createInstance(RTcontext* context);

private:
	Camera* camera;
	Cube* cube;
	ConstantMaterial* constantMaterial;
	Environment* environment;
};

#endif //__SCENE_H__