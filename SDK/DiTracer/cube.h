#ifndef __CUBE_H__
#define __CUBE_H__

#include "geometry.h"

class Cube : public Geometry {
public:
	Cube();
	~Cube();

	void prepareGPUProgram(RTcontext* context) override;
	void prepareGPUVariables(RTcontext* context) override;
private:
};

#endif //__CUBE_H__
