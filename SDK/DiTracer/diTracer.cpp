#include "contextManager.h"

int main (int argc, char* argv[]) {
	ContextManager contextManager;
	contextManager.createContext();
	RTcontext* context = contextManager.getContext();

	try {
		sutil::initGlut(&argc, argv);

		RT_CHECK_ERROR(rtContextValidate(*context));
		RT_CHECK_ERROR(rtContextLaunch2D(*context, 0, BUFFER_WIDTH, BUFFER_HEIGHT));

		sutil::displayBufferGlut(argv[0], *contextManager.getOutputBuffer()->getBuffer());

		RT_CHECK_ERROR(rtContextDestroy(*context));

		return 0;
	} SUTIL_CATCH(*context)
}