#include "Model.h"

Model::Model(GLuint vaoID, int vertexCount):
	m_vaoID(vaoID), m_vertexCount(vertexCount)
{
}

GLuint Model::getVaoID() const
{
	return m_vaoID;
}

int Model::getVertexCount() const
{
	return m_vertexCount;
}
