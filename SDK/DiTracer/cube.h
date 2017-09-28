#ifndef __CUBE_H__
#define __CUBE_H__

#include "geometry.h"

class Cube : public DiGeometry {
public:
	Cube();
	~Cube();

	optix::float3 getBottom() const;
	optix::float3 getTop() const;

	void setBottom(optix::float3 bottom);
	void setTop(optix::float3 top);

	void createGeometry(RTcontext* context) override; // From Geometry
	void prepareIntersectionProgram(RTcontext* context) override; // From Geometry
	void prepareBoundingBoxProgram(RTcontext* context) override; // From Geometry

	void prepareGPUPrograms(RTcontext* context) override; // From SceneElement
	void prepareGPUVariables(RTcontext* context) override; // From SceneElement

private:
	optix::float3 bottom;
	optix::float3 top;
};

#endif //__CUBE_H__
