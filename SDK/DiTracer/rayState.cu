#ifndef __RAYSTATE_CU__
#define __RAYSTATE_CU__

#include <optix_world.h>

struct RayState {
	float3 result;
};

//**************************************************************************************************************************
//**************************************************************************************************************************

rtDeclareVariable(RayState, rayState, rtPayload, );

#endif // __RAYSTATE_CU__