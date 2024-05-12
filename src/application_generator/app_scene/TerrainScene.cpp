#include "app_scene/TerrainScene.h"
#include "Meshs/simple_shapes/Cube.h"
#include "Texture.h"
#include "Config.h"

TerrainScene::TerrainScene()
{
	init();
}

void TerrainScene::init()
{
	addMesh<Cube>(Vec3f(0.0f, 0.0f, -10.0f), Texture(Config::TEXTURES_PATH + "texture.png"));

	m_projectionMatrix = Mat4f::Projection(static_cast<float>(Config::WindowSize().x) / static_cast<float>(Config::WindowSize().y),
		Config::CameraFov / 180.f * 3.14159265359f, Config::CameraNear, Config::CameraFar);

	m_shader = new Shader(Config::SHADERS_PATH + "cube.vert", Config::SHADERS_PATH + "cube.frag");
}

void TerrainScene::handleInput()
{
	// TODO: Handle input
}

void TerrainScene::update(float deltaTime)
{
	deltaTime;
	for (auto const& mesh : m_meshes)
	{
		mesh->update();
		mesh->rotate(Vec3f(0.f, 1.f, 0.f), 0.01f);
	}
}

void TerrainScene::render()
{
	GLCall(glViewport(0, 0, Config::WindowSize().x, Config::WindowSize().y));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));

	m_viewMatrix = Mat4f::RotationX(-m_beta) * Mat4f::RotationY(-m_alpha) * Mat4f::Translation(Vec3f(0.f, 0.f, 0.f));
	Mat4f VP = m_projectionMatrix * m_viewMatrix;

	for (auto const& mesh : m_meshes)
	{
		mesh->render(*m_shader, VP, Config::CameraInitialPosition());
	}
}
