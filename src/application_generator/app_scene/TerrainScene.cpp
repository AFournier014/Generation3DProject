#include "app_scene/TerrainScene.h"
#include "Meshs/simple_shapes/Cube.h"
#include "Config.h"
#include "managers/ShaderManager.h"
#include <Camera.h>
#include "sky_sphere/Skyphere.h"
#include "lights/Light.h"
#include <RenderConfig.h>
#include "terrain/Chunk.h"

#include "Renderer.h"
#include "TerrainWidget.h"

TerrainScene::TerrainScene(GLFWwindow* window, const std::shared_ptr<ShaderManager> shaderManager, const std::shared_ptr<Camera> camera)
	: Scene(window, shaderManager, camera)
{
}

void TerrainScene::init()
{
	auto skySphereTexture = std::make_shared<Texture>(Config::TEXTURES_PATH + "Skysphere.png");
	m_skyphere = std::make_unique<Skyphere>(skySphereTexture);

	auto terrainTexture = std::make_shared<Texture>(Config::TEXTURES_PATH + "terrain.png");

	m_directionalLight = std::make_shared<DirectionalLight>(Vector3f(1, -1.f, 0.f), Color4f(1.f, 1.f, 1.f, 1.f));
	m_opticalProperties = std::make_shared<OpticalProperties>(0.3f, 0.7f, 1.f, 32.f);
	m_terrainWidget = std::make_unique<TerrainWidget>();

	// Temporaire pour tester
	Transformf transform(Vec3f(0.0f, 0.0f, -10.0f), Mat4f::Identity(), Vec3f(1.0f, 1.0f, 1.0f));
	Transformf transform2(Vec3f(2.0f, 3.0f, -10.0f), Mat4f::Identity(), Vec3f(1.0f, 1.0f, 1.0f));
	Transformf transformTerrain(Vec3f(0.0f, 0.0f, 0.0f), Mat4f::Identity(), Vec3f(1.0f, 1.0f, 1.0f));

	auto renderConfigCube = std::make_shared<RenderConfig>();
	renderConfigCube->transform = transform;
	renderConfigCube->texture = std::make_shared<Texture>(Config::TEXTURES_PATH + "texture.png");
	renderConfigCube->shader = m_shaderManager->getCubeShader();
	renderConfigCube->directionalLight = m_directionalLight;
	renderConfigCube->opticalProperties = m_opticalProperties;

	auto renderConfigCube2 = std::make_shared<RenderConfig>();
	renderConfigCube2->transform = transform2;
	renderConfigCube2->texture = renderConfigCube->texture;
	renderConfigCube2->shader = m_shaderManager->getCubeShader();
	renderConfigCube2->directionalLight = m_directionalLight;
	renderConfigCube2->opticalProperties = m_opticalProperties;

	auto renderConfigTerrain = std::make_shared<RenderConfig>();
	renderConfigTerrain->transform = transformTerrain;
	renderConfigTerrain->texture = terrainTexture;
	renderConfigTerrain->shader = m_shaderManager->getTerrainShader();
	renderConfigTerrain->directionalLight = m_directionalLight;
	renderConfigTerrain->opticalProperties = m_opticalProperties;

	m_mapGenerator = std::make_unique<MapGenerator>(renderConfigTerrain);
	m_mapGenerator->generate_chunk_preview();

	m_textures.push_back(renderConfigCube->texture);
	m_textures.push_back(terrainTexture);

	addMesh<Cube>(renderConfigCube);
	addMesh<Cube>(renderConfigCube2);

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

	if (m_camera)
		m_camera->update(deltaTime);
}

void TerrainScene::render()
{
	GLCall(glViewport(0, 0, Config::WindowSize().x, Config::WindowSize().y));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));

	initShaders();
	m_terrainWidget->CreateTerrainWidgets();
	for (auto const& mesh : m_meshes)
	{
		mesh->render();
	}
	m_skyphere->render(m_shaderManager->getSkyboxShader());

	m_mapGenerator->render_preview_chunk();
}

void TerrainScene::initShaders() const
{
	initShader(m_shaderManager->getCubeShader());
	initShader(m_shaderManager->getTerrainShader());
	initShader(m_shaderManager->getSkyboxShader());
	initShader(m_shaderManager->getTerrainShader());
}

void TerrainScene::initShader(const std::shared_ptr<Shader> shader) const
{
	if (shader && shader->GetRendererID() != 0 && m_camera)
	{
		shader->Bind();
		shader->SetUniformMat4f("ViewProjection", m_camera->getProjectionViewMatrix());
		shader->SetUniform3f("cameraPositionWorld", m_camera->getPosition());
	}
}
