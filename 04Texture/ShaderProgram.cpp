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

	// ������״̬
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

	// ������״̬
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

void ShaderProgram::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void ShaderProgram::setBool(const std::string& name, bool value) const
{
	glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void ShaderProgram::setVec2(const std::string& name, glm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(m_programID, name.c_str()), value.x, value.y);
}

void ShaderProgram::setVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(m_programID, name.c_str()), value.x, value.y, value.z);
}

void ShaderProgram::setVec4(const std::string& name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(m_programID, name.c_str()), value.x, value.y, value.z, value.w);
}
