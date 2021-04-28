#pragma once
#include "glad/glad.h"
#include "DisplayManager.h"
#include "Mesh.h"
class GameManager
{
public:
	GameManager();
	~GameManager();
	void loop();
	void initCloth();
private:
	DisplayManager* m_displayManager;
	Mesh* m_clothMesh;
};

