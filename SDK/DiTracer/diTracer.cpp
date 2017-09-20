#include "contextManager.h"


//**************************************************************************************************************************
//**************************************************************************************************************************

void createEmptyGroup(RTcontext* context) {
	RTgroup group;
	RTvariable topObject;
	RTacceleration acceleration;

	RT_CHECK_ERROR(rtGroupCreate(*context, &group));

	RT_CHECK_ERROR(rtAccelerationCreate(*context, &acceleration));
	RT_CHECK_ERROR(rtAccelerationSetBuilder(acceleration, "NoAccel"));
	RT_CHECK_ERROR(rtGroupSetAcceleration(group, acceleration));

	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "topObject", &topObject));
	RT_CHECK_ERROR(rtVariableSetObject(topObject, group));
}

//**************************************************************************************************************************
//**************************************************************************************************************************

int main (int argc, char* argv[]) {
	ContextManager contextManager;
	contextManager.createContext();
	RTcontext* context = contextManager.getContext();

	try {
		createEmptyGroup(context);

		sutil::initGlut(&argc, argv);

		RT_CHECK_ERROR(rtContextValidate(*context));
		RT_CHECK_ERROR(rtContextLaunch2D(*context, 0, BUFFER_WIDTH, BUFFER_HEIGHT));

		sutil::displayBufferGlut(argv[0], *contextManager.getOutputBufferObj());

		RT_CHECK_ERROR(rtContextDestroy(*context));

		return 0;
	} SUTIL_CATCH(*context)
}