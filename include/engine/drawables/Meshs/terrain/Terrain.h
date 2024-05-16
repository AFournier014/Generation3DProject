#ifndef TERRAIN_H
#define TERRAIN_H

#include <Meshs/Mesh.h>

class Terrain : public Mesh
{
public:

	Terrain(const std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices, const std::shared_ptr<RenderConfig> rendererConfig)
		: Mesh(vertices, indices, rendererConfig)
	{}

private:
};


#endif // !TERRAIN_H