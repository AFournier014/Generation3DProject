#include "engine/opengl/Shader.h"
#include <engine/opengl/Renderer.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <malloc.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	: m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
{
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, vertexPath.c_str()},
		{ GL_FRAGMENT_SHADER, fragmentPath.c_str()},
		{ GL_NONE, nullptr }
	};
	m_RendererID = LoadShader(shaders);
}

Shader::~Shader()
{
	m_UniformLocationCache.clear();

	m_VertexPath.clear();
	m_FragmentPath.clear();
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::Release() const
{
	GLCall(glDeleteProgram(m_RendererID));

	GLCall(glDeleteProgram(m_RendererID));
	for (auto const& [key, val] : m_UniformLocationCache)
	{
		GLCall(glDeleteShader(val));
	}
}

void Shader::SetUniform1i(const std::string& name, int value) const
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value) const
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const std::string& name, const Vector3D<float> Vector) const
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, Vector.data()));
}

void Shader::SetUniformMat3f(const std::string& name, const Mat4<float>& matrix) const
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, matrix.data()));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const Mat4<float>& matrix) const
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.data()));
}

GLint Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.contains(name))
	{
		return m_UniformLocationCache[name];
	}
	return m_UniformLocationCache[name] = glGetUniformLocation(m_RendererID, name.c_str());
}

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

GLuint Shader::LoadShader(ShaderInfo* shaders) const
{
	if (shaders == nullptr)
	{
		throw std::runtime_error("Aucun shader à charger");
	}

	GLCall(auto program = glCreateProgram());

	auto* entry = shaders;

	while (entry->type != GL_NONE)
	{
		GLCall(auto id = glCreateShader(entry->type));

		entry->shaderId = id;

		auto str = ReadShader(entry->filename);

		const char* csrc = str.c_str();

		GLCall(glShaderSource(id, 1, &csrc, nullptr));
		GLCall(glCompileShader(id));

		GLint hasCompiled;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &hasCompiled));

		if (!hasCompiled)
		{
			ThrowException(id, entry->filename, "Erreur de compilation du shader: ");
		}

		GLCall(glAttachShader(program, id));

		++entry;
		GLCall(glDeleteShader(id));
	}

	GLCall(glLinkProgram(program));

	GLint isLinked;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &isLinked));

	if (!isLinked)
	{
		ThrowException(program, entry->filename, "Erreur de linkage du programme de shaders: ");
	}

	GLCall(glValidateProgram(program));

	return program;
}