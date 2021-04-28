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
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setBool(const std::string& name, bool value) const;
	void setVec2(const std::string& name, glm::vec2 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec4(const std::string& name, glm::vec4 value) const;
};