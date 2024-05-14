#include "Application.h"
#include "managers/SceneManager.h"
#include "managers/ShaderManager.h"
#include <app_scene/TerrainScene.h>
#include <memory>
#include <stdexcept>
#include <camera/Camera.h>

Application::Application() : m_shaderManager(std::make_unique<ShaderManager>()),
                             m_sceneManager(std::make_unique<SceneManager>())
{
    if (!glfwInit())
    {
        // Initialization failed
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    m_applicationName = Config::ApplicationName;
    m_windowSize = Config::WindowSize();

    m_window = glfwCreateWindow(m_windowSize.x, m_windowSize.y, m_applicationName.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Echec de la création de la fenêtre");
    }
    glfwMakeContextCurrent(m_window);
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

	m_window->setVerticalSyncEnabled(true);
	m_window->setActive(true);

	m_camera = std::make_shared<Camera>(Vec3f(0.f, 0.f, 0.f), Config::GetAspectRatio(), Config::GetCameraFov(), Config::CameraNear, Config::CameraFar);
	m_inputManager = std::make_unique<InputManager>();

	Initialize();
}

Application::~Application()
{
    Cleanup();
}

void Application::Run()
{
    double time = glfwGetTime();
    while (m_isRunning && !glfwWindowShouldClose(m_window))
    {
        float deltaTime = static_cast<float>(glfwGetTime() - time);
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

	bindInputs();
	m_sceneManager->pushScene(std::make_unique<TerrainScene>(m_window, m_shaderManager, m_camera));
}

void Application::ProcessEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isRunning = false;
		}
		if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
			m_camera->InitProjection(static_cast<float>(event.size.width) / event.size.height, Config::GetCameraFov(), Config::CameraNear, Config::CameraFar);
		}
		m_inputManager->handle(event);
	}
}

void Application::Update(float deltaTime) const
{
    m_sceneManager->update(deltaTime);
}

void Application::Render()
{
    // Nettoyage de la fen�tre
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_sceneManager->render();

    glFlush();

    glfwSwapBuffers(m_window);
    glfwSwapInterval(1);
}

void Application::Cleanup() const
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Application::initShaders()
{
    auto cubeShader = std::make_shared<Shader>(Config::SHADERS_PATH + "cube.vert", Config::SHADERS_PATH + "cube.frag");
    m_shaderManager->setCubeShader(cubeShader);

    auto triangleShader = std::make_shared<Shader>(Config::SHADERS_PATH + "triangle.vert",
                                                   Config::SHADERS_PATH + "triangle.frag");
    m_shaderManager->setTriangleShader(std::shared_ptr<Shader>(triangleShader));

    /*auto* terrainShader = new Shader(Config::SHADERS_PATH + "terrain.vert", Config::SHADERS_PATH + "terrain.frag");
    m_shaderManager->setTerrainShader(std::shared_ptr<Shader>(terrainShader));*/
}

void Application::initTextures()
{
}

void Application::bindInputs()
{
	m_inputManager->subscribe("MouseMoved", m_camera);
	m_inputManager->subscribe("Z_KeyPressed", m_camera);
	m_inputManager->subscribe("Q_KeyPressed", m_camera);
	m_inputManager->subscribe("S_KeyPressed", m_camera);
	m_inputManager->subscribe("D_KeyPressed", m_camera);
}
