#pragma once
#include "glad/glad.h"
/*
	用来描述模型（模型角度）
	模型关联的 vaoID, 以及模型数据
*/
class Model
{
public:
	Model(GLuint vaoID, int vertexCount);
	GLuint getVaoID() const;
	int getVertexCount() const;
private:

	GLuint m_vaoID;
	int m_vertexCount;
};