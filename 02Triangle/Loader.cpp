#include "Loader.h"
#include "glm/vec3.hpp"

Model Loader::loadToVAO(std::vector<float> vertices)
{
	GLuint vaoID = createVAO();
	storeDataInAttributeList(0, 3, &vertices[0], vertices.size() * sizeof(glm::vec3));
	unBindVAO();
	return Model(vaoID, vertices.size());
}

void Loader::cleanUp()
{
	while (m_vbos.size() > 0)
	{
		glDeleteBuffers(1, &m_vbos.back());
		m_vbos.pop_back();
	}
	while (m_vaos.size() > 0)
	{
		glDeleteVertexArrays(1, &m_vaos.back());
		m_vaos.pop_back();
	}
}

GLuint Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	m_vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttributeList(GLuint attribNumber, int attribSize, float* data, int dataSize)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	// 顶点属性index, 属性大小，类型，GL_FALSE, 步长，(void*)0
	glVertexAttribPointer(attribNumber, attribSize, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Loader::unBindVAO()
{
	glBindVertexArray(0);
}
