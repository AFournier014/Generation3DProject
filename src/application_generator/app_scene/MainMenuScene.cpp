#include "app_scene/MainMenuScene.h"
#include <sstream>
#include "SFML/Graphics.hpp"

MainMenuScene::MainMenuScene(const std::shared_ptr<sf::Window>& window)
	: m_window(window)
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

void MainMenuScene::handleInput()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				// Start the game
			}
			else if (event.key.code == sf::Keyboard::Num2)
			{
				m_window->close();
			}
		}
	}
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
