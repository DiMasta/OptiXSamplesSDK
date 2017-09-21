#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "sceneElment.h"

class Camera : public SceneElement {
public:
	Camera();
	~Camera();

	optix::float3 getCamEye() const;
	optix::float3 getLookAt() const;
	optix::float3 getUpVector() const;
	float getFov() const;
	float getAspectRatio() const;

	void setCamEye(optix::float3 camEye);
	void setLookAt(optix::float3 lookAt);
	void setUpVector(optix::float3 upVector);
	void setFov(float fov);
	void setAspectRatio(float aspectRatio);

	void prepareGPUProgram(RTcontext* context) override;
	void prepareGPUVariables(RTcontext* context) override;

	void computeAspectRatio();

private:
	optix::float3 camEye;
	optix::float3 lookAt;
	optix::float3 upVector;
	float fov;
	float aspectRatio;
};

#endif // __CAMERA_H__
