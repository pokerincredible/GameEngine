#pragma once
#include <vector>
#include "glad/glad.h"
#include "RawModel.h"
// 描述所有加载的数据：vaoIDs, vboIDs
// 将数据绑定到 vao, vbo 中，并返回 Model
class Loader
{
public:
	Mesh loadToVAO(std::vector<float> vertices, std::vector<int> indices);
	void cleanUp();
private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;

	GLuint createVAO();
	void storeDataInAttributeList(GLuint attribNumber, int attribSize, float* data, int dataSize);
	void bindIndicesBuffers(int* indices, int count);
	void unBindVAO();
};

