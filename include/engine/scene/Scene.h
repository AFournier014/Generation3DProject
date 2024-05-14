#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <SFML/Window/Window.hpp>
#include "managers/ShaderManager.h"

class Camera;

class Scene {
public:
	Scene(const std::shared_ptr<sf::Window> window, const std::shared_ptr<ShaderManager> shaderManager, const std::shared_ptr<Camera> camera)
		: m_window(window), m_shaderManager(shaderManager), m_camera(camera)
	{
	}

	virtual ~Scene() = default;

	virtual void init() = 0; // Initialisation de la scène
	virtual void update(float deltaTime) = 0; // Mise à jour de la scène
	virtual void render() = 0; // Rendu de la scène

protected:
	std::shared_ptr<sf::Window> m_window;
	std::shared_ptr<ShaderManager> m_shaderManager;
	std::shared_ptr<Camera> m_camera;
};

#endif // SCENE_H
