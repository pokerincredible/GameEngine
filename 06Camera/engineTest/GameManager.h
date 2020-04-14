#pragma once
#include "glad/glad.h"
#include "../renders/DisplayManager.h"
class GameManager
{
public:
	GameManager();
	~GameManager();
	void loop();
private:
	DisplayManager* m_displayManager;
};

