#include <iostream>
#include "GameManager.h"
#include "Loader.h"
#include "Renderer.h"
#include "BasicShader.h"
#include "TexturedModel.h"

GameManager::GameManager()
{
	if (glfwInit())
	{
		std::cout << "GLFW initialized successfully" << std::endl;
		// create a displayManager
		m_displayManager = new DisplayManager(800, 720, "simulation");
		// init glad
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
	Mesh clothMesh;
	clothMesh.initClothMesh(1.6, 1.6, 10, 6);

	Loader loader;
	Model model = loader.loadToVAO(clothMesh.m_vertices, clothMesh.m_indices);
	GLuint textureID = loader.loadTexture("pic.png", false);
	Texture texture(textureID);
	TexturedModel texturedModel(model, texture);

	std::cout << model.getVertexCount() << std::endl;
	std::cout << "Game Loop is running now" << std::endl;
	Renderer render;
	BasicShader shader;
	
	// render loop
	while (m_displayManager->isWindowOpen())
	{
		render.prepare();
		shader.use();
		render.Render(texturedModel);
		shader.unUse();
		m_displayManager->updateDisplay();
	}
	loader.cleanUp();
}