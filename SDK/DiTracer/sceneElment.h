#ifndef __SCENE_ELEMENT_H__
#define __SCENE_ELEMENT_H__

#include <optix.h>

#include "constants.h"

class SceneElement {
public:
	SceneElement();
	~SceneElement();

	virtual void prepareGPUProgram(RTcontext* context) = 0;
	virtual void prepareGPUVariables(RTcontext* context) = 0;
private:
};

#endif //__SCENE_ELEMENT_H__