#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "sceneElment.h"

class Geometry : public SceneElement {
public:
	Geometry();
	~Geometry();

	RTgeometry* getGeometry() const;

	void setGeoemtry(RTgeometry* geometry);

	virtual void createGeometry(RTcontext* context) = 0;
	virtual void prepareIntersectionProgram(RTcontext* context) = 0;
	virtual void prepareBoundingBoxProgram(RTcontext* context) = 0;

private:
	RTgeometry* geometry;
};

#endif // !__GEOMETRY_H__

