#pragma once
#include "glad/glad.h"
/*
	存放模型的 VAO
	模型关联的 vaoID，以及模型数据
	渲染时只需要 VAO 序号即可
*/
class RawModel
{
public:
	RawModel(GLuint vaoID, int vertexCount);
	GLuint getVaoID() const;
	int getVertexCount() const;
private:
	GLuint m_vaoID;
	int m_vertexCount;
};

