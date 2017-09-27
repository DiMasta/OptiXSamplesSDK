#ifndef __CUBE_CU__
#define __CUBE_CU__

#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>

using namespace optix;

rtDeclareVariable(float3, cubeBottom, , );
rtDeclareVariable(float3, cubeTop, , );
rtDeclareVariable(Ray, ray, rtCurrentRay, );

//**************************************************************************************************************************
//**************************************************************************************************************************

RT_PROGRAM void boundingBoxProgram(int primIdx, float result[6]) {
	Aabb* aabb = (Aabb*)result;

	aabb->set(cubeBottom, cubeTop);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

RT_PROGRAM void intersectionProgram(int primIdx) {
	float3 origin = ray.origin;
	float3 direction = ray.direction;

	float3 t0 = (cubeBottom - origin) / direction;
	float3 t1 = (cubeTop - origin) / direction;

	float3 near = fminf(t0, t1);
	float3 far = fmaxf(t0, t1);

	float tmin = fmaxf(near);
	float tmax = fminf(far);

	if (tmin <= tmax) {
		bool checkSecond = true;

		if (rtPotentialIntersection(tmin)) {
			if (rtReportIntersection(0)) {
				checkSecond = false;
			}
		}

		if (checkSecond) {

			if (rtPotentialIntersection(tmax)) {
				rtReportIntersection(0);
			}
		}
	}
}

#endif // __CUBE_CU__