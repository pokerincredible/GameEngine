#pragma once
#include "ShaderProgram.h"
class BasicShader :
	public ShaderProgram
{
public:
	BasicShader();
	void loadTransformationMatrix(glm::mat4 transMat);
protected:
	void bindAttributes();
	void getAllUniformLocations();
private:
	int location_transformationMatrix;
};

