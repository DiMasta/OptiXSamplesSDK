#ifndef __SCENE_H__
#define __SCENE_H__

#include "camera.h"
#include "cube.h"

class Scene {
public:
	Scene();
	~Scene();

	Camera* getCamera() const;
	Cube* getCube() const;

	void setCamera(Camera* camera);
	void setCube(Cube* cube);

	void setupCameraForRendering(RTcontext* context);
	void setupCubeForRendering(RTcontext* context);

private:
	Camera* camera;
	Cube* cube;
};

#endif //__SCENE_H__