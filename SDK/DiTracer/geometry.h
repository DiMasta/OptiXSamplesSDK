#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "sceneElment.h"

class Geometry : public SceneElement {
public:
	Geometry();
	~Geometry();

	RTgeometry* getRTGeometry() const;

	void setRTGeoemtry(RTgeometry* geometry);

	virtual void createGeometry(RTcontext* context) = 0;
	virtual void prepareIntersectionProgram(RTcontext* context) = 0;
	virtual void prepareBoundingBoxProgram(RTcontext* context) = 0;

private:
	RTgeometry* geometry;
};

#endif // !__GEOMETRY_H__

