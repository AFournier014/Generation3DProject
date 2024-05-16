#include "inputs/InputManager.h"


InputManager* s_instance = nullptr;

InputManager::InputManager()
{
    s_instance = this;
}

void InputManager::Initialize(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void InputManager::subscribe(std::unique_ptr<InputObserver> observer)
{
	//Add observer to the observers vector
    m_observers.push_back(std::move(observer));
}

