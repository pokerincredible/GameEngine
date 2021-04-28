#include "DisplayManager.h"
#include <iostream>

DisplayManager::DisplayManager(int width, int height, const std::string& title)
{
	// ��ʼ�� GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ����һ�����ڶ���
	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	// ��ⴰ����û�д����ɹ�
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
	}
	else
	{
		std::cout << "GLFW window is created successfully" << std::endl;
		glfwMakeContextCurrent(m_window);
		glViewport(0, 0, width, height);
	}
}

DisplayManager::~DisplayManager()
{
	std::cout << "Window destroyed" << std::endl;
	glfwDestroyWindow(m_window);
}

bool DisplayManager::isWindowOpen()
{
	return !glfwWindowShouldClose(m_window);
}

void DisplayManager::updateDisplay()
{
	// �������壬�������¼�
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
