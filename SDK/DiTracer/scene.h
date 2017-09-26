#ifndef __SCENE_H__
#define __SCENE_H__

#include "camera.h"
#include "cube.h"
#include "constantMaterial.h"

class Scene {
public:
	Scene();
	~Scene();

	Camera* getCamera() const;
	Cube* getCube() const;
	ConstantMaterial* getConstantMaterial() const;

	void setCamera(Camera* camera);
	void setCube(Cube* cube);
	void setConstantMaterial(ConstantMaterial* constantMaterial);

	void setupCameraForRendering(RTcontext* context);
	void setupCubeForRendering(RTcontext* context);
	void setupConstantMaterialForRendering(RTcontext* context);

	void createInstance(RTcontext* context);

private:
	Camera* camera;
	Cube* cube;
	ConstantMaterial* constantMaterial;
};

#endif //__SCENE_H__