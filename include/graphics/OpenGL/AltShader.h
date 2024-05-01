#pragma once

#include <string>
#include <GL/glew.h>
#include "MathHelper.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class AltShader
{
public:
	AltShader(const std::string& vertexPath, const std::string& fragmentPath);
	~AltShader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const Mat4<float>& matrix);

private:
	GLint GetUniformLocation(const std::string& name);
	std::string ReadShader(const char* filename);
	GLuint CompileShader(GLenum type, const std::string& source);
	GLuint CreateShader(const std::string& vertexSource, const std::string& fragmentSource);

	GLuint m_RendererID;
	std::string m_VertexPath;
	std::string m_FragmentPath;
};