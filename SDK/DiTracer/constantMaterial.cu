#include "raystate.cu"

rtDeclareVariable(float3, constantColor, , );

//**************************************************************************************************************************
//**************************************************************************************************************************

RT_PROGRAM void constantMaterialClosestHit() {
	rayState.result = constantColor;
}