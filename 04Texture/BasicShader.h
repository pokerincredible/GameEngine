#pragma once
#include "ShaderProgram.h"
class BasicShader :
	public ShaderProgram
{
public:
	BasicShader();
protected:
	void bindAttributes();
};

