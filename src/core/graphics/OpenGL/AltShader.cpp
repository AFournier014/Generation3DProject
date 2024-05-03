#include "OpenGL/AltShader.h"
#include <OpenGL/Renderer.h>
#include <fstream>
#include <sstream>
#include <iostream>

AltShader::AltShader(const std::string& vertexPath, const std::string& fragmentPath)
	: m_VertexPath(vertexPath), m_FragmentPath(fragmentPath), m_RendererID(0)
{
	m_RendererID = CreateShader(vertexPath, fragmentPath);
}

AltShader::~AltShader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void AltShader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void AltShader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void AltShader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void AltShader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void AltShader::SetUniform3f(const std::string& name, Point3D<float> point)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, point.data()));
}

void AltShader::SetUniformMat3f(const std::string& name, Mat4<float> point)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, point.data()));
}

void AltShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void AltShader::SetUniformMat4f(const std::string& name, const Mat4<float>& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.data()));
}

GLint AltShader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	return m_UniformLocationCache[name] = glGetUniformLocation(m_RendererID, name.c_str());
}

std::string AltShader::ReadShader(const char* filename)
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

GLuint AltShader::CompileShader(GLenum type, const char* source)
{
	GLCall(auto id = glCreateShader(type));
	auto str = ReadShader(source);

	const char* src = str.c_str();

	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

GLuint AltShader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
	GLCall(GLuint program = glCreateProgram());
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

	GLCall(glAttachShader(program, vertexShader));
	GLCall(glAttachShader(program, fragmentShader));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	return program;
}