#pragma once
//#include<glad/glad.h>
//#include<GLFW/glfw3.h>
//#include <glm/glm.hpp>
#include <iostream>

class UniformBlock
{
public:
	unsigned int UBO;
	unsigned int bind_point;
	UniformBlock(unsigned long data_size, unsigned int bind_point);
	~UniformBlock();
	void SetUniformData(unsigned int offset,unsigned long data_size, const void* data)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, data_size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

private:

};

UniformBlock::UniformBlock(unsigned long data_size,unsigned int bind_point)
{
	this->bind_point = bind_point;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, data_size,NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, this->bind_point, UBO, 0, data_size);
}

UniformBlock::~UniformBlock()
{
}
