#ifndef __CONSTANT_MATERIAL_H__
#define __CONSTANT_MATERIAL_H__

#include "material.h"

class ConstantMaterial : public Material {
public:
	ConstantMaterial();
	~ConstantMaterial();

	optix::float3 getColor() const;

	void setColor(optix::float3 color);

	void createMaterial(RTcontext* context) override; // From Material
	void prepareClosestHitProgram(RTcontext* context) override; // From Material

	void prepareGPUPrograms(RTcontext* context) override; // From SceneElement
	void prepareGPUVariables(RTcontext* context) override; // From SceneElement

private:
	optix::float3 color;
};

#endif // __CONSTANT_MATERIAL_H__

