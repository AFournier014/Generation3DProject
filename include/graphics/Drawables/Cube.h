#pragma once

#include "RectangleShape.h"

template <typename T>
class Cube : public RectangleShape<T>
{
public:

	Cube()
		: RectangleShape<T>(Point3D<T>(0, 0, 0), 1, 1, SHADER_PATH + "cube.vert", SHADER_PATH + "cube.frag")
	{
	}
	Cube(const Point3D<T>& location, T size)
		: RectangleShape<T>(location, size, size, SHADER_PATH + "cube.vert", SHADER_PATH + "cube.frag")
	{
	}

	~Cube()
	{
	}

	virtual void load() override
	{
		RectangleShape<T>::load();
	}

	virtual void render(const Mat4<T>& VP, Point3D<T> cameraPositionWorld) override
	{
		RectangleShape<T>::render(VP, cameraPositionWorld);
	}

	virtual void update() override
	{
		RectangleShape<T>::update();
	}
};