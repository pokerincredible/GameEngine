#include "GameManager.h"
#include <iostream>
GameManager::GameManager()
{
	if (glfwInit())
	{
		std::cout << "GLFW initialized successfully" << std::endl;
		// ����һ�� displayManager
		m_displayManager = new DisplayManager(1280, 720, "GameEngine");
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
	std::cout << "Game Loop is running now" << std::endl;
	// ��Ⱦѭ��
	while (m_displayManager->isWindowOpen())
	{
		m_displayManager->updateDisplay();
	}
}