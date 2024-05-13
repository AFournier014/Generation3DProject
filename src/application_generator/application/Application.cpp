#include "Application.h"
#include "managers/SceneManager.h"
#include "managers/ShaderManager.h"
#include <app_scene/TerrainScene.h>
#include <GL/glew.h>
#include <memory>
#include <Renderer.h>
#include <SFML/OpenGL.hpp>

Application::Application() : m_shaderManager(std::make_unique<ShaderManager>()), m_sceneManager(std::make_unique<SceneManager>())
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

	initShaders();

	m_sceneManager->pushScene(std::make_unique<TerrainScene>(m_window, m_shaderManager));
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

void Application::initShaders()
{
	auto cubeShader = std::make_shared<Shader>(Config::SHADERS_PATH + "cube.vert", Config::SHADERS_PATH + "cube.frag");
	m_shaderManager->setCubeShader(cubeShader);

	auto triangleShader = std::make_shared<Shader>(Config::SHADERS_PATH + "triangle.vert", Config::SHADERS_PATH + "triangle.frag");
	m_shaderManager->setTriangleShader(std::shared_ptr<Shader>(triangleShader));

	/*auto* terrainShader = new Shader(Config::SHADERS_PATH + "terrain.vert", Config::SHADERS_PATH + "terrain.frag");
	m_shaderManager->setTerrainShader(std::shared_ptr<Shader>(terrainShader));*/
}

void Application::initTextures()
{
}
