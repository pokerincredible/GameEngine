#include "Mesh.h"
#include <iostream>

Vertex::Vertex() {
	Position = glm::vec3(0, 0, 0);
	Normal = glm::vec3(0, 0, 0);
	TexCoord = glm::vec2(0, 0);
}

void Mesh::initClothMesh(float width, float height, float wNum, float hNum)
{
	// resize vector size
	m_vertices.resize((wNum  + 1) * (hNum + 1));
	m_indices.resize(6 * (wNum) * (hNum));

	float d_w = width / wNum; 
	float d_h = height / hNum;
	float uv_w = 1.0f / wNum;
	float uv_h = 1.0f / hNum;
	glm::vec3 originPos = glm::vec3(-width / 2.0f, height / 2.0f, 0.0f);

	glm::vec3 dx = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 dy = glm::vec3(0.0f, -1.0f, 0.0f);

	int idx = 0;
	for (int i = 0; i <= hNum; i++) {
		for (int j = 0; j <= wNum; j++) {
			// positions
			m_vertices[j + i * wNum].Position = originPos + dx * d_w * (float)j + dy * d_h * (float)i;
			// texCoords
			std::cout << j + i * wNum << "  u:" << uv_w * j << " v:" << uv_h * i << " ";
			m_vertices[j + i * wNum].TexCoord = glm::vec2(uv_w * j, uv_h * i);

			if (j > 0 && i > 0) {
				m_indices[idx++] = j + i * (wNum + 1);
				m_indices[idx++] = j - 1 + (i - 1) * (wNum + 1);
				m_indices[idx++] = j + (i - 1) * (wNum + 1);
				m_indices[idx++] = j-1 + (i-1) * (wNum + 1);
				m_indices[idx++] = j + i * (wNum + 1);
				m_indices[idx++] = j - 1 + i * (wNum + 1);
			}
		}
		std::cout << std::endl;
	}
	updateNormals();
}

void Mesh::updateNormals() {
	for (int i = 0; i < m_vertices.size(); i++)
		m_vertices[i].Normal = glm::vec3(0, 0, 0);
	//for (size_t i = 0; i < m_indices.size(); i += 3) {
	//	unsigned int vertId0 = m_indices[i];
	//	unsigned int vertId1 = m_indices[i + 1];
	//	unsigned int vertId2 = m_indices[i + 2];
	//	glm::vec3 pVert0 = m_vertices[vertId0].Position;
	//	glm::vec3 pVert1 = m_vertices[vertId1].Position;
	//	glm::vec3 pVert2 = m_vertices[vertId2].Position;
	//	glm::vec3 e10 = pVert1 - pVert0;
	//	glm::vec3 e21 = pVert2 - pVert1;
	//	glm::vec3 e02 = pVert0 - pVert2;

	//	glm::vec3 faceNormal;
	//	glm::vec3 v1 = e10;
	//	glm::vec3 v2 = -e02;
	//	
	//	faceNormal[0] = v1[1] * v2[2] - v1[2] * v2[1];
	//	faceNormal[1] = v1[2] * v2[0] - v1[0] * v2[2];
	//	faceNormal[2] = v1[0] * v2[1] - v1[1] * v2[0];

	//	//Eigen::Vector3f faceNormal = e10.cross(-e02);
	//	faceNormal = glm::normalize(faceNormal);

	//	m_vertices[vertId0].Normal += faceNormal;
	//	m_vertices[vertId1].Normal += faceNormal;
	//	m_vertices[vertId2].Normal += faceNormal;
	//}
	//for (int i = 0; i < m_vertices.size(); i++)
	//	m_vertices[i].Normal = glm::normalize(m_vertices[i].Normal);
}