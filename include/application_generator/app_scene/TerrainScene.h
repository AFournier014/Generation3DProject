#ifndef TERRAIN_SCENE_H
#define TERRAIN_SCENE_H

#include "scene/Scene.h"
#include "Config.h"
#include "memory"
#include "Texture.h"
#include "vector"
#include "Meshs/Mesh.h"
#include "terrain/MapGenerator.h"

class Shader;
class ShaderManager;
class Camera;
class Skyphere;
class DirectionalLight;
struct OpticalProperties;

class TerrainScene : public Scene
{
public:
	TerrainScene(GLFWwindow* window, const std::shared_ptr<ShaderManager> shaderManager, const std::shared_ptr<Camera> camera);
	~TerrainScene() override
	{
		m_meshes.clear();
		m_shaderManager.reset();
		m_camera.reset();
	}

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void initShaders() const;
	void initShader(const std::shared_ptr<Shader> shader) const;
	void release() const override
	{
		for (auto& texture : m_textures)
		{
			texture->Release();
		}
		for (auto& mesh : m_meshes)
		{
			mesh->release();
		}
	}


	template <typename MeshT>
	MeshT* addMesh(std::shared_ptr<RenderConfig> renderConfig)
	{
		auto* mesh = new MeshT(renderConfig);
		m_meshes.push_back(std::unique_ptr<Mesh>(mesh));
		return mesh;
	}

private:
	std::vector<std::unique_ptr<Mesh>> m_meshes;
	std::unique_ptr<MapGenerator> m_mapGenerator;
	std::unique_ptr<Skyphere> m_skyphere;
	std::shared_ptr<DirectionalLight> m_directionalLight;
	std::vector<std::shared_ptr<Texture>> m_textures;
	std::shared_ptr<OpticalProperties> m_opticalProperties;
	std::unique_ptr<TerrainWidget> m_terrainWidget;
};

#endif // TERRAIN_SCENE_H