#include "inputs/InputManager.h"

void InputManager::Initialize(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void InputManager::subscribe(std::shared_ptr<InputObserver> observer)
{
	//Add observer to the observers vector
    m_observers.push_back(observer);
}

void InputManager::unsubscribe(std::shared_ptr<InputObserver> observer)
{
    // Find and remove the observer from the observers vector
    auto it = std::find(m_observers.begin(), m_observers.end(), observer);
    if (it != m_observers.end()) {
        m_observers.erase(it);
    }
}
