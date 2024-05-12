#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <memory>
#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager() = default;
	~ShaderManager() = default;

	void setCubeShader(const std::shared_ptr<Shader>& shader) { m_cubeShader = shader; }
	void setTriangleShader(const std::shared_ptr<Shader>& shader) { m_triangleShader = shader; }
	void setTerrainShader(const std::shared_ptr<Shader>& shader) { m_terrainShader = shader; }
	void setSkyboxShader(const std::shared_ptr<Shader>& shader) { m_skyboxShader = shader; }

	std::shared_ptr<Shader> getCubeShader() { return m_cubeShader; }
	std::shared_ptr<Shader> getTriangleShader() { return m_triangleShader; }
	std::shared_ptr<Shader> getTerrainShader() { return m_terrainShader; }
	std::shared_ptr<Shader> getSkyboxShader() { return m_skyboxShader; }

private:
	std::shared_ptr<Shader> m_cubeShader;
	std::shared_ptr<Shader> m_triangleShader;
	std::shared_ptr<Shader> m_terrainShader;
	std::shared_ptr<Shader> m_skyboxShader;
};

#endif // SHADER_MANAGER_H