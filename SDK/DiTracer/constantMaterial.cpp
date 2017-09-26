#include "constantMaterial.h"

ConstantMaterial::ConstantMaterial() :
	Material()
{

}

//**************************************************************************************************************************
//**************************************************************************************************************************

ConstantMaterial::~ConstantMaterial() {
}

//**************************************************************************************************************************
//**************************************************************************************************************************

optix::float3 ConstantMaterial::getColor() const {
	return color;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ConstantMaterial::setColor(optix::float3 color) {
	this->color = color;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ConstantMaterial::createMaterial(RTcontext* context) {
	RTmaterial* material = getRTMaterial();

	RT_CHECK_ERROR(rtMaterialCreate(*context, material));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ConstantMaterial::prepareClosestHitProgram(RTcontext* context) {
	RTprogram closestHitProgram;
	RTmaterial* material = getRTMaterial();

	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, CONSTANT_MATERIAL_PTX, "constantMaterialClosestHit", &closestHitProgram));
	RT_CHECK_ERROR(rtMaterialSetClosestHitProgram(*material, 0, closestHitProgram));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ConstantMaterial::prepareGPUPrograms(RTcontext* context) {
	prepareClosestHitProgram(context);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void ConstantMaterial::prepareGPUVariables(RTcontext* context) {
	RTvariable constantColor;
	RTmaterial* material = getRTMaterial();

	RT_CHECK_ERROR(rtMaterialDeclareVariable(*material, "constantColor", &constantColor));
	RT_CHECK_ERROR(rtVariableSet3f(constantColor, CONSTANT_MATERIAL_COLOR.x, CONSTANT_MATERIAL_COLOR.y, CONSTANT_MATERIAL_COLOR.z));
}
