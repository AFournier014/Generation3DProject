#ifndef APPLICATION_H
#define APPLICATION_H
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include "Config.h"
#include <memory>
#include <string>

class Camera;
class SceneManager;
class InputManager;
class ShaderManager;
class ImGuiManager;

class Application
{
public:
	Application();

	~Application();
	void Run();

private:
	void Initialize();
	void ProcessEvents();
	void Update(float deltaTime) const;
	void Render();
	void Cleanup() const;

	void initShaders();
	void initTextures();
	void bindInputs();
	void setCameraRatio(int width, int height);

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	std::shared_ptr<ShaderManager> m_shaderManager = nullptr;
	std::unique_ptr<SceneManager> m_sceneManager = nullptr;

	Vec2u m_windowSize;
	std::string m_applicationName;
	GLFWwindow* m_window = nullptr;
	bool m_isRunning = true;

	std::shared_ptr<Camera> m_camera;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<ImGuiManager> m_imGuiManager;

	float m_deltaTime = 0.0f;
};

#endif // APPLICATION_H