#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <SFML/Window/Window.hpp>
#include "managers/ShaderManager.h"

class Scene {
public:
	Scene(const std::shared_ptr<sf::Window> window, const std::shared_ptr<ShaderManager> shaderManager)
		: m_window(window), m_shaderManager(shaderManager)
	{
	}

	virtual ~Scene() = default;

	virtual void init() = 0; // Initialisation de la scène
	virtual void handleInput() = 0; // Gestion des entrées
	virtual void update(float deltaTime) = 0; // Mise à jour de la scène
	virtual void render() = 0; // Rendu de la scène

protected:
	std::shared_ptr<sf::Window> m_window;
	std::shared_ptr<ShaderManager> m_shaderManager;
};

#endif // SCENE_H