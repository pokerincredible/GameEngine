#pragma once
#include "glad/glad.h"
#include "DisplayManager.h"
#include <memory>
class GameManager
{
public:
	GameManager();
	~GameManager();
	void loop();
private:
	std::unique_ptr<DisplayManager> m_displayManager;
};

