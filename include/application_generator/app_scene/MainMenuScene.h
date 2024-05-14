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
	explicit MainMenuScene(const std::shared_ptr<sf::Window> window, const std::shared_ptr<ShaderManager> shaderManager, const std::shared_ptr<Camera> camera);
	void init() override;
	void update(float deltaTime) override;
	void render() override;

	void updateMenuText();

private:
	sf::Font m_font;
	sf::Text m_text;
	std::string m_menuText;
};

#endif // MAIN_MENU_SCENE_H