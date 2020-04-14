#include "BasicShader.h"

BasicShader::BasicShader() : 
	ShaderProgram("res/shader/vertShader.vert", "res/shader/fragShader.frag")
{
	getAllUniformLocations();
	bindAttributes();
}

void BasicShader::loadTransformationMatrix(glm::mat4 transMat)
{
	loadMatrix(location_transformationMatrix, transMat);
}

void BasicShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "texCoord");
}

void BasicShader::getAllUniformLocations()
{
	location_transformationMatrix = getUniformLocation("transformationMatrix");
}
