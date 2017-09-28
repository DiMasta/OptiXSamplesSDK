#include "cube.h"

Cube::Cube() :
	DiGeometry(),
	bottom(),
	top()
{

}

//**************************************************************************************************************************
//**************************************************************************************************************************

Cube::~Cube() {

}

//**************************************************************************************************************************
//**************************************************************************************************************************

optix::float3 Cube::getBottom() const {
	return bottom;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

optix::float3 Cube::getTop() const {
	return top;
}

//**************************************************************************************************************************
//**************************************************************************************************************************


void Cube::setBottom(optix::float3 bottom) {
	this->bottom = bottom;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Cube::setTop(optix::float3 top) {
	this->top = top;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Cube::createGeometry(RTcontext* context) {
	RTgeometry* geometry = getRTGeometry();

	RT_CHECK_ERROR(rtGeometryCreate(*context, geometry));
	RT_CHECK_ERROR(rtGeometrySetPrimitiveCount(*geometry, 1u));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Cube::prepareIntersectionProgram(RTcontext* context) {
	RTprogram intersectionProgram;
	RTgeometry* geometry = getRTGeometry();

	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, CUBE_PTX, "intersectionProgram", &intersectionProgram));
	RT_CHECK_ERROR(rtGeometrySetIntersectionProgram(*geometry, intersectionProgram));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Cube::prepareBoundingBoxProgram(RTcontext* context) {
	RTprogram boundingBoxProgram;
	RTgeometry* geometry = getRTGeometry();

	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, CUBE_PTX, "boundingBoxProgram", &boundingBoxProgram));
	RT_CHECK_ERROR(rtGeometrySetBoundingBoxProgram(*geometry, boundingBoxProgram));
}

//**************************************************************************************************************************
//**************************************************************************************************************************


void Cube::prepareGPUPrograms(RTcontext* context) {
	prepareBoundingBoxProgram(context);
	prepareIntersectionProgram(context);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Cube::prepareGPUVariables(RTcontext* context) {
	RTvariable cubeBottom;
	RTvariable cubeTop;
	RTgeometry* geometry = getRTGeometry();

	RT_CHECK_ERROR(rtGeometryDeclareVariable(*geometry, "cubeBottom", &cubeBottom));
	RT_CHECK_ERROR(rtGeometryDeclareVariable(*geometry, "cubeTop", &cubeTop));

	RT_CHECK_ERROR(rtVariableSet3f(cubeBottom, bottom.x, bottom.y, bottom.z));
	RT_CHECK_ERROR(rtVariableSet3f(cubeTop, top.x, top.y, top.z));
}