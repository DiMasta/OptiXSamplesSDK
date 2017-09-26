#include "environment.h"

Environment::Environment() :
	SceneElement()
{
	missProgram = new RTprogram();
}

//**************************************************************************************************************************
//**************************************************************************************************************************

Environment::~Environment() {
	if (missProgram) {
		delete missProgram;
		missProgram = NULL;
	}
}

//**************************************************************************************************************************
//**************************************************************************************************************************

optix::float3 Environment::getBackgroundColor() const {
	return backgroundColor;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Environment::setBackgroundColor(optix::float3 backgroundColor) {
	this->backgroundColor = backgroundColor;
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Environment::prepareGPUPrograms(RTcontext* context) {
	prepareMissProgram(context);
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Environment::prepareGPUVariables(RTcontext* context) {
	RTvariable bgColor;

	RT_CHECK_ERROR(rtProgramDeclareVariable(*missProgram, "bgColor", &bgColor));
	RT_CHECK_ERROR(rtVariableSet3f(bgColor, backgroundColor.x, backgroundColor.y, backgroundColor.z));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

void Environment::prepareMissProgram(RTcontext * context) {
	RT_CHECK_ERROR(rtProgramCreateFromPTXFile(*context, MISS_PTX, "miss", missProgram));
	RT_CHECK_ERROR(rtContextSetMissProgram(*context, 0, *missProgram));
}
