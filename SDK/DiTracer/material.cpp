#include "material.h"

DiMaterial::DiMaterial() :
	SceneElement()
{
	material = new RTmaterial();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

DiMaterial::~DiMaterial() {
	if (material) {
		delete material;
		material = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************


RTmaterial* DiMaterial::getRTMaterial() const {
	return material;
}

//**************************************************************************************************************************
//**************************************************************************************************************************


void DiMaterial::setRTMaterial(RTmaterial* material) {
	this->material = material;
}
