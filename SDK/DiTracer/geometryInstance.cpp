#include "geometryInstance.h"

DiGeometryInstnace::DiGeometryInstnace() :
	materials(),
	geometry(NULL)
{
	rtGeometryInstance = new RTgeometryinstance();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

DiGeometryInstnace::~DiGeometryInstnace() {
	if (rtGeometryInstance) {
		delete rtGeometryInstance;
		rtGeometryInstance = NULL;
	}

	// Geometry and Materials memory is freed in the Scene class

	materials.clear();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

DiGeometry* DiGeometryInstnace::getGeometry() const {
	return geometry;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

MaterialsList DiGeometryInstnace::getMaterials() const {
	return materials;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RTgeometryinstance* DiGeometryInstnace::getRTGeometryInstance() const {
	return rtGeometryInstance;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void DiGeometryInstnace::setGeometry(DiGeometry* geometry) {
	this->geometry = geometry;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void DiGeometryInstnace::setMaterials(MaterialsList materials) {
	this->materials = materials;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void DiGeometryInstnace::setRTGeoemetryInstance(RTgeometryinstance* rtGeometryInstance) {
	this->rtGeometryInstance = rtGeometryInstance;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void DiGeometryInstnace::create(RTcontext* context) {
	RTgeometry* rtGeometry = geometry->getRTGeometry();
	RTmaterial* rtMaterial = materials[0]->getRTMaterial();

	RT_CHECK_ERROR(rtGeometryInstanceCreate(*context, rtGeometryInstance));
	RT_CHECK_ERROR(rtGeometryInstanceSetGeometry(*rtGeometryInstance, *rtGeometry));
	RT_CHECK_ERROR(rtGeometryInstanceSetMaterialCount(*rtGeometryInstance, 1));
	RT_CHECK_ERROR(rtGeometryInstanceSetMaterial(*rtGeometryInstance, 0, *rtMaterial));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void DiGeometryInstnace::addMaterial(DiMaterial* material) {
	materials.push_back(material);
}
