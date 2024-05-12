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

class TerrainScene : public Scene
{
public:
	TerrainScene();
	~TerrainScene() override = default;

	void init() override;
	void handleInput() override;
	void update(float deltaTime) override;
	void render() override;

	template <typename T>
	T* addMesh(Vec3f position, Texture texture)
	{
		auto* mesh = new T(position, 1.f, texture);
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

	Shader* m_shader;
};

#endif // TERRAIN_SCENE_H