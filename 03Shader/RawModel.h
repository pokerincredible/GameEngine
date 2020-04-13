#pragma once
#include "glad/glad.h"
/*
	��������ģ�ͣ�ģ�ͽǶȣ�
	ģ�͹����� vaoID, �Լ�ģ������
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