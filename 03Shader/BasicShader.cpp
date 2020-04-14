#include "BasicShader.h"

BasicShader::BasicShader() : 
	ShaderProgram("res/shader/vertShader.vert", "res/shader/fragShader.frag")
{
	bindAttributes();
}

void BasicShader::bindAttributes()
{
	bindAttribute(0, "position");
}
