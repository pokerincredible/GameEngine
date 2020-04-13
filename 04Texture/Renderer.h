#pragma once
#include "RawModel.h"
#include "TexturedModel.h"
class Renderer
{
public:
	void prepare();
	void Render(TexturedModel texturedModel);
};

