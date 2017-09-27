#ifndef __PINHOLE_CAMERA_CU__
#define __PINHOLE_CAMERA_CU__

#include <optix_world.h>
#include "helpers.h"

using namespace optix;

struct RayState {
	float3 result;
};

//**************************************************************************************************************************
//**************************************************************************************************************************

rtDeclareVariable(float3, eye, , );
rtDeclareVariable(float3, U, , );
rtDeclareVariable(float3, V, , );
rtDeclareVariable(float3, W, , );
rtDeclareVariable(rtObject, topObject, , );
rtBuffer<uchar4, 2> outputBuffer;

rtDeclareVariable(uint2, launchIndex, rtLaunchIndex, );
rtDeclareVariable(uint2, launchDim, rtLaunchDim, );

//**************************************************************************************************************************
//**************************************************************************************************************************

RT_PROGRAM void pinholeCamera() {
	float2 d = make_float2(launchIndex) / make_float2(launchDim) * 2.f - 1.f;
	float3 rayOrigin = eye;
	float3 rayDirection = normalize(d.x * U + d.y * V + W);

	optix::Ray ray = optix::make_Ray(rayOrigin, rayDirection, 0u, 1.e-4f, RT_DEFAULT_MAX);

	RayState rayState;
	rtTrace(topObject, ray, rayState);

	outputBuffer[launchIndex] = make_color(rayState.result);
}

#endif // __PINHOLE_CAMERA_CU__