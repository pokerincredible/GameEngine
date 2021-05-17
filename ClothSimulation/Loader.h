#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "glad/glad.h"
#include "RawModel.h"
#include "Mesh.h"
// 描述所有加载的数据：vaoIDs, vboIDs
// 将数据绑定到 vao, vbo 中，并返回 Model
class Loader
{
public:
	Model loadToVAO(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	GLuint loadTexture(const std::string& fileName, bool repeat = false);
	void cleanUp();
private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
	std::vector<GLuint> m_textures;

	GLuint createVAO();
	void storeDataInAttributeList(GLuint attribNumber, int attribSize, float* data, int dataSize);
	void bindIndicesBuffers(unsigned int* indices, int count);
	void unBindVAO();
};

