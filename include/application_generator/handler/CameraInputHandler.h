#ifndef CAMERA_INPUT_HANDLER_H
#define CAMERA_INPUT_HANDLER_H

#include "inputs/InputObserver.h"
#include <memory>
#include "Camera.h"
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
		m_multiplier = mods == GLFW_MOD_SHIFT? 3.f : 1.f;

		m_pendingKeyChanges.push_back(std::make_pair(key, action == GLFW_PRESS || action == GLFW_REPEAT));

		scheduleBatchedProcessing();
	};

	void onMouseMoved(double xpos, double ypos) override
	{
		if (m_toggleRotation)
		{
			//on calcule l'offset depuis la derni�re position connue de la souris 
			double xOffset = xpos - m_lastX;
			double yOffset = ypos - m_lastY;

			//On met � jour l'orientation de la cam en fonction de l'offset
			m_camera->mouseMoved(xOffset, yOffset);

			//On met � jour les derni�res positions connues de la souris
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

			//On reset la derni�re position de la souris
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

	void onWindowResized(int width, int height) override
	{
		m_camera->setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	}

	void scheduleBatchedProcessing()
	{
		// Implement logic to process pending changes in batches
		processPendingChanges();
	}

	void processPendingChanges()
	{
		// Process all pending key state changes
		std::for_each(m_pendingKeyChanges.begin(), m_pendingKeyChanges.end(), [&](const auto& change) {
			int key = change.first;
			bool state = change.second;

			// Update key state in the map
			m_keyStates[key] = state;
			});

		// Clear the pending changes buffer after processing
		m_pendingKeyChanges.clear();

		// Update camera movement based on the updated key states
		updateCameraMovement();
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

	std::vector<std::pair<int, bool>> m_pendingKeyChanges;

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