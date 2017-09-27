#ifndef __OUTPUT_BUFFER_H__
#define __OUTPUT_BUFFER_H__

#include "buffer.h"
#include "constants.h"

class OutputBuffer : public Buffer {
public:
	OutputBuffer();
	~OutputBuffer();

	void createBuffer(RTcontext* context) override; // From Buffer

private:
};

#endif // __OUTPUTBUFFER_H__
