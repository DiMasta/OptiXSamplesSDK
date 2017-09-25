#include <optix_world.h>

using namespace optix;

rtDeclareVariable(float3, cubeBottom, , );
rtDeclareVariable(float3, cubeTop, , );

//**************************************************************************************************************************
//**************************************************************************************************************************

RT_PROGRAM void boundingBoxProgram(int primIdx, float result[6]) {
	Aabb* aabb = (Aabb*)result;

	aabb->m_min = cubeBottom;
	aabb->m_max = cubeTop;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RT_PROGRAM void intersectionProgram(int primIdx) {

}