#ifndef VERTEX_H
#define VERTEX_H

#include <Color.h>
#include <Vector.h>

template <typename T>
struct Vertex
{
	Vector3D<T> position = Vector3D<T>(0, 0, 0);
	Vector3D<T> normal = Vector3D<T>(0, 0, 0);
	Color3<T> color = Color3<T>(0, 0, 0);
	Vector2D<T> texture = Vector2D<T>(0, 0);
};

#endif // !VERTEX_H