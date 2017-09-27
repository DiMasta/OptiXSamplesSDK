#include "outputBuffer.h"

OutputBuffer::OutputBuffer() :
	Buffer()
{

}

//**************************************************************************************************************************
//**************************************************************************************************************************

OutputBuffer::~OutputBuffer() {

}

//**************************************************************************************************************************
//**************************************************************************************************************************

void OutputBuffer::createBuffer(RTcontext* context) {
	RTvariable* variable = getVariable();
	RTbuffer* buffer = getBuffer();

	RT_CHECK_ERROR(rtContextDeclareVariable(*context, "outputBuffer", variable));
	RT_CHECK_ERROR(rtBufferCreate(*context, RT_BUFFER_OUTPUT, buffer));
	RT_CHECK_ERROR(rtBufferSetFormat(*buffer, RT_FORMAT_UNSIGNED_BYTE4));
	RT_CHECK_ERROR(rtBufferSetSize2D(*buffer, BUFFER_WIDTH, BUFFER_HEIGHT));
	RT_CHECK_ERROR(rtVariableSetObject(*variable, *buffer));
}
