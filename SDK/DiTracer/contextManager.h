#ifndef __CONTEXT_MANAGER_H__
#define __CONTEXT_MANAGER_H__

#include <optix.h>
#include <sutil.h>

#include "constants.h"

class ContextManager {
public:
	ContextManager();
	~ContextManager();

	RTcontext* getContext();
	RTbuffer* getOutputBufferObj();
	void createContext();
private:
	RTbuffer* outputBufferObj;

	RTcontext* context;
};

#endif //__CONTEXT_MANAGER_H__
