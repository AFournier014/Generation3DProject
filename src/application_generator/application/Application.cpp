#include "Application.h"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <Renderer.h>
#include <memory>
#include "app_scene/SceneManager.h"
#include <app_scene/TerrainScene.h>

Application::Application() : m_sceneManager(std::make_unique<SceneManager>()), m_isRunning(true)
{
	m_applicationName = Config::ApplicationName;
	m_windowSize = Config::WindowSize();

	m_contextSettings = sf::ContextSettings(Config::ContextSettingsDepthBits, Config::ContextSettingsStencilBits,
		Config::ContextSettingsAntialiasingLevel, Config::ContextSettingsMajorVersion, Config::ContextSettingsMinorVersion);

	m_window = std::make_shared<sf::Window>();
	m_window->create(sf::VideoMode(m_windowSize.x, m_windowSize.y), m_applicationName, sf::Style::Default, m_contextSettings);

	m_window->setVerticalSyncEnabled(true);
	m_window->setActive(true);

	Initialize();
}

Application::~Application()
{
	Cleanup();
}

void Application::Run()
{
	sf::Clock clock;
	while (m_isRunning && m_window->isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		ProcessEvents();
		Update(deltaTime);
		Render();
	}
}

void Application::Initialize()
{
	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		throw std::runtime_error("Echec de l'initialisation de GLEW");
	};
	glEnable(GL_DEPTH_TEST);

	m_sceneManager->pushScene(std::make_unique<TerrainScene>());
}

void Application::ProcessEvents()
{
	//m_inputManager->processInput(*m_window);
}

void Application::Update(float deltaTime) const
{
	m_sceneManager->update(deltaTime);
}

void Application::Render()
{
	m_window->setActive(true);

	// Nettoyage de la fenêtre
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_sceneManager->render();

	glFlush();

	m_window->display();
}

void Application::Cleanup() const
{
	m_window->close();
}