#pragma once
#include "glm/glm.hpp"
#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// 通用着色器类
class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertShaderPath, const std::string& fragShaderPath);
	~ShaderProgram();
	void use();
	void unUse();
private:
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
	GLuint loadShader(const std::string& fileName, GLenum type);
protected:
	void bindAttribute(int attribute, const std::string& varName);
	GLuint getUniformLocation(const std::string& name);

	void loadBool(GLuint location, bool value);
	void loadFloat(GLuint location, float value);
	void loadVector(GLuint location, const glm::vec3 value);
	void loadMatrix(GLuint location, const glm::mat4 value);
};

