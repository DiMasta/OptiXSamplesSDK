#ifndef __SCENE_H__
#define __SCENE_H__

#include "camera.h"

class Scene {
public:
	Scene();
	~Scene();

	Camera* getCamera() const;

	void setCamera(Camera* camera);

	void setupCameraForRendering(RTcontext* context);

private:
	Camera* camera;
};

#endif //__SCENE_H__