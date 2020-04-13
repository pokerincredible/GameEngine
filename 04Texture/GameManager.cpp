#include <iostream>
#include "GameManager.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"
#include "BasicShader.h"

GameManager::GameManager()
{
	if (glfwInit())
	{
		std::cout << "GLFW initialized successfully" << std::endl;
		// 创建一个 displayManager
		m_displayManager = new DisplayManager(1280, 720, "GameEngine");
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
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,	// left down
		0.5f, -0.5f, 0.0f,	// right down
		-0.5f,  0.5f, 0.0f,	// left top  
		0.5f, 0.5f, 0.0f	// right top
	};
	float indices[] = {
		0, 1, 2,
		2, 3, 1
	};
	float textureCoords[] = {
		0,0,
		1,0,
		0,1,
		1,1
	};
	Loader loader;
	//------------float array to vector<float>------------//
	std::vector<float> vertex_vec(vertices, vertices + sizeof(vertices) / sizeof(float));
	std::vector<int> indices_vec(indices, indices + sizeof(indices) / sizeof(int));
	std::vector<float> texCoords_vec(textureCoords, textureCoords + sizeof(textureCoords) / sizeof(float));
	
	GLuint textureID = loader.loadTexture("pic.png", false);
	Texture texture(textureID);
	Model model = loader.loadToVAO(vertex_vec, indices_vec, texCoords_vec);
	TexturedModel texturedModel(model, texture);

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