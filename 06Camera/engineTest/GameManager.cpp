#include <iostream>
#include "GameManager.h"
#include "../renders/Loader.h"
#include "../renders/Renderer.h"
#include "../shaders/BasicShader.h"
#include "../entities/Entity.h"

GameManager::GameManager()
{
	if (glfwInit())
	{
		std::cout << "GLFW initialized successfully" << std::endl;
		// ����һ�� displayManager
		m_displayManager = new DisplayManager(800, 700, "GameEngine");
		// ��ʼ�� glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD" << std::endl;
		}
		else
		{
			std::cout << "GLAD initialized successfully" << std::endl;
		}
	}
	else
	{
		std::cerr << "ERROR: GLFW failed to initialze" << std::endl;
	}
}

GameManager::~GameManager()
{
	delete m_displayManager;
	glfwTerminate();
}

void GameManager::loop()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,	// left down
		0.5f, -0.5f, 0.0f,	// right down
		-0.5f,  0.5f, 0.0f,	// left top  
		0.5f, 0.5f, 0.0f	// right top
	};
	int indices[] = {
		0, 1, 2,
		2, 3, 1
	};
	float texCoords[] = {
		0,0,
		1,0,
		0,1,
		1,1
	};
	Loader loader;
	std::vector<float> vertices_vec(vertices, vertices + sizeof(vertices) / sizeof(float));
	std::vector<int> indices_vec(indices, indices + sizeof(indices) / sizeof(int));
	std::vector<float> texCoords_vec(texCoords, texCoords + sizeof(texCoords) / sizeof(float));

	Model model = loader.loadToVAO(vertices_vec, indices_vec, texCoords_vec);
	GLuint textureID = loader.loadTexture("pic.png", false);
	Texture texture(textureID);
	TexturedModel texturedModel(model, texture);
	Entity entity(texturedModel, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1.1, 1));

	std::cout << model.getVertexCount() << std::endl;
	std::cout << "Game Loop is running now" << std::endl;
	Renderer render;
	BasicShader shader;
	// ��Ⱦѭ��
	while (m_displayManager->isWindowOpen())
	{
		render.prepare();
		render.Render(entity, shader);	
		// updateDisplay �в��ܼ��� prepare �߼�
		m_displayManager->updateDisplay();
	}
	loader.cleanUp();
}