#pragma once

#include "RectangleShape.h"
#include "Vertex.h"
#include "Vector.h"
#include "Matrice.h"

class Texture;

class Cube : public RectangleShape
{
public:
	using Vector3f = Vector3D<float>;
	using Mat4f = Mat4<float>;
	using vertex_type = Vertex<float>;

	Cube(const Vector3f& location, float size, const Texture& texture)
		: RectangleShape(location, size, size, texture)
	{
	}
};