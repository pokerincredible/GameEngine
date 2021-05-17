#pragma once
#include "glad/glad.h"
#include "RawModel.h"
#include "Texture.h"

class TexturedModel
{
public:
	TexturedModel(Mesh model, Texture texture)
		:m_texture(texture), m_model(model){}
	Texture getTexture() const { return m_texture; }
	Mesh getModel() const { return m_model; }
private:
	Texture m_texture;
	Mesh m_model;
};