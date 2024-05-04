#pragma once

#include "Mesh.h"

template <typename T>
class RectangleShape : public Mesh<T>
{
public:
	RectangleShape(const Point3D<T>& location, T width, T height, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
		: Mesh<T>(std::vector<Vertex<T>>(createRectangleShapeVertices(location, width, height)), std::vector<unsigned int>(createRectangleShapeIndices()), vertexShaderPath, fragmentShaderPath)
	{
	}

	~RectangleShape() = default;

	void load() override
	{
		Mesh<T>::load();
	}

	void update() override
	{
		// Do nothing
		Mesh<T>::update();
	}

	void render(const Mat4<T>& VP, Point3D<T> cameraPositionWorld) override
	{
		Mesh<T>::render(VP, cameraPositionWorld);
	}

private:
	static std::vector<Vertex<T>> createRectangleShapeVertices(const Point3D<T>& center, T width, T height)
	{
		T halfWidth = width / 2;
		T halfHeight = height / 2;

		std::vector<Vertex<T>> vertices;
		vertices.reserve(24);

		// Top face
		vertices.push_back({ {center.x - halfWidth, center.y + halfHeight, center.z + halfWidth}, {0, 1, 0}, {1, 1, 1}, {0, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y + halfHeight, center.z + halfWidth}, {0, 1, 0}, {1, 1, 1}, {1, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y + halfHeight, center.z - halfWidth}, {0, 1, 0}, {1, 1, 1}, {1, 1} });
		vertices.push_back({ {center.x - halfWidth, center.y + halfHeight, center.z - halfWidth}, {0, 1, 0}, {1, 1, 1}, {0, 1} });

		// Bottom face
		vertices.push_back({ {center.x - halfWidth, center.y - halfHeight, center.z + halfWidth}, {0, -1, 0}, {0, 1, 1}, {0, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y - halfHeight, center.z + halfWidth}, {0, -1, 0}, {0, 1, 1}, {1, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y - halfHeight, center.z - halfWidth}, {0, -1, 0}, {0, 1, 1}, {1, 1} });
		vertices.push_back({ {center.x - halfWidth, center.y - halfHeight, center.z - halfWidth}, {0, -1, 0}, {0, 1, 1}, {0, 1} });

		// Right face
		vertices.push_back({ {center.x + halfWidth, center.y + halfHeight, center.z + halfWidth}, {1, 0, 0}, {1, 0, 1}, {0, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y + halfHeight, center.z - halfWidth}, {1, 0, 0}, {1, 0, 1}, {1, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y - halfHeight, center.z - halfWidth}, {1, 0, 0}, {1, 0, 1}, {1, 1} });
		vertices.push_back({ {center.x + halfWidth, center.y - halfHeight, center.z + halfWidth}, {1, 0, 0}, {1, 0, 1}, {0, 1} });

		// Left face
		vertices.push_back({ {center.x - halfWidth, center.y + halfHeight, center.z + halfWidth}, {-1, 0, 0}, {1, 1, 0}, {0, 0} });
		vertices.push_back({ {center.x - halfWidth, center.y + halfHeight, center.z - halfWidth}, {-1, 0, 0}, {1, 1, 0}, {1, 0} });
		vertices.push_back({ {center.x - halfWidth, center.y - halfHeight, center.z - halfWidth}, {-1, 0, 0}, {1, 1, 0}, {1, 1} });
		vertices.push_back({ {center.x - halfWidth, center.y - halfHeight, center.z + halfWidth}, {-1, 0, 0}, {1, 1, 0}, {0, 1} });

		// Front face
		vertices.push_back({ {center.x - halfWidth, center.y + halfHeight, center.z + halfWidth}, {0, 0, 1}, {1, 0, 0}, {0, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y + halfHeight, center.z + halfWidth}, {0, 0, 1}, {1, 0, 0}, {1, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y - halfHeight, center.z + halfWidth}, {0, 0, 1}, {1, 0, 0}, {1, 1} });
		vertices.push_back({ {center.x - halfWidth, center.y - halfHeight, center.z + halfWidth}, {0, 0, 1}, {1, 0, 0}, {0, 1} });

		// Back face
		vertices.push_back({ {center.x - halfWidth, center.y + halfHeight, center.z - halfWidth}, {0, 0, -1}, {0, 1, 0}, {0, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y + halfHeight, center.z - halfWidth}, {0, 0, -1}, {0, 1, 0}, {1, 0} });
		vertices.push_back({ {center.x + halfWidth, center.y - halfHeight, center.z - halfWidth}, {0, 0, -1}, {0, 1, 0}, {1, 1} });
		vertices.push_back({ {center.x - halfWidth, center.y - halfHeight, center.z - halfWidth}, {0, 0, -1}, {0, 1, 0}, {0, 1} });

		return vertices;
	}

	static std::vector<unsigned int> createRectangleShapeIndices()
	{
		std::vector<unsigned int> indices;
		indices.reserve(36);

		// Top face
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		indices.push_back(0); indices.push_back(2); indices.push_back(3);

		// Bottom face
		indices.push_back(4); indices.push_back(6); indices.push_back(5);
		indices.push_back(4); indices.push_back(7); indices.push_back(6);

		// Right face
		indices.push_back(8); indices.push_back(10); indices.push_back(9);
		indices.push_back(8); indices.push_back(11); indices.push_back(10);

		// Left face
		indices.push_back(12); indices.push_back(13); indices.push_back(14);
		indices.push_back(12); indices.push_back(14); indices.push_back(15);

		// Front face
		indices.push_back(16); indices.push_back(17); indices.push_back(18);
		indices.push_back(16); indices.push_back(18); indices.push_back(19);

		// Back face
		indices.push_back(20); indices.push_back(22); indices.push_back(21);
		indices.push_back(20); indices.push_back(23); indices.push_back(22);

		return indices;
	}
};