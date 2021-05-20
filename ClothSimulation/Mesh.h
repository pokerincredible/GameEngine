#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
	Vertex();
};

class Mesh
{
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

	// width height : [-1, 1]
	// num : point num in width or height
	void initClothMesh(float width, float height, float wNum, float hNum);
	void updateNormals();
private:
	unsigned int VAO, VBO, EBO;
};

