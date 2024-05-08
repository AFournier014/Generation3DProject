#ifndef TERRAIN_H
#define TERRAIN_H

#include <meshs/Mesh.h>

class Terrain : public Mesh
{
public:

	Terrain(const std::vector<vertex_type>& vertices, const std::vector<unsigned int>& indices, const Texture& texture)
		: Mesh(vertices, indices, texture)
	{}

private:
};


#endif // !TERRAIN_H