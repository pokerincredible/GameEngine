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
	// 创建顶点 buffer
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// dataSize 数据所占字节数
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	// 第几个顶点属性, 数据大小，数据类型，GL_FALSE, 一组数据长度， (void*)0
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