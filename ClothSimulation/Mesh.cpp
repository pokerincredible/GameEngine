#include "Mesh.h"
#include <iostream>

Vertex::Vertex() {
	Position = glm::vec3(0, 0, 0);
	Normal = glm::vec3(0, 0, 0);
	TexCoord = glm::vec2(0, 0);
}

void Mesh::initClothMesh(float width, float height, float cols, float rows)
{
	// resize vector size
	m_vertices.resize(cols * rows);
	m_indices.resize(6 * (cols - 1) * (rows - 1));

	float dx = width / (cols - 1);
	float dy = height / (rows - 1);
	float uv_w = 1.0f / (cols - 1);
	float uv_h = 1.0f / (rows - 1);
	glm::vec3 originPos = glm::vec3(-width / 2.0f, height / 2.0f, 0.0f);

	glm::vec3 nor_x = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 nor_y = glm::vec3(0.0f, -1.0f, 0.0f);

	int idx = 0;
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			// positions
			m_vertices[x + y * cols].Position = originPos + nor_x * dx * (float)x + nor_y * dy * (float)y;
			// texCoords
			m_vertices[x + y * cols].TexCoord = glm::vec2(uv_w * x, uv_h * y);
			// indices
			if (x > 0 && y > 0) {
				m_indices[idx++] = x + y * cols;
				m_indices[idx++] = x - 1 + (y - 1) * cols;
				m_indices[idx++] = x + (y - 1) * cols;
				m_indices[idx++] = x - 1 + (y - 1) * cols;
				m_indices[idx++] = x + y * cols;
				m_indices[idx++] = x - 1 + y * cols;
			}
		}
	}
	updateNormals();
}

void Mesh::updateNormals() {
	//for (int i = 0; i < m_vertices.size(); i++)
	//	m_vertices[i].Normal = glm::vec3(0, 0, 0);
	for (size_t i = 0; i < m_indices.size(); i += 3) {
		unsigned int vertId0 = m_indices[i];
		unsigned int vertId1 = m_indices[i + 1];
		unsigned int vertId2 = m_indices[i + 2];
		glm::vec3 pVert0 = m_vertices[vertId0].Position;
		glm::vec3 pVert1 = m_vertices[vertId1].Position;
		glm::vec3 pVert2 = m_vertices[vertId2].Position;
		glm::vec3 e10 = pVert1 - pVert0;
		glm::vec3 e21 = pVert2 - pVert1;
		glm::vec3 e02 = pVert0 - pVert2;

		glm::vec3 faceNormal;
		glm::vec3 v1 = e10;
		glm::vec3 v2 = -e02;
		
		faceNormal[0] = v1[1] * v2[2] - v1[2] * v2[1];
		faceNormal[1] = v1[2] * v2[0] - v1[0] * v2[2];
		faceNormal[2] = v1[0] * v2[1] - v1[1] * v2[0];

		//Eigen::Vector3f faceNormal = e10.cross(-e02);
		faceNormal = glm::normalize(faceNormal);

		m_vertices[vertId0].Normal += faceNormal;
		m_vertices[vertId1].Normal += faceNormal;
		m_vertices[vertId2].Normal += faceNormal;
	}
	for (int i = 0; i < m_vertices.size(); i++)
		m_vertices[i].Normal = glm::normalize(m_vertices[i].Normal);
}