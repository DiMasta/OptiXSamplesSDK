#include <iostream>
#include <optix.h>
#include <sutil.h>

using namespace std;

int main (int argc, char* argv[]) {
	RTcontext context = 0;
	RTbuffer outputBuffer;

	//createContext(&context, &outputBuffer);

	//sutil::initGlut(&argc, argv);
	//sutil::displayBufferGlut(argv[0], outputBuffer);

	cout << "Hello, world!" << endl;

	return 0;
}