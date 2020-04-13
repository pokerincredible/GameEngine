#pragma once
#include "RawModel.h"
#include "Texture.h"

class TexturedModel
{
public:
	TexturedModel(Model model, Texture texture):
		m_rawModel(model), m_modelTexture(texture)
	{}
	Model getRawModel() const { return m_rawModel; }
	Texture getTexture() const { return m_modelTexture; }
private:
	Model m_rawModel;
	Texture m_modelTexture;
};