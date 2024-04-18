#include "Shader.h"

#include <stdexcept>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

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
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogSize);

		GLchar* logBuffer = new GLchar[infoLogSize + 1];
		glGetShaderInfoLog(shaderId, infoLogSize, &infoLogSize, logBuffer);

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

	auto programId = glCreateProgram();
	auto* entry = shaderInfo;

	while (entry->type != GL_NONE)
	{
		auto shaderId = glCreateShader(entry->type);
		entry->shaderId = shaderId;

		auto str = ReadShader(entry->filename);

		const char* cstr = str.c_str();

		glShaderSource(shaderId, 1, &cstr, nullptr);
		glCompileShader(shaderId);

		GLint hasCompiled;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &hasCompiled);

		if (!hasCompiled)
		{
			ThrowException(shaderId, entry->filename, "Erreur de compilation du shader: ");
		}

		glAttachShader(programId, shaderId);
		++entry;
	}

	glLinkProgram(programId);

	GLint isLinked;
	glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);

	if (!isLinked)
	{
		ThrowException(programId, entry->filename, "Erreur de linkage du programme de shaders: ");
	}

	return programId;
}