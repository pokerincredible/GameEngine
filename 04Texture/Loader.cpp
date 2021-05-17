#include <iostream>
#include "Loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Mesh Loader::loadToVAO(std::vector<float> vertices, std::vector<int> indices, std::vector<float> texCoords)
{
	GLuint vaoID = createVAO();
	int indicesSize = indices.size();
	bindIndicesBuffers(indices.data(), indicesSize);
	storeDataInAttributeList(0, 3, &vertices[0], vertices.size() * sizeof(float));
	storeDataInAttributeList(1, 2, texCoords.data(), texCoords.size() * sizeof(float));
	unBindVAO();
	return Mesh(vaoID, vertices.size());
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
	while (m_textures.size() > 0)
	{
		glDeleteTextures(1, &m_textures.back());
		m_textures.pop_back();
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
	// 链接顶点属性，手动指定输入数据的哪一部分对应顶点着色器的哪个顶点属性
	// 1:shader中的layout(location) 2:顶点属性大小 5:步长，0时OpenGL自己决定 6:偏移量
	glVertexAttribPointer(attribNumber, attribSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Loader::bindIndicesBuffers(int* indices, int count)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}

GLuint Loader::loadTexture(const std::string& fileName, bool repeat)
{
	GLuint textureID;
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(("res/texture/" + fileName).c_str(), &width, &height, &numComponents, 0);
	std::cout << "width: " << width << " height: " << height << " components: " << numComponents << std::endl;
	if (imageData == NULL)
	{
		std::cerr << "ERROR: texture loading failed for " << fileName << std::endl;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	if (!repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	m_textures.push_back(textureID);
	stbi_image_free(imageData);
	return textureID;
}



void Loader::unBindVAO()
{
	glBindVertexArray(0);
}
