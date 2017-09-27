#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <sutil.h>
#include <string>

class Buffer {
public:
	Buffer();
	~Buffer();

	RTbuffer* getBuffer() const;
	RTvariable* getVariable() const;
	std::string getName() const;

	void setBuffer(RTbuffer* buffer);
	void setVariable(RTvariable* variable);
	void setName(std::string name);

	virtual void createBuffer(RTcontext* context) = 0;

private:
	RTbuffer* buffer;
	RTvariable* variable;
	std::string name;
};

#endif // __BUFFER_H__
