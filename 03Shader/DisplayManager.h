#pragma once
#include "GLFW/glfw3.h"
#include <string>
class DisplayManager
{
public:
	DisplayManager(int width, int height, const std::string& title);
	~DisplayManager();
	bool isWindowOpen();
	void updateDisplay();
private:
	GLFWwindow* m_window;
};

