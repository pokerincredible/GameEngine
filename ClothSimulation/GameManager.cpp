#include <iostream>
#include "GameManager.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"
#include "BasicShader.h"
#include "Camera.h"
#include "Mesh.h"

// System parameters
namespace SystemParam {
	static const int n = 33;					// must be odd, n * n = n_vertices | 61
	static const float w = 2.0f;				// width | 2.0f
	static const float h = 0.008f;				// time step, smaller for better results | 0.008f = 0.016f/2
	static const float r = w / (n - 1) * 1.05f; // spring rest legnth
	static const float k = 1.0f;				// spring stiffness | 1.0f;
	static const float m = 0.25f / (n * n);		// point mass | 0.25f
	static const float a = 0.993f;				// damping, close to 1.0 | 0.993f
	static const float g = 9.8f * m;			// gravitational force | 9.8f
}

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

void GameManager::initCloth() {
	const int n = SystemParam::n;
	const float w = SystemParam::w;
	// generate mesh
	MeshBuilder meshBuilder;
	meshBuilder.uniformGrid(w, n);
	m_clothMesh = meshBuilder.getResult();

}

void GameManager::loop()
{
	std::cout << "Game Loop is running now" << std::endl;
	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,	// left down
		0.5f, -0.5f, 0.0f,	// right down
		-0.5f,  0.5f, 0.0f,	// left top  
		0.5f, 0.5f, 0.0f	// right top
	};
	int indices[] = {
		0, 1, 2,
		2, 3, 1
	};
	
	Loader loader;
	initCloth();
	std::vector<float> vertices_vec(vertices, vertices + sizeof(vertices) / sizeof(float));
	std::vector<int> indices_vec(indices, indices + sizeof(indices) / sizeof(int));

	RawModel rawModel = loader.loadToVAO(vertices_vec, indices_vec);
	std::cout << rawModel.getVertexCount() << std::endl;
	Renderer render;
	BasicShader shader;
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	// 渲染循环
	while (m_displayManager->isWindowOpen())
	{
		render.prepare();
		shader.use();
		render.Render(rawModel);
		shader.unUse();
		m_displayManager->updateDisplay();
	}
	// delete vao, vbo 等 buffer
	loader.cleanUp();
}