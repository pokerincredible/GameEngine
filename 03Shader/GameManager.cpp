#include <iostream>
#include "GameManager.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"
#include "BasicShader.h"

GameManager::GameManager()
{
	if (glfwInit())
	{
		std::cout << "GLFW initialized successfully" << std::endl;
		// ����һ�� displayManager
		m_displayManager.reset(new DisplayManager(1280, 720, "GameEngine"));
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
	Loader loader;
	std::vector<float> vertices_vec(vertices, vertices + sizeof(vertices) / sizeof(float));
	std::vector<int> indices_vec(indices, indices + sizeof(indices) / sizeof(int));
	Mesh model = loader.loadToVAO(vertices_vec, indices_vec);
	std::cout << model.getVertexCount() << std::endl;
	std::cout << "Game Loop is running now" << std::endl;
	Renderer render;
	BasicShader shader;
	// ��Ⱦѭ��
	while (m_displayManager->isWindowOpen())
	{
		render.prepare();
		shader.use();
		render.Render(model);
		shader.unUse();
		// updateDisplay �в��ܼ��� prepare �߼�
		m_displayManager->updateDisplay();
	}
	loader.cleanUp();
}