#include "BasicShader.h"

BasicShader::BasicShader() : 
	ShaderProgram("res/shaders/vertShader.vert", "res/shaders/fragShader.frag")
{
	bindAttributes();
}

void BasicShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
}
