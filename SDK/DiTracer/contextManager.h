#ifndef __CONTEXT_MANAGER_H__
#define __CONTEXT_MANAGER_H__

#include <optix.h>

#include "constants.h"
#include "scene.h"
#include "outputBuffer.h"

struct GLUTInitArgs {
	int argc;
	char** argv;
};

class ContextManager {
public:
	ContextManager();
	ContextManager(int argc, char** argv);
	~ContextManager();

	Scene* getScene() const;
	OutputBuffer* getOutputBuffer() const;
	RTcontext* getContext() const;

	void setScene(Scene* scene);
	void setOutputBuffer(OutputBuffer* outputBuffer);
	void setContext(RTcontext* context);

	void initRendering();
	void createContext();
	void renderBegin();
	void renderEnd();
	void render();

private:
	// Cached main function arguments used to init GLUT
	GLUTInitArgs glutInitArgs;

	Scene* scene;
	OutputBuffer* outputBuffer;

	RTcontext* context;
};

#endif //__CONTEXT_MANAGER_H__
