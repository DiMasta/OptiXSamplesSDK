#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <sutil.h>

const int BUFFER_WIDTH = 1024;
const int BUFFER_HEIGHT = 768;
const int PRINT_BUFFER_SIZE = 4096;

static const char* PINHOLE_CAMERA_PTX = "D:\\VLADO\\GPU\\OptiX\\DiTraceSolution\\lib\\ptx\\diTracer_generated_pinholeCamera.cu.ptx";
static const char* MISS_PTX = "D:\\VLADO\\GPU\\OptiX\\DiTraceSolution\\lib\\ptx\\diTracer_generated_miss.cu.ptx";
static const char* CUBE_PTX = "D:\\VLADO\\GPU\\OptiX\\DiTraceSolution\\lib\\ptx\\diTracer_generated_cube.cu.ptx";
static const char* CONSTANT_MATERIAL_PTX = "D:\\VLADO\\GPU\\OptiX\\DiTraceSolution\\lib\\ptx\\diTracer_generated_constantMaterial.cu.ptx";

const optix::float3 DEFAULT_CAEMRA_EYE = { .0f, .0f, 5.f };
const optix::float3 DEFAULT_CAMERA_LOOK_AT = { .0f, .0f, .0f };
const optix::float3 DEFAULT_CAMERA_UP_VECTOR = { .0f, 1.f, .0f };
const float DEFAULT_CAMERA_FOV = 60.f;

const optix::float3 CUBE_BOTTOM = { 1.f, -1.f, -1.f };
const optix::float3 CUBE_TOP = { -1.f, 1.f, 1.f };

const optix::float3 CONSTANT_MATERIAL_COLOR = { .0f, 1.f, .0f };

const optix::float3 ENVIRONMENT_COLOR = { 1.f, .0f, .0f };

#endif // __CONSTANTS_H__
