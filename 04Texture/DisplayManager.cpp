#include "DisplayManager.h"
#include <iostream>

DisplayManager::DisplayManager(int width, int height, const std::string& title)
{
	// 初始化 GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 创建一个窗口对象
	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	// 检测窗口有没有创建成功
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
	// 交换缓冲，检测调用事件
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
