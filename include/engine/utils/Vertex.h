#ifndef VERTEX_H
#define VERTEX_H

#include <Color.h>
#include <Point.h>

template <typename T>
struct Vertex
{
	Point3D<T> position = Point3D<T>(0, 0, 0);
	Point3D<T> normal = Point3D<T>(0, 0, 0);
	Color3<T> color = Color3<T>(0, 0, 0);
	Point2D<T> texture = Point2D<T>(0, 0);
};

#endif // !VERTEX_H