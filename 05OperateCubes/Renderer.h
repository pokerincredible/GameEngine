#pragma once
#include "Entity.h"
#include "BasicShader.h"
class Renderer
{
public:
	void prepare();
	void Render(Entity entity, BasicShader& shader);
};

