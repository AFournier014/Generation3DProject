#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "scene/Scene.h"
#include "Config.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <memory>

class MainMenuScene : public Scene
{
public:
	explicit MainMenuScene(const std::shared_ptr<sf::Window>& window);
	void init() override;
	void handleInput() override;
	void update(float deltaTime) override;
	void render() override;

	void updateMenuText();

private:
	std::shared_ptr<sf::Window> m_window;
	sf::Font m_font;
	sf::Text m_text;
	std::string m_menuText;
};

#endif // MAIN_MENU_SCENE_H