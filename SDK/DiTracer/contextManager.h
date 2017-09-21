#ifndef __CONTEXT_MANAGER_H__
#define __CONTEXT_MANAGER_H__

#include <optix.h>

#include "constants.h"
#include "scene.h"

class ContextManager {
public:
	ContextManager();
	~ContextManager();

	Scene* getScene() const;
	RTbuffer* getOutputBufferObj() const;
	RTcontext* getContext() const;

	void setScene(Scene* scene);
	void setOutputBufferObj(RTbuffer* outputBufferObj);
	void setContext(RTcontext* context);

	void createContext();
private:
	Scene* scene;
	RTbuffer* outputBufferObj;

	RTcontext* context;
};

#endif //__CONTEXT_MANAGER_H__
