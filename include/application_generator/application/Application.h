#ifndef APPLICATION_H
#define APPLICATION_H

#include "Config.h"
#include <memory>
#include <SFML/Window.hpp>
#include <string>

class Camera;
class OpenGLConfig;
class SceneManager;
class InputManager;

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

	//std::unique_ptr<Camera> m_camera;
	//std::unique_ptr<OpenGLConfig> m_openGLConfig;
	std::unique_ptr<SceneManager> m_sceneManager;
	//std::unique_ptr<InputManager> m_inputManager;

	Vec2u m_windowSize;
	std::string m_applicationName;
	sf::ContextSettings m_contextSettings;
	std::shared_ptr<sf::Window> m_window;
	bool m_isRunning;
};

#endif // APPLICATION_H