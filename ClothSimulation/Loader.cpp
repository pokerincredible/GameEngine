#include "Loader.h"

GLuint Loader::createVAO() {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	m_vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

RawModel Loader::loadToVAO(std::vector<float> vertices, std::vector<int> indices){
	GLuint vaoID = createVAO();
	int indicesSize = indices.size();
	bindIndicesBuffers(indices.data(), indicesSize);
	storeDataInAttributeList(0, 3, &vertices[0], vertices.size() * sizeof(float));
	unBindVAO();
	return RawModel(vaoID, indices.size());
}

void Loader::cleanUp(){
	while (m_vbos.size() > 0) {
		glDeleteBuffers(1, &m_vbos.back());
		m_vbos.pop_back();
	}
	while (m_vaos.size() > 0) {
		glDeleteVertexArrays(1, &m_vaos.back());
		m_vaos.pop_back();
	}
}

void Loader::storeDataInAttributeList(GLuint attribNumber, int attribSize, float* data, int dataSize) {
	// �������� buffer
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// dataSize ������ռ�ֽ���
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	// �ڼ�����������, ���ݴ�С���������ͣ�GL_FALSE, һ�����ݳ��ȣ� (void*)0
	glVertexAttribPointer(attribNumber, attribSize, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Loader::bindIndicesBuffers(int* indices, int count) {
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}

void Loader::unBindVAO() {
	glBindVertexArray(0);
}