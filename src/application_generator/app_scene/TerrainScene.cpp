#include "app_scene/TerrainScene.h"
#include "Meshs/simple_shapes/Cube.h"
#include "Texture.h"
#include "Config.h"
#include "managers/ShaderManager.h"
#include <Transform.h>

TerrainScene::TerrainScene(const std::shared_ptr<sf::Window> window, const std::shared_ptr<ShaderManager> shaderManager)
	: Scene(window, shaderManager)
{
	float aspect = static_cast<float>(Config::WindowSize().x / Config::WindowSize().y);
	camera = std::make_unique<Camera>(Vec3f(0.f, 0.f, 0.f), aspect, Config::CameraFov, Config::CameraNear, Config::CameraFar);
}

void TerrainScene::init()
{
	// Temporaire pour tester
	Transform transform(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 1.0f, 1.0f));
	addMesh<Cube>(transform, Texture(Config::TEXTURES_PATH + "texture.png"));

}

void TerrainScene::handleInput()
{
	// TODO: Handle input
}

void TerrainScene::update(float deltaTime)
{
	for (auto const& mesh : m_meshes)
	{
		mesh->update();
		mesh->rotate(Vec3f(0.f, 1.f, 0.f), 0.01f);
		mesh->rotate(Vec3f(1.f, 0.f, 0.f), 0.01f);
	}
	camera->Update(deltaTime);
}

void TerrainScene::render()
{
	GLCall(glViewport(0, 0, Config::WindowSize().x, Config::WindowSize().y));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));

	initShaders();

	for (auto const& mesh : m_meshes)
	{
		mesh->render(*m_shaderManager->getCubeShader());
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
	if (shader && shader->GetRendererID() != 0)
	{
		shader->Bind();
		shader->SetUniformMat4f("ViewProjection", camera->GetProjectionViewMatrix());
		shader->SetUniform3f("cameraPositionWorld", camera->GetPosition());
	}
}
