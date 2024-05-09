#pragma once

#include "RectangleShape.h"

class Texture;

class Cube : public RectangleShape
{
public:
	using Point3f = Point3D<float>;
	using Mat4f = Mat4<float>;
	using vertex_type = Vertex<float>;

	Cube(const Point3f& location, float size, Texture& texture)
		: RectangleShape(location, size, size, texture)
	{
	}
};