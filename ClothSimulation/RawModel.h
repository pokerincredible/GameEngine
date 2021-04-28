#pragma once
#include "glad/glad.h"
/*
	���ģ�͵� VAO
	ģ�͹����� vaoID���Լ�ģ������
	��Ⱦʱֻ��Ҫ VAO ��ż���
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

