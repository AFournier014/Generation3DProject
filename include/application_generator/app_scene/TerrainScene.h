#ifndef TERRAIN_SCENE_H
#define TERRAIN_SCENE_H

#include "scene/Scene.h"
#include "Config.h"
#include "memory"
#include "Texture.h"
#include "vector"
#include <GLFW/glfw3.h>


class Mesh;
class Shader;
class ShaderManager;	

class TerrainScene : public Scene
{
public:
	TerrainScene(GLFWwindow* window, const std::shared_ptr<ShaderManager> shaderManager, const std::shared_ptr<Camera> camera);
	~TerrainScene() override = default;

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void initShaders() const;
	void initShader(const std::shared_ptr<Shader> shader) const;

	template <typename MeshT, typename T>
	MeshT* addMesh(Transform<T> transform, Texture texture)
	{
		auto* mesh = new MeshT(transform, texture);
		m_meshes.push_back(std::unique_ptr<Mesh>(mesh));
		return mesh;
	}

private:
	// Temporaire
	std::vector<std::unique_ptr<Mesh>> m_meshes;

};

#endif // TERRAIN_SCENE_H