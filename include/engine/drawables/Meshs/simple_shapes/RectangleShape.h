#pragma once

#include "meshs/Mesh.h"
#include <vector>
#include <memory>

class Texture;

class RectangleShape : public Mesh
{
public:
	using Vector3f = Vector3D<float>;
	using Mat4f = Mat4<float>;
	using vertex_type = Vertex<float>;

	RectangleShape(const Vector3f& location, float width, float height, const Texture texture)
		: Mesh(createRectangleShapeVertices(location, width, height), createRectangleShapeIndices(), texture)
	{
		setLocation(location);
		scale({ width, height, 1 });
	}

private:

	static std::vector<vertex_type> createRectangleShapeVertices(const Vector3f& center, float width, float height)
	{
		float halfWidth = width / 2;
		float halfHeight = height / 2;

		std::vector<vertex_type> vertices;
		vertices.reserve(24);

		// Top face
		vertices.push_back({ {center.x() - halfWidth, center.y() + halfHeight, center.z() + halfWidth}, {0, 1, 0}, {1, 1, 1}, {0, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() + halfHeight, center.z() + halfWidth}, {0, 1, 0}, {1, 1, 1}, {1, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() + halfHeight, center.z() - halfWidth}, {0, 1, 0}, {1, 1, 1}, {1, 1} });
		vertices.push_back({ {center.x() - halfWidth, center.y() + halfHeight, center.z() - halfWidth}, {0, 1, 0}, {1, 1, 1}, {0, 1} });

		// Bottom face
		vertices.push_back({ {center.x() - halfWidth, center.y() - halfHeight, center.z() + halfWidth}, {0, -1, 0}, {0, 1, 1}, {0, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() - halfHeight, center.z() + halfWidth}, {0, -1, 0}, {0, 1, 1}, {1, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() - halfHeight, center.z() - halfWidth}, {0, -1, 0}, {0, 1, 1}, {1, 1} });
		vertices.push_back({ {center.x() - halfWidth, center.y() - halfHeight, center.z() - halfWidth}, {0, -1, 0}, {0, 1, 1}, {0, 1} });

		// Right face
		vertices.push_back({ {center.x() + halfWidth, center.y() + halfHeight, center.z() + halfWidth}, {1, 0, 0}, {1, 0, 1}, {0, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() + halfHeight, center.z() - halfWidth}, {1, 0, 0}, {1, 0, 1}, {1, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() - halfHeight, center.z() - halfWidth}, {1, 0, 0}, {1, 0, 1}, {1, 1} });
		vertices.push_back({ {center.x() + halfWidth, center.y() - halfHeight, center.z() + halfWidth}, {1, 0, 0}, {1, 0, 1}, {0, 1} });

		// Left face
		vertices.push_back({ {center.x() - halfWidth, center.y() + halfHeight, center.z() + halfWidth}, {-1, 0, 0}, {1, 1, 0}, {0, 0} });
		vertices.push_back({ {center.x() - halfWidth, center.y() + halfHeight, center.z() - halfWidth}, {-1, 0, 0}, {1, 1, 0}, {1, 0} });
		vertices.push_back({ {center.x() - halfWidth, center.y() - halfHeight, center.z() - halfWidth}, {-1, 0, 0}, {1, 1, 0}, {1, 1} });
		vertices.push_back({ {center.x() - halfWidth, center.y() - halfHeight, center.z() + halfWidth}, {-1, 0, 0}, {1, 1, 0}, {0, 1} });

		// Front face
		vertices.push_back({ {center.x() - halfWidth, center.y() + halfHeight, center.z() + halfWidth}, {0, 0, 1}, {1, 0, 0}, {0, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() + halfHeight, center.z() + halfWidth}, {0, 0, 1}, {1, 0, 0}, {1, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() - halfHeight, center.z() + halfWidth}, {0, 0, 1}, {1, 0, 0}, {1, 1} });
		vertices.push_back({ {center.x() - halfWidth, center.y() - halfHeight, center.z() + halfWidth}, {0, 0, 1}, {1, 0, 0}, {0, 1} });

		// Back face
		vertices.push_back({ {center.x() - halfWidth, center.y() + halfHeight, center.z() - halfWidth}, {0, 0, -1}, {0, 1, 0}, {0, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() + halfHeight, center.z() - halfWidth}, {0, 0, -1}, {0, 1, 0}, {1, 0} });
		vertices.push_back({ {center.x() + halfWidth, center.y() - halfHeight, center.z() - halfWidth}, {0, 0, -1}, {0, 1, 0}, {1, 1} });
		vertices.push_back({ {center.x() - halfWidth, center.y() - halfHeight, center.z() - halfWidth}, {0, 0, -1}, {0, 1, 0}, {0, 1} });

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