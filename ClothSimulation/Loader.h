#pragma once
#include <vector>
#include "glad/glad.h"
#include "RawModel.h"
/*
	描述所有加载的数据：vaoIDs, vboIDs
	将数据绑定到 vao, vbo 中，并返回 RawModel
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
	// 没有 createVBO 的原因是 vbo 存在多种类型
	void storeDataInAttributeList(GLuint attribNumber, int attribSize, float* data, int dataSize);
	void bindIndicesBuffers(int* indices, int count);
	void unBindVAO();
};

