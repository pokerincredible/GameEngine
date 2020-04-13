#include "BasicShader.h"

BasicShader::BasicShader() : 
	ShaderProgram("shaderFiles/vertShader.vert", "shaderFiles/fragShader.frag")
{
	bindAttributes();
}

void BasicShader::bindAttributes()
{
	bindAttribute(0, "position");
}
