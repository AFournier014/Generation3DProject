#include "Application.h"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <Renderer.h>
#include <Texture.h>
#include "meshs/simple_shapes/Cube.h"
#include <memory>

Mat4<float> Proj;
float alpha = 0.f;
float beta = 0.f;
Vector3D<float> cameraPosition;
std::unique_ptr<Cube> cube;
std::unique_ptr<Shader> shader;

Application::Application() : m_windowSize(0, 0), m_applicationName(""), m_contextSettings(0, 0, 0, 0, 0), m_window(), m_isRunning(true)
{
	m_applicationName = Config::ApplicationName;
	m_windowSize = Config::WindowSize();

	m_contextSettings = sf::ContextSettings(Config::ContextSettingsDepthBits, Config::ContextSettingsStencilBits,
		Config::ContextSettingsAntialiasingLevel, Config::ContextSettingsMajorVersion, Config::ContextSettingsMinorVersion);
	
	m_window = std::make_unique<sf::Window>();
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
		sf::Time deltaTime = clock.restart();
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

	ImGui::SFML::Init(*m_window, sf::Vector2f(static_cast<float>(m_windowSize.x), static_cast<float>(m_windowSize.y)));

	cameraPosition = Config::CameraInitialPosition();
	Proj = Mat4<float>::Projection(static_cast<float>(m_windowSize.x) / static_cast<float>(m_windowSize.y), Config::CameraFov, Config::CameraNear, Config::CameraFar);
	Texture texture(Config::TEXTURES_PATH + "texture.png");
	shader = std::make_unique<Shader>(Config::SHADERS_PATH + "cube.vert", Config::SHADERS_PATH + "cube.frag");
	cube = std::make_unique<Cube>(Vector3D<float>(0.f, 0.f, -10.f), 1.f, texture);
}

void Application::ProcessEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed)
		{
			m_isRunning = false;
		}
		// TODO: Temporaire, à retirer (déplacement de la caméra)
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_isRunning = false;
			}
		}
	}
}

void Application::Update(sf::Time deltaTime) const
{
	ImGui::SFML::Update(sf::Vector2i(sf::Mouse::getPosition(*m_window)), sf::Vector2f(static_cast<float>(m_windowSize.x), static_cast<float>(m_windowSize.y)), deltaTime);
}

void Application::Render()
{
	// OpenGL rendering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube->render(*shader, Proj, cameraPosition);

	glFlush();

	ImGui::Begin("Control Panel");
	if (ImGui::Button("Close!"))
	{
		m_window->close();
	}
	ImGui::End();

	ImGui::SFML::Render();
	m_window->display();
}

void Application::Cleanup() const
{
	ImGui::SFML::Shutdown();
}