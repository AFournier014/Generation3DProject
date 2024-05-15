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
#include <inputs/InputManager.h>
#include <handler/CameraInputHandler.h>

Application::Application() : m_shaderManager(std::make_shared<ShaderManager>()),
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

	m_camera = std::make_shared<Camera>(Vec3f(0.f, 0.f, 0.f), Config::GetAspectRatio(), Config::GetCameraFov(), Config::CameraNear, Config::CameraFar);
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
        float deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
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
    m_inputManager->Init(m_window);
	bindInputs();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	ImGui::StyleColorsDark();

	m_sceneManager->pushScene(std::make_unique<TerrainScene>(m_window, m_shaderManager, m_camera));

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
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

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    {
        ImGui::Begin("Controls");                          // Create a window called "Controls" and append into it.
        ImGui::Text("This is some useful text.");
        ImGui::Checkbox("Demo Window", &m_isRunning);

        if (ImGui::Button("Generate mesh"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        {
            m_isRunning = false;
        }

        ImGui::End();
    }

    // Rendering
    ImGui::Render();

    glfwSwapBuffers(m_window);
    glfwSwapInterval(1);
}

void Application::Cleanup() const
{
	m_sceneManager->release();

    glfwDestroyWindow(m_window);
    glfwTerminate();

    //ImGui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
	std::shared_ptr<CameraInputHandler> cameraInputHandler = std::make_shared<CameraInputHandler>(m_camera);
	m_inputManager->subscribe(cameraInputHandler);
}
