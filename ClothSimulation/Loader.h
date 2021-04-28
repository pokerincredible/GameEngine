#pragma once
#include <vector>
#include "glad/glad.h"
#include "RawModel.h"
/*
	�������м��ص����ݣ�vaoIDs, vboIDs
	�����ݰ󶨵� vao, vbo �У������� RawModel
*/

class Loader
{
public:
	RawModel loadToVAO(std::vector<float> vertices, std::vector<int> indices);
	void cleanUp();
private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;

	GLuint createVAO();
	// û�� createVBO ��ԭ���� vbo ���ڶ�������
	void storeDataInAttributeList(GLuint attribNumber, int attribSize, float* data, int dataSize);
	void bindIndicesBuffers(int* indices, int count);
	void unBindVAO();
};

