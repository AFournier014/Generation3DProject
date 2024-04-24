#include "Shader.h"

#include <stdexcept>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <OpenGL/Renderer.h>

namespace
{
	std::string ReadShader(const char* filename)
	{
		std::ifstream inputFile(filename);
		if (!inputFile.is_open())
		{
			throw std::runtime_error("Impossible d'ouvrir le fichier de shader: " + std::string(filename));
		}

		std::stringstream buffer;
		buffer << inputFile.rdbuf();

		inputFile.close();
		return buffer.str();
	}

	void ThrowException(auto& shaderId, const char* filename, const char* message)
	{
		GLint infoLogSize;
		GLCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogSize));

		GLchar* logBuffer = new GLchar[infoLogSize + 1];
		GLCall(glGetShaderInfoLog(shaderId, infoLogSize, &infoLogSize, logBuffer));

		std::cerr << logBuffer << std::endl;

		delete[] logBuffer;

		throw std::runtime_error(message + std::string(filename));
	}
}

unsigned int Shader::LoadShaders(ShaderInfo* shaderInfo)
{
	if (shaderInfo == nullptr)
	{
		throw std::runtime_error("Aucun shader à charger");
	}

	GLCall(auto programId = glCreateProgram());
	auto* entry = shaderInfo;

	while (entry->type != GL_NONE)
	{
		GLCall(auto shaderId = glCreateShader(entry->type));
		entry->shaderId = shaderId;

		auto str = ReadShader(entry->filename);

		const char* cstr = str.c_str();

		GLCall(glShaderSource(shaderId, 1, &cstr, nullptr));
		GLCall(glCompileShader(shaderId));

		GLint hasCompiled;
		GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &hasCompiled));

		if (!hasCompiled)
		{
			ThrowException(shaderId, entry->filename, "Erreur de compilation du shader: ");
		}

		GLCall(glAttachShader(programId, shaderId));
		++entry;

		GLCall(glDeleteShader(shaderId));
	}

	GLCall(glLinkProgram(programId));

	GLint isLinked;
	GLCall(glGetProgramiv(programId, GL_LINK_STATUS, &isLinked));

	if (!isLinked)
	{
		ThrowException(programId, entry->filename, "Erreur de linkage du programme de shaders: ");
	}

	GLCall(glValidateProgram(programId));
	
	return programId;
}