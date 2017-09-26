#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "sceneElment.h"

class Environment : public SceneElement {
public:
	Environment();
	~Environment();

	optix::float3 getBackgroundColor() const;

	void setBackgroundColor(optix::float3 backgroundColor);

	void prepareGPUPrograms(RTcontext* context) override; // From SceneElement
	void prepareGPUVariables(RTcontext* context) override; // From SceneElement

	void prepareMissProgram(RTcontext* context);

private:
	RTprogram* missProgram;

	optix::float3 backgroundColor;
};

#endif // __ENVIRONMENT_H__

