#pragma once
#include "glad/glad.h"

class Texture
{
public:
	Texture(GLuint texture) :
		m_textureID(texture){}
	GLuint getID() const { return m_textureID; }
private:
	GLuint m_textureID;
};