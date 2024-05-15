#ifndef CAMERA_INPUT_HANDLER_H
#define CAMERA_INPUT_HANDLER_H

#include "inputs/InputObserver.h"
#include <memory>
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <unordered_set>
#include <map>

class CameraInputHandler : public InputObserver
{
public:
	CameraInputHandler(std::shared_ptr<Camera> camera) : m_camera(camera){}
	~CameraInputHandler() = default;

	void onKeyPressed(int key, int scancode, int action, int mods) override
	{
		scancode;
		m_multiplier = 1.f;
		if (mods == GLFW_MOD_SHIFT)
			m_multiplier = 3.f;

		if (action == GLFW_PRESS)
		{
			m_keyStates[key] = true;
		}
		else if (action == GLFW_RELEASE) 
		{
			m_keyStates[key] = false;
		}
		updateCameraMovement();
		
	};
	void onMouseMoved(double xpos, double ypos) override
	{
		if (m_toggleRotation)
		{
			//on calcule l'offset depuis la dernière position connue de la souris 
			double xOffset = xpos - m_lastX;
			double yOffset = ypos - m_lastY;

			//On met à jour l'orientation de la cam en fonction de l'offset
			m_camera->mouseMoved(xOffset, yOffset);

			//On met à jour les dernières positions connues de la souris
			m_lastX = xpos;
			m_lastY = ypos;
		}

	}

	void onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods) override
	{
		mods;
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			m_toggleRotation = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			//On reset la dernière position de la souris
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			m_lastX = xpos;
			m_lastY = ypos;

		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		{
			m_toggleRotation = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
		}
	}

	void onScroll(double xoffset, double yoffset) override
	{
		m_camera->mouseWheelMoved(xoffset, yoffset);
	}

	void updateCameraMovement()
	{
		if (m_keyStates[forward])
		{
			m_camera->moveForward(m_multiplier);
		}
		if (m_keyStates[backward])
		{
			m_camera->moveBackward(m_multiplier);
		}
		if (m_keyStates[left])
		{
			m_camera->moveLeft(m_multiplier);
		}
		if (m_keyStates[right])
		{
			m_camera->moveRight(m_multiplier);
		}
	}

private:
	std::shared_ptr<Camera> m_camera;
	std::map<int, bool> m_keyStates{ {forward, false}, {backward, false}, {left, false}, {right, false} };
	float m_multiplier = 1.f;
	bool m_toggleRotation = false;

	double m_lastX = 0;
	double m_lastY = 0;

	int forward = Config::CameraForward;
	int backward = Config::CameraBackward;
	int left = Config::CameraLeft;
	int right = Config::CameraRight;
};
#endif // !CAMERA_INPUT_HANDLER_H