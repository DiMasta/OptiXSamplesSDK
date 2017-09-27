#ifndef __CONTEXT_MANAGER_H__
#define __CONTEXT_MANAGER_H__

#include <optix.h>

#include "constants.h"
#include "scene.h"
#include "outputBuffer.h"

class ContextManager {
public:
	ContextManager();
	~ContextManager();

	Scene* getScene() const;
	OutputBuffer* getOutputBuffer() const;
	RTcontext* getContext() const;

	void setScene(Scene* scene);
	void setOutputBuffer(OutputBuffer* outputBuffer);
	void setContext(RTcontext* context);

	void createContext();
private:
	Scene* scene;
	OutputBuffer* outputBuffer;

	RTcontext* context;
};

#endif //__CONTEXT_MANAGER_H__
