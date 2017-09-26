#include "raystate.cu"

rtDeclareVariable(float3, constnatColor, , );

//**************************************************************************************************************************
//**************************************************************************************************************************

RT_PROGRAM void constantMaterialClosestHit() {
	rayState.result = constnatColor;
}