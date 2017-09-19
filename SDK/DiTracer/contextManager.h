#ifndef __CONTEXT_MANAGER_H__
#define __CONTEXT_MANAGER_H__

#include <optix.h>
#include <sutil.h>

#include "constants.h"

class ContextManager {
public:
	ContextManager();

	RTcontext* getContextPointer();
	RTbuffer* getOutputBufferObjPtr();
	void createContext();
private:
	RTbuffer outputBufferObj;

	RTcontext context;
};

#endif //__CONTEXT_MANAGER_H__
