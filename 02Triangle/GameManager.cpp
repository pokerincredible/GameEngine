#include <iostream>
#include "GameManager.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"

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
	float vertArray[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	};
	Loader loader;
	std::vector<float> vertices(vertArray, vertArray + sizeof(vertArray) / sizeof(float));
	Mesh model = loader.loadToVAO(vertices);
	std::cout << model.getVertexCount() << std::endl;
	std::cout << "Game Loop is running now" << std::endl;
	Renderer render;
	// ��Ⱦѭ��
	while (m_displayManager->isWindowOpen())
	{
		render.prepare();
		render.Render(model);
		// updateDisplay �в��ܼ��� prepare �߼�
		m_displayManager->updateDisplay();
	}
	loader.cleanUp();
}