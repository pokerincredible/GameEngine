#pragma once
#include "../entities/Entity.h"
#include "../shaders/BasicShader.h"
class Renderer
{
public:
	void prepare();
	void Render(Entity entity, BasicShader& shader);
};

