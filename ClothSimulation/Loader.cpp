#include <iostream>
#include "Loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Model Loader::loadToVAO(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	GLuint vaoID = createVAO();
	int indicesSize = indices.size();
	bindIndicesBuffers(indices.data(), indicesSize);
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// 顶点位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// 顶点法线
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// 顶点纹理坐标
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
	unBindVAO();
	return Model(vaoID, indicesSize);
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

void Loader::bindIndicesBuffers(unsigned int* indices, int count)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
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
