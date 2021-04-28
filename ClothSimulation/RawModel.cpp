#include "RawModel.h"

RawModel::RawModel(GLuint vaoID, int vertexCount):
	m_vaoID(vaoID), m_vertexCount(vertexCount){ }

GLuint RawModel::getVaoID() const
{
	return m_vaoID;
}

int RawModel::getVertexCount() const
{
	return m_vertexCount;
}
