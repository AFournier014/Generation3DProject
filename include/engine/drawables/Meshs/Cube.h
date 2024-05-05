#pragma once

#include "RectangleShape.h"

template <typename T>
class Cube : public RectangleShape<T>
{
public:
	Cube(const Point3D<T>& location, T size, const Texture& texture)
		: RectangleShape<T>(location, size, size, texture)
	{
	}

	~Cube() = default;

	void render(Shader& shader, const Mat4<T>& VP, const Point3D<T>& cameraPositionWorld) override
	{
		RectangleShape<T>::render(shader, VP, cameraPositionWorld);
	}

	void update() override
	{
		RectangleShape<T>::update();
	}
};