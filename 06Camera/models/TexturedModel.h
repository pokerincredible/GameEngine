#pragma once
#include "glad/glad.h"
#include "RawModel.h"
#include "../textures/Texture.h"

class TexturedModel
{
public:
	TexturedModel(Model model, Texture texture)
		:m_texture(texture), m_model(model){}
	Texture getTexture() const { return m_texture; }
	Model getModel() const { return m_model; }
private:
	Texture m_texture;
	Model m_model;
};