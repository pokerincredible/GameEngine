#pragma once
#include <glad/glad.h>

class ProgramInput {
private:
	GLuint handle;		// vertex array object handle
	GLuint vbo[4];		// vertex buffer object handle | position, normal, texture, index
	void bufferData(unsigned int index, void* buffer, size_t size);
public:
	ProgramInput();
	void setPositionData(float* buff, unsigned int len);
	void setNormal
};