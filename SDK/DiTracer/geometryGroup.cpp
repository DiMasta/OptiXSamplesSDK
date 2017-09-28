#include "geometryGroup.h"

DiGeometryGroup::DiGeometryGroup() :
	geometryInstancesList()
{
	geometryGroup = new RTgeometrygroup();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

DiGeometryGroup::~DiGeometryGroup() {
	for (size_t geomInstIdx = 0; geomInstIdx < geometryInstancesList.size(); ++geomInstIdx) {
		if (geometryInstancesList[geomInstIdx]) {
			delete geometryInstancesList[geomInstIdx];
			geometryInstancesList[geomInstIdx] = NULL;
		}
	}

	geometryInstancesList.clear();

	if (geometryGroup) {
		delete geometryGroup;
		geometryGroup  = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************

GeometryInstancesList DiGeometryGroup::getGeometryInstancesList() const {
	return geometryInstancesList;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RTgeometrygroup* DiGeometryGroup::getGeometryGroup() const {
	return geometryGroup;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void DiGeometryGroup::setGeometryInstancesList(GeometryInstancesList geometryInstancesList) {
	this->geometryInstancesList = geometryInstancesList;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void DiGeometryGroup::setGeometryGroup(RTgeometrygroup* geometryGroup) {
	this->geometryGroup = geometryGroup;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void DiGeometryGroup::addGeometryInstance(DiGeometry* geometry, DiMaterial* material) {
	DiGeometryInstnace* geometryInstance = new DiGeometryInstnace();

	geometryInstance->setGeometry(geometry);
	geometryInstance->addMaterial(material);

	geometryInstancesList.push_back(geometryInstance);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

int DiGeometryGroup::getGeometryInstancesCount() const {
	return (int)geometryInstancesList.size();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

DiGeometryInstnace* DiGeometryGroup::getGeometryInstanceByIdx(int idx) const {
	return geometryInstancesList[idx];
}
