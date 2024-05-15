#ifndef CHUNK_H
#define CHUNK_H

#include "Meshs/Mesh.h"

class Chunk
{
public:
	Chunk(int size, const Vector3D<float>& position);
	Mesh* getMesh() const { return m_mesh; }

private:
	void generate_mesh(int chunkSize, Vector3D<float> pos);
	static void recalculate_normals(std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices);
	static std::vector<std::vector<float>> generate_height_map(int width, int height);
	
	Mesh* m_mesh;
	int m_size;
	Vector3D<float> m_position;
};

inline float MapValue(float minimum, float maximum, float value)
{
	return minimum + (maximum - minimum) * ((value - 0) / (1 - 0));
}

inline float GetRandF(float fMin, float fMax)
{
	return (fMax - fMin) * ((((float)rand()) / (float)RAND_MAX)) + fMin;
}

inline int GetRand(int min, int max)
{
	return min + (rand() % static_cast<int>(max - min + 1));
}

#endif // APPLICATION_H