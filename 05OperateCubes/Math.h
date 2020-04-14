#pragma once

#include "glm/gtx/transform.hpp"

class Math
{
public:
	static glm::mat4 createTransformMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
};

glm::mat4 Math::createTransformMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
	// ����һ��ƽ�ƾ���
	glm::mat4 transMatrix = glm::translate(translation);
	// ����һ����ת����
	glm::mat4 rotMatrix =
		glm::rotate(rotation.z, glm::vec3(0, 0, 1)) *
		glm::rotate(rotation.y, glm::vec3(0, 1, 0)) *
		glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	// ����һ�����ž���
	glm::mat4 scaleMatrix = glm::scale(scale);
	return transMatrix * rotMatrix * scaleMatrix;
}