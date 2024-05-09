#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <array>
#include <cmath>

template <typename T>
struct Point2D
{
	static constexpr int ndim = 2;

	Point2D(const T& x_ = 0, const T& y_ = 0)
		: x(x_), y(y_)
	{}

	Point2D(const Point2D& pt)
		: x(pt.x), y(pt.y)
	{}

	T x;
	T y;
};

template <typename T>
struct Point3D
{
	static constexpr int ndim = 3;

	Point3D(const T& x_ = 0, const T& y_ = 0, const T& z_ = 0)
		: coord{ x_, y_, z_ }
	{}

	Point3D(const Point3D& pt)
		: coord{ pt.coord }
	{}

	Point3D<T> operator-() const { return Point3D<T>{-coord[0], -coord[1], -coord[2]}; }
	Point3D<T> operator+(const Point3D<T>& pt) const { return Point3D<T>{coord[0] + pt.coord[0], coord[1] + pt.coord[1], coord[2] + pt.coord[2]}; }
	Point3D<T> operator-(const Point3D<T>& pt) const { return Point3D<T>{coord[0] - pt.coord[0], coord[1] - pt.coord[1], coord[2] - pt.coord[2]}; }
	Point3D<T> operator*(const T& scalar) const { return Point3D<T>{coord[0] * scalar, coord[1] * scalar, coord[2] * scalar}; }
	Point3D<T>& operator+=(const Point3D<T>& pt) { coord[0] += pt.coord[0]; coord[1] += pt.coord[1]; coord[2] += pt.coord[2]; return *this; }
	Point3D<T>& operator-=(const Point3D<T>& pt) { coord[0] -= pt.coord[0]; coord[1] -= pt.coord[1]; coord[2] -= pt.coord[2]; return *this; }

	T* data() { return coord.data(); }
	const T* data() const { return coord.data(); }

	const T& x() const { return coord[0]; }
	const T& y() const { return coord[1]; }
	const T& z() const { return coord[2]; }

	Point3D<T> Normalize()
	{
		T norm = std::sqrt(coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2]);
		coord[0] /= norm;
		coord[1] /= norm;
		coord[2] /= norm;
		return *this;
	}

	std::array<T, 3> coord;
};

template <typename T>
Point3D<T> operator*(const T& scalar, const Point3D<T>& pt)
{
	return pt * scalar;
}


#endif // !MATH_HELPER_H