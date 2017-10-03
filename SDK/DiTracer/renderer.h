#ifndef __CONTEXT_MANAGER_H__
#define __CONTEXT_MANAGER_H__

#include <optix.h>

#include "scene.h"
#include "outputBuffer.h"
#include "glutManager.h"

struct GLUTInitArgs {
	int argc;
	char** argv;
};

class Renderer {
public:
	Renderer();
	Renderer(int argc, char** argv);
	~Renderer();

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
	void setupSceneForRendering();

private:
	// Cached main function arguments used to init GLUT
	GLUTInitArgs glutInitArgs;

	Scene* scene;
	OutputBuffer* outputBuffer;
	GLUTManager* glutManager;

	RTcontext* context;
};

#endif //__CONTEXT_MANAGER_H__
