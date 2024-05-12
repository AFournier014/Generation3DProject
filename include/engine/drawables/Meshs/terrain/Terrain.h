#ifndef TERRAIN_H
#define TERRAIN_H

#include <meshs/Mesh.h>

class Texture;

class Terrain : public Mesh
{
public:

	Terrain(const std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices, const Texture& texture)
		: Mesh(vertices, indices, texture)
	{}

private:
};


#endif // !TERRAIN_H