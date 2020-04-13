#pragma once

#include "glad/glad.h"

class Texture
{
public:
	Texture(){}
	Texture(GLuint textureID): m_textureID(textureID){}
	GLuint getID() const { return m_textureID; }
private:
	GLuint m_textureID;
};