#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <engine/utils/MathHelper.h>
#include <unordered_map>

struct ShaderInfo {
	unsigned int type;
	const char* filename;
	unsigned int shaderId;
};

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value) const;
	void SetUniform1f(const std::string& name, float value) const;
	void SetUniform3f(const std::string& name, const Point3D<float> point) const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void SetUniformMat3f(const std::string& name, const Mat4<float>& matrix) const;
	void SetUniformMat4f(const std::string& name, const Mat4<float>& matrix) const;

	GLuint GetRendererID() const { return m_RendererID; }

private:
	GLint GetUniformLocation(const std::string& name) const;
	GLuint LoadShader(ShaderInfo* shaders) const;

	GLuint m_RendererID;
	std::string m_VertexPath;
	std::string m_FragmentPath;
	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
};

#endif // SHADER_H