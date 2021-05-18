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
		// 创建一个 displayManager
		m_displayManager = new DisplayManager(800, 720, "simulation");
		// 初始化 glad
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
	clothMesh.initClothMesh(2, 2, 2, 2);

	for (int i = 0; i < clothMesh.m_vertices.size(); i++) {
		//std::cout << clothMesh.m_vertices[i].Position[0] << " " << clothMesh.m_vertices[i].Position[1] << " " << clothMesh.m_vertices[i].Position[2] << std::endl;
		//std::cout << clothMesh.m_vertices[i].Normal[0] << " " << clothMesh.m_vertices[i].Normal[1] << " " << clothMesh.m_vertices[i].Normal[2] << std::endl;
		std::cout << clothMesh.m_vertices[i].TexCoord[0] << " " << clothMesh.m_vertices[i].TexCoord[1] << std::endl;
	}

	for (int i = 0; i < clothMesh.m_indices.size(); i = i + 6) {
		std::cout << clothMesh.m_indices[i] << " ";
		std::cout << clothMesh.m_indices[i+1] << " ";
		std::cout << clothMesh.m_indices[i+2] << " ";
		std::cout << clothMesh.m_indices[i+3] << " ";
		std::cout << clothMesh.m_indices[i+4] << " ";
		std::cout << clothMesh.m_indices[i+5] << " ";
		std::cout << std::endl;
	}

	Loader loader;
	Model model = loader.loadToVAO(clothMesh.m_vertices, clothMesh.m_indices);
	GLuint textureID = loader.loadTexture("pic.png", false);
	Texture texture(textureID);
	TexturedModel texturedModel(model, texture);

	std::cout << model.getVertexCount() << std::endl;
	std::cout << "Game Loop is running now" << std::endl;
	Renderer render;
	BasicShader shader;
	// 渲染循环
	while (m_displayManager->isWindowOpen())
	{
		render.prepare();
		shader.use();
		render.Render(texturedModel);
		shader.unUse();
		// updateDisplay 中不能加入 prepare 逻辑
		m_displayManager->updateDisplay();
	}
	loader.cleanUp();
}