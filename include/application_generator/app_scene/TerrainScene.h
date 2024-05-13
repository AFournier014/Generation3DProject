#ifndef TERRAIN_SCENE_H
#define TERRAIN_SCENE_H

#include "scene/Scene.h"
#include "Config.h"
#include "memory"
#include "vector"
#include "SFML/Window.hpp"

class Texture;
class Mesh;
class Shader;
class ShaderManager;

class TerrainScene : public Scene
{
public:
	TerrainScene(const std::shared_ptr<sf::Window> window, const std::shared_ptr<ShaderManager> shaderManager);
	~TerrainScene() override = default;

	void init() override;
	void handleInput() override;
	void update(float deltaTime) override;
	void render() override;
	void initShaders() const;
	void initShader(const std::shared_ptr<Shader> shader) const;

	template <typename MeshT, typename T>
	MeshT* addMesh(Transform<T> transform, Texture texture)
	{
		auto* mesh = new MeshT(transform, texture);
		m_meshes.push_back(std::unique_ptr<Mesh>(mesh));
		return mesh;
	}

private:

	// Temporaire
	std::vector<std::unique_ptr<Mesh>> m_meshes;
	Mat4f m_projectionMatrix;
	std::shared_ptr<sf::Window> m_window;
	Mat4f m_viewMatrix;

	float m_cameraSpeed = 0.1f;
	float m_cameraRotationSpeed = 0.1f;
	float m_alpha = 0.f;
	float m_beta = 0.f;
};

#endif // TERRAIN_SCENE_H