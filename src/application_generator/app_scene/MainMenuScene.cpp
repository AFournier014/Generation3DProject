#include "app_scene/MainMenuScene.h"
#include <sstream>
#include "SFML/Graphics.hpp"

MainMenuScene::MainMenuScene(const std::shared_ptr<sf::Window> window, const std::shared_ptr<ShaderManager> shaderManager, const std::shared_ptr<Camera> camera)
	: Scene(window, shaderManager, camera)
{
	if (!m_font.loadFromFile(Config::ArialFontPath))
	{
		throw std::runtime_error("Failed to load font");
	}

	m_text.setFont(m_font);
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::White);
	updateMenuText();
}

void MainMenuScene::init()
{
}

void MainMenuScene::update(float deltaTime)
{
	deltaTime;
}

void MainMenuScene::render()
{
	m_window->display();
}

void MainMenuScene::updateMenuText()
{
	std::stringstream ss;
	ss << "Main Menu\n";
	ss << "Press 1 to start the game\n";
	ss << "Press 2 to exit the game\n";
	m_text.setString(ss.str());
}
