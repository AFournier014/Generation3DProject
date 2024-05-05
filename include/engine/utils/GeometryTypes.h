#ifndef GEOMETRY_TYPES_H
#define GEOMETRY_TYPES_H

#include <MathHelper.h>

template <typename T>
struct Color3
{
	static constexpr int ndim = 3;

	Color3(const T& r_ = 0, const T& g_ = 0, const T& b_ = 0)
		: r(r_), g(g_), b(b_)
	{}

	Color3(const Color3& c)
		: r(c.r), g(c.g), b(c.b)
	{}

	T r;
	T g;
	T b;
};

template <typename T>
struct Color4
{
	static constexpr int ndim = 4;

	Color4(const T& r_ = 0, const T& g_ = 0, const T& b_ = 0, const T& a_ = 0)
		: r(r_), g(g_), b(b_), a(a_)
	{}

	Color4(const Color4& c)
		: r(c.r), g(c.g), b(c.b), a(c.a)
	{}

	T r;
	T g;
	T b;
	T a;
};

template <typename T>
struct Vertex
{
	Point3D<T> position = Point3D<T>(0, 0, 0);
	Point3D<T> normal = Point3D<T>(0, 0, 0);
	Color3<T> color = Color3<T>(0, 0, 0);
	Point2D<T> texture = Point2D<T>(0, 0);
};

#endif // !GEOMETRY_TYPES_H