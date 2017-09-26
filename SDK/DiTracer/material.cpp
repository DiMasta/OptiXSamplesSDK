#include "material.h"

Material::Material() :
	SceneElement()
{
	material = new RTmaterial();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Material::~Material() {
	if (material) {
		delete material;
		material = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************


RTmaterial* Material::getRTMaterial() const {
	return material;
}

//**************************************************************************************************************************
//**************************************************************************************************************************


void Material::setRTMaterial(RTmaterial* material) {
	this->material = material;
}