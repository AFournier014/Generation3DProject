#ifndef APPLICATION_H
#define APPLICATION_H

#include "Config.h"
#include <memory>
#include <SFML/Window.hpp>
#include <string>

class Camera;
class SceneManager;
class InputManager;
class ShaderManager;

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

	//std::unique_ptr<Camera> m_camera;
	std::shared_ptr<ShaderManager> m_shaderManager = nullptr;
	std::unique_ptr<SceneManager> m_sceneManager = nullptr;
	//std::unique_ptr<InputManager> m_inputManager;

	Vec2u m_windowSize;
	std::string m_applicationName;
	sf::ContextSettings m_contextSettings;
	std::shared_ptr<sf::Window> m_window = nullptr;
	bool m_isRunning = true;
};

#endif // APPLICATION_H