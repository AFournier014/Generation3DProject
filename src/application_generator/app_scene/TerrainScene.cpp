#include "app_scene/TerrainScene.h"
#include "Meshs/simple_shapes/Cube.h"
#include "Config.h"
#include "managers/ShaderManager.h"
#include <Transform.h>
#include <Camera.h>

TerrainScene::TerrainScene(GLFWwindow* window, const std::shared_ptr<ShaderManager> shaderManager, const std::shared_ptr<Camera> camera)
    : Scene(window, shaderManager, camera)
{
}

void TerrainScene::init()
{
    // Temporaire pour tester
    Transform transform(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 1.0f, 1.0f));
	Transform transform2(Vec3f(2.0f, 3.0f, -10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 1.0f, 1.0f));

	auto texture = std::make_shared<Texture>(Config::TEXTURES_PATH + "texture.png");
	m_textures.push_back(texture);
	addMesh<Cube>(transform, texture);
	addMesh<Cube>(transform2, texture);

    
    //sf::Mouse::setPosition(sf::Vector2i(Config::WindowSize().x / 2, Config::WindowSize().y / 2), *m_window);
    glfwSetCursorPos(m_window, static_cast<float>(Config::WindowSize().x) / 2, static_cast<float>(Config::WindowSize().y) / 2);
}


void TerrainScene::update(float deltaTime)
{
    for (auto const& mesh : m_meshes)
    {
        mesh->update();
        mesh->rotate(Vec3f(0.f, 1.f, 0.f), 0.01f);
        mesh->rotate(Vec3f(1.f, 0.f, 0.f), 0.01f);
    }

    if(m_camera)
	    m_camera->update(deltaTime);
}

void TerrainScene::render()
{
    GLCall(glViewport(0, 0, Config::WindowSize().x, Config::WindowSize().y));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));

    initShaders();

    for (auto const& mesh : m_meshes)
    {
        mesh->render(m_shaderManager->getCubeShader());
    }
}

void TerrainScene::initShaders() const
{
    initShader(m_shaderManager->getCubeShader());
    initShader(m_shaderManager->getTerrainShader());
    // initShader(*m_shaderManager->getSkyboxShader());
    // initShader(*m_shaderManager->getTerrainShader());
}

void TerrainScene::initShader(const std::shared_ptr<Shader> shader) const
{
    if (shader && shader->GetRendererID() != 0 && m_camera)
    {
        shader->Bind();
        shader->SetUniformMat4f("ViewProjection", m_camera->GetProjectionViewMatrix());
        shader->SetUniform3f("cameraPositionWorld", m_camera->GetPosition());
    }
}
