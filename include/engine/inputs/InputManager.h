#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <memory>
#include "InputObserver.h"
#include <vector>
#include <GLFW/glfw3.h>

class InputManager
{
public:
    InputManager();
	void Initialize(GLFWwindow* window);
    void subscribe(std::unique_ptr<InputObserver> observer);

private:
    std::vector<std::unique_ptr<InputObserver>> m_observers;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
        if (inputManager && inputManager->m_observers.size() > 0) {
            for (const auto& observer : inputManager->m_observers) {
                observer->onKeyPressed(key, scancode, action, mods);
            }
        }
    }

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
		if (inputManager) {
			for (const auto& observer : inputManager->m_observers) {
				observer->onMouseMoved(xpos, ypos);
			}
		}
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
		if (inputManager) {
			for (const auto& observer : inputManager->m_observers) {
				observer->onMouseButtonPressed(window, button, action, mods);
			}
		}
	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
		if (inputManager) {
			for (const auto& observer : inputManager->m_observers) {
				observer->onScroll(xoffset, yoffset);
			}
		}
	}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
		if (inputManager) {
			for (const auto& observer : inputManager->m_observers) {
				observer->onWindowResized(width, height);
			}
		}
	}
};


#endif // INPUT_MANAGER_H