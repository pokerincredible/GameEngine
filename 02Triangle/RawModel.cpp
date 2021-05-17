#include "RawModel.h"

Mesh::Mesh(GLuint vaoID, int vertexCount):
	m_vaoID(vaoID), m_vertexCount(vertexCount)
{
}

GLuint Mesh::getVaoID() const
{
	return m_vaoID;
}

int Mesh::getVertexCount() const
{
	return m_vertexCount;
}
