#include <iostream>
#include <optix.h>
#include <sutil.h>

using namespace std;

const int BUFFER_WIDTH = 1024;
const int BUFFER_HEIGHT = 768;

//**************************************************************************************************************************
//**************************************************************************************************************************

void createContext(RTcontext* context, RTbuffer* outputBufferObj) {
	RTvariable outputBuffer;

	RT_CHECK_ERROR(rtContextCreate(context));
	RT_CHECK_ERROR(rtContextSetRayTypeCount(*context, 1));
	RT_CHECK_ERROR(rtContextSetEntryPointCount(*context, 1));

	RT_CHECK_ERROR(rtBufferCreate(*context, RT_BUFFER_OUTPUT, outputBufferObj));
	RT_CHECK_ERROR(rtBufferSetFormat(*outputBufferObj, RT_FORMAT_UNSIGNED_BYTE4));
	RT_CHECK_ERROR(rtBufferSetSize2D(*outputBufferObj, BUFFER_WIDTH, BUFFER_HEIGHT));
	RT_CHECK_ERROR(rtVariableSetObject(outputBuffer, *outputBufferObj));


}

//**************************************************************************************************************************
//**************************************************************************************************************************

int main (int argc, char* argv[]) {
	RTcontext context = 0;
	RTbuffer outputBufferObj;

	createContext(&context, &outputBufferObj);

	//sutil::initGlut(&argc, argv);
	//sutil::displayBufferGlut(argv[0], outputBuffer);

	cout << "Hello, world!" << endl;

	return 0;
}