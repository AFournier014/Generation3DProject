#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Window.hpp>
#include <memory>

class InputManager
{
public:
	bool init();

	void processInput(const std::shared_ptr<sf::Window>& window);
};

#endif // INPUT_MANAGER_H