#include "ShaderProgram.h"

#include <iostream>

namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) 
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER is not compiled: compile time error" << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER is not compiled: compile time error" << std::endl;
			glDeleteShader(vertexShaderID); // if it's failed, so we have to delete vertexShader too
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		// checking if linking is done correctly
		GLint isSuccess;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &isSuccess);
		if (!isSuccess)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link time error:\n" << infoLog << std::endl;
		}
		else
		{
			m_isCompiled = true;
		}

		// after linking we're deleting vertexShader and fragmentShader
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		// checking if everything is right
		GLint isSuccess;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
		if (!isSuccess)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile time error:\n" << infoLog << std::endl;
			return false;
		}

		return true;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;

		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
	}
}
