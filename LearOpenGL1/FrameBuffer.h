#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>

class FrameBuffer
{
public:
	unsigned int FBO;
	unsigned int Render_Texture;
	unsigned int Width;
	unsigned int Height;
	FrameBuffer(unsigned int width,unsigned int height);
	~FrameBuffer();

private:
	void GenFrameBuffer() 
	{
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glGenTextures(1, &Render_Texture);
		glBindTexture(GL_TEXTURE_2D, Render_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->Width, this->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Render_Texture, 0);

		//renderbuff äÖÈ¾»º³å
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->Width, this->Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR:FRAMEBUFFER:FRAME NOT COMPLETE" << std::endl;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
};

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
	this->Width = width;
	this->Height = height;
	GenFrameBuffer();
}

FrameBuffer::~FrameBuffer()
{
	
}