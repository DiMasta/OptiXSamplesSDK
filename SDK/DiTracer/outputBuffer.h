#ifndef __OUTPUT_BUFFER_H__
#define __OUTPUT_BUFFER_H__

#include "buffer.h"
#include "constants.h"

class OutputBuffer : public DiBuffer {
public:
	OutputBuffer();
	~OutputBuffer();

	void createBuffer(RTcontext* context) override; // From DiBuffer

private:
};

#endif // __OUTPUTBUFFER_H__
