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

	virtual void init() = 0; // Initialisation de la sc�ne
	virtual void handleInput() = 0; // Gestion des entr�es
	virtual void update(float deltaTime) = 0; // Mise � jour de la sc�ne
	virtual void render() = 0; // Rendu de la sc�ne

protected:
	std::shared_ptr<sf::Window> m_window;
	std::shared_ptr<ShaderManager> m_shaderManager;
};

#endif // SCENE_H