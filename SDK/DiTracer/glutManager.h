#ifndef __GLUT_MANAGER_H__
#define __GLUT_MANAGER_H__

#include "constants.h"

class GLUTManager {
public:
	GLUTManager();
	~GLUTManager();

	void init(int* argc, char** argv);
	void display(const char* windowTitle, RTbuffer* buffer);

private:

};

#endif // __GLUT_MANAGER_H__

