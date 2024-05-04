#pragma once

#include "RectangleShape.h"

template <typename T>
class Cube : public RectangleShape<T>
{
public:
	Cube(const Point3D<T>& location, T size)
		: RectangleShape<T>(location, size, size, SHADER_PATH + "cube.vert", SHADER_PATH + "cube.frag")
	{
	}

	~Cube() = default;

	void load() override
	{
		RectangleShape<T>::load();
	}

	void render(const Mat4<T>& VP, Point3D<T> cameraPositionWorld) override
	{
		RectangleShape<T>::render(VP, cameraPositionWorld);
	}

	void update() override
	{
		RectangleShape<T>::update();
	}
};