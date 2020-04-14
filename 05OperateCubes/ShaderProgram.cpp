#include "ShaderProgram.h"
#include "Error.h"

ShaderProgram::ShaderProgram(const std::string& vertShaderPath, const std::string& fragShaderPath)
{
	m_vertexShaderID = loadShader(vertShaderPath, GL_VERTEX_SHADER);
	m_fragmentShaderID = loadShader(fragShaderPath, GL_FRAGMENT_SHADER);
	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);
	glLinkProgram(m_programID);
	glValidateProgram(m_programID);

	// ¼ì²é±àÒë×´Ì¬
	GLint status;
	glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLength;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLength);
		GLchar* infoLog = new GLchar[infoLength];
		glGetProgramInfoLog(m_programID, infoLength, NULL, infoLog);
		std::cout << "ERROR: could not validate shader program" << std::endl;
		std::cout << infoLog << std::endl;
		delete[] infoLog;
	}
}

ShaderProgram::~ShaderProgram()
{
	unUse();
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteProgram(m_programID);
}

void ShaderProgram::use()
{
	glUseProgram(m_programID);
}

void ShaderProgram::unUse()
{
	glUseProgram(0);
}

GLuint ShaderProgram::loadShader(const std::string& fileName, GLenum type)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(fileName);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	const char* shaderStr = shaderCode.c_str();
	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderStr, NULL);
	glCompileShader(shaderID);

	// ¼ì²é±àÒë×´Ì¬
	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);
		std::cout << "ERROR: could not compile shader " << infoLog << std::endl;
		delete[] infoLog;
	}
	return shaderID;
}

void ShaderProgram::bindAttribute(int attribute, const std::string& varName)
{
	Error::GLClearError();
	glBindAttribLocation(m_programID, attribute, varName.c_str());
	Error::GLCheckError();
}

GLuint ShaderProgram::getUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_programID, name.c_str());
}

void ShaderProgram::loadBool(GLuint location, bool value)
{
	glUniform1f(location, value ? 1.0f : 0.0f);
}

void ShaderProgram::loadFloat(GLuint location, float value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector(GLuint location, const glm::vec3 value)
{
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::loadMatrix(GLuint location, const glm::mat4 value)
{
	glUniformMatrix4fv(location, 1, false, &value[0][0]);
}

