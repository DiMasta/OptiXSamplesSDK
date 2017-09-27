#include "geometryInstance.h"

GeoemetryInstnace::GeoemetryInstnace() {

}

//**************************************************************************************************************************
//**************************************************************************************************************************

GeoemetryInstnace::~GeoemetryInstnace() {

}

//**************************************************************************************************************************
//**************************************************************************************************************************

Geometry* GeoemetryInstnace::getGeoemetry() const {
	return geometry;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

MaterialsList GeoemetryInstnace::getMaterials() const {
	return materials;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RTgeometryinstance* GeoemetryInstnace::getRTGeometryInstance() const {
	return rtGeometryInstance;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void GeoemetryInstnace::setGeometry(Geometry* geometry) {
	this->geometry = geometry;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void GeoemetryInstnace::setMaterials(MaterialsList materials) {
	this->materials = materials;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void GeoemetryInstnace::setRTGeoemetryInstance(RTgeometryinstance* rtGeometryInstance) {
	this->rtGeometryInstance = rtGeometryInstance;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void GeoemetryInstnace::create(RTcontext* context) {
	RTgeometry* rtGeometry = geometry->getRTGeometry();
	RTmaterial* rtMaterial = materials[0]->getRTMaterial();

	RT_CHECK_ERROR(rtGeometryInstanceCreate(*context, rtGeometryInstance));
	RT_CHECK_ERROR(rtGeometryInstanceSetGeometry(*rtGeometryInstance, *rtGeometry));
	RT_CHECK_ERROR(rtGeometryInstanceSetMaterialCount(*rtGeometryInstance, 1));
	RT_CHECK_ERROR(rtGeometryInstanceSetMaterial(*rtGeometryInstance, 0, *rtMaterial));
}
