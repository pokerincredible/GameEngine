#pragma once
#include "glm/glm.hpp"
#include "../models/TexturedModel.h"

class Entity
{
public:
	Entity(TexturedModel& texturedmodel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		:m_texturedModel(texturedmodel), m_position(position), m_rotation(rotation), m_scale(scale)
	{}
	void changePosition(glm::vec3 position) { m_position = position; }
	void changeRotation(glm::vec3 rotation) { m_rotation = rotation; }
	void changeScale(glm::vec3 scale) { m_scale = scale; }

	TexturedModel getTexturedModel() const { return m_texturedModel; }
	glm::vec3 getPosition() const { return m_position; }
	glm::vec3 getRotation() const { return m_rotation; }
	glm::vec3 getScale() const { return m_scale; }

	void setTexturedModel(TexturedModel texturedModel) { m_texturedModel = texturedModel; }
	void setPosition(glm::vec3 position) { m_position = position; }
	void setRotation(glm::vec3 rotation) { m_rotation = rotation; }
	void setScale(glm::vec3 scale) { m_scale = scale; }
private:
	TexturedModel m_texturedModel;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};