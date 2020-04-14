#pragma once
#include <vector>
#include <string>
#include "glad/glad.h"
#include "RawModel.h"
// 描述所有加载的数据：vaoIDs, vboIDs
// 将数据绑定到 vao, vbo 中，并返回 Model
class Loader
{
public:
	Model loadToVAO(std::vector<float> vertices, std::vector<int> indices, std::vector<float> texCoords);
	GLuint loadTexture(const std::string& fileName, bool repeat = false);
	void cleanUp();
private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
	std::vector<GLuint> m_textures;

	GLuint createVAO();
	void storeDataInAttributeList(GLuint attribNumber, int attribSize, float* data, int dataSize);
	void bindIndicesBuffers(int* indices, int count);
	void unBindVAO();
};

