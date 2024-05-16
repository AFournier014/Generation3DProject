#include "Application.h"
#include "managers/SceneManager.h"
#include "managers/ShaderManager.h"
#include <app_scene/TerrainScene.h>
#include <memory>
#include <stdexcept>
#include <camera/Camera.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imGui/ImGuiManager.h>
#include <inputs/InputManager.h>
#include <handler/CameraInputHandler.h>
#include <CameraWidget.h>
#include <TerrainWidget.h>
#include "sky_sphere/Skyphere.h"
#include <AppWidget.h>

Application::Application() : m_shaderManager(std::make_shared<ShaderManager>()),
                             m_sceneManager(std::make_unique<SceneManager>())
{
    if (!glfwInit())
    {
		throw std::runtime_error("Echec de l'initialisation de GLFW");
    }
    int width, height;

	// Configuration de la version d'OpenGL et ImGui
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    m_applicationName = Config::ApplicationName;
    m_windowSize = Config::WindowSize();

	// Création de la fenêtre
    m_window = glfwCreateWindow(m_windowSize.x, m_windowSize.y, m_applicationName.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Echec de la création de la fenêtre");
    }

	//Contexte OpenGL et ImGui
    glfwMakeContextCurrent(m_window);

    m_imGuiManager = std::make_unique<ImGuiManager>(m_window, "#version 430 core");

	// Configuration de la fenêtre
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

	// Configuration de la caméra et de l'inputManager
    m_camera = std::make_shared<Camera>(Vec3f(Config::CameraInitialPosition()), Config::GetAspectRatio(), Config::GetCameraFov(), Config::CameraNear, Config::CameraFar);
	m_inputManager = std::make_unique<InputManager>();

	Initialize();
}

Application::~Application()
{
    Cleanup();

	m_shaderManager.reset();
	m_sceneManager.reset();
	m_inputManager.reset();
	m_camera.reset();
}

void Application::Run()
{
    float lastFrameTime = static_cast<float>(glfwGetTime());
    while (m_isRunning && !glfwWindowShouldClose(m_window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        m_deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
        ProcessEvents();
        Update(m_deltaTime);
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

    m_inputManager->Initialize(m_window);
    m_imGuiManager->Initialize();
	m_sceneManager->pushScene(std::make_unique<TerrainScene>(m_window, m_shaderManager, m_camera));

    bindInputs();
}

void Application::ProcessEvents()
{
	glfwPollEvents();
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_isRunning = false;
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

    m_imGuiManager->BeginFrame();

    CameraWidget cameraWidget = CameraWidget();
	TerrainWidget terrainWidget = TerrainWidget();
    AppWidget applicationWidget = AppWidget();

	terrainWidget.CreateTerrainWidgets();
	cameraWidget.CreateCameraWidgets(m_camera);
    applicationWidget.CreateAppWidgets(m_deltaTime);

    m_imGuiManager->EndFrame();

	// Swap buffers
    glfwSwapBuffers(m_window);
    glfwSwapInterval(1);
}

void Application::Cleanup() const
{
	m_sceneManager->release();

    glfwDestroyWindow(m_window);
    glfwTerminate();

    //ImGui Cleanup
	m_imGuiManager->Shutdown();
}

void Application::initShaders()
{
    auto cubeShader = std::make_shared<Shader>(Config::SHADERS_PATH + "cube.vert", Config::SHADERS_PATH + "cube.frag");
    m_shaderManager->setCubeShader(cubeShader);

    auto triangleShader = std::make_shared<Shader>(Config::SHADERS_PATH + "triangle.vert",
                                                   Config::SHADERS_PATH + "triangle.frag");
    m_shaderManager->setTriangleShader(std::shared_ptr<Shader>(triangleShader));

	auto skyboxShader = std::make_shared<Shader>(Config::SHADERS_PATH + "skysphere.vert", Config::SHADERS_PATH + "skysphere.frag");
	m_shaderManager->setSkyboxShader(skyboxShader);

	auto terrainShader = std::make_shared<Shader>(Config::SHADERS_PATH + "terrain.vert", Config::SHADERS_PATH + "terrain.frag");
	m_shaderManager->setTerrainShader(terrainShader);
}

void Application::initTextures()
{
}

void Application::bindInputs()
{
	std::shared_ptr<CameraInputHandler> cameraInputHandler = std::make_shared<CameraInputHandler>(m_camera);
	m_inputManager->subscribe(cameraInputHandler);
}
