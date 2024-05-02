#pragma once

#include "Drawable.h"

template <typename T>
struct Vertex // possible de templater pour gerer opengl en sachant ce qu'il contient (pas tout compris)
{
	Point3D<T> position;
	Point3D<T> normal;
	Color3<T> color;
	Point2D<T> texture;
};

template <typename T>
class Parallelogram : public Mesh<T>
{
public:
	Parallelogram(const Point3D<T>& location, T width, T height)
		: Mesh<T>(createParallelogramVertices(location, width, height), createParallelogramIndices())
	{}

	~Parallelogram() {}

private:
	static std::vector<Vertex<T>> createParallelogramVertices(const Point3D<T>& center, T width, T height)
	{
		T halfWidth = width / 2;
		T halfHeight = height / 2;

		std::vector<Vertex<T>> vertices;
		vertices.reserve(24);

		// Front face
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y - halfHeight, center.z + halfHeight), Point3D<T>(0, 0, 1), Point2D<T>(0, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y - halfHeight, center.z + halfHeight), Point3D<T>(0, 0, 1), Point2D<T>(1, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y + halfHeight, center.z + halfHeight), Point3D<T>(0, 0, 1), Point2D<T>(1, 1)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y + halfHeight, center.z + halfHeight), Point3D<T>(0, 0, 1), Point2D<T>(0, 1)));
		// Back face
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y - halfHeight, center.z - halfHeight), Point3D<T>(0, 0, -1), Point2D<T>(0, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y - halfHeight, center.z - halfHeight), Point3D<T>(0, 0, -1), Point2D<T>(1, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y + halfHeight, center.z - halfHeight), Point3D<T>(0, 0, -1), Point2D<T>(1, 1)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y + halfHeight, center.z - halfHeight), Point3D<T>(0, 0, -1), Point2D<T>(0, 1)));
		// Right face
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y - halfHeight, center.z + halfHeight), Point3D<T>(1, 0, 0), Point2D<T>(0, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y - halfHeight, center.z - halfHeight), Point3D<T>(1, 0, 0), Point2D<T>(1, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y + halfHeight, center.z - halfHeight), Point3D<T>(1, 0, 0), Point2D<T>(1, 1)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y + halfHeight, center.z + halfHeight), Point3D<T>(1, 0, 0), Point2D<T>(0, 1)));
		// Left face
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y - halfHeight, center.z + halfHeight), Point3D<T>(-1, 0, 0), Point2D<T>(0, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y - halfHeight, center.z - halfHeight), Point3D<T>(-1, 0, 0), Point2D<T>(1, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y + halfHeight, center.z - halfHeight), Point3D<T>(-1, 0, 0), Point2D<T>(1, 1)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y + halfHeight, center.z + halfHeight), Point3D<T>(-1, 0, 0), Point2D<T>(0, 1)));
		// Top face
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y + halfHeight, center.z + halfHeight), Point3D<T>(0, 1, 0), Point2D<T>(0, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y + halfHeight, center.z + halfHeight), Point3D<T>(0, 1, 0), Point2D<T>(1, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y + halfHeight, center.z - halfHeight), Point3D<T>(0, 1, 0), Point2D<T>(1, 1)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y + halfHeight, center.z - halfHeight), Point3D<T>(0, 1, 0), Point2D<T>(0, 1)));
		// Bottom face
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y - halfHeight, center.z + halfHeight), Point3D<T>(0, -1, 0), Point2D<T>(0, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y - halfHeight, center.z + halfHeight), Point3D<T>(0, -1, 0), Point2D<T>(1, 0)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x + halfWidth, center.y - halfHeight, center.z - halfHeight), Point3D<T>(0, -1, 0), Point2D<T>(1, 1)));
		vertices.push_back(Vertex<T>(Point3D<T>(center.x - halfWidth, center.y - halfHeight, center.z - halfHeight), Point3D<T>(0, -1, 0), Point2D<T>(0, 1)));
	}

	static std::vector<unsigned int> createParallelogramIndices()
	{
		std::vector<unsigned int> indices;
		indices.reserve(36);

		// Front face
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		indices.push_back(0); indices.push_back(2); indices.push_back(3);
		// Back face
		indices.push_back(4); indices.push_back(5); indices.push_back(6);
		indices.push_back(4); indices.push_back(6); indices.push_back(7);
		// Right face
		indices.push_back(8); indices.push_back(9); indices.push_back(10);
		indices.push_back(8); indices.push_back(10); indices.push_back(11);
		// Left face
		indices.push_back(12); indices.push_back(13); indices.push_back(14);
		indices.push_back(12); indices.push_back(14); indices.push_back(15);
		// Top face
		indices.push_back(16); indices.push_back(17); indices.push_back(18);
		indices.push_back(16); indices.push_back(18); indices.push_back(19);
		// Bottom face
		indices.push_back(20); indices.push_back(21); indices.push_back(22);
		indices.push_back(20); indices.push_back(22); indices.push_back(23);

		return indices;
	}

};