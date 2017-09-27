#ifndef __CONSTANT_MATERIAL_CU__
#define __CONSTANT_MATERIAL_CU__

#include "raystate.cu"

rtDeclareVariable(float3, constantColor, , );

//**************************************************************************************************************************
//**************************************************************************************************************************

RT_PROGRAM void constantMaterialClosestHit() {
	rayState.result = constantColor;
}

#endif // __CONSTANT_MATERIAL_CU__