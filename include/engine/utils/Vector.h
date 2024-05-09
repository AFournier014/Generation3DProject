#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <array>
#include <cmath>

template <typename T>
struct Vector2D
{
	static constexpr int ndim = 2;

	Vector2D(const T& x_ = 0, const T& y_ = 0)
		: x(x_), y(y_)
	{}

	Vector2D(const Vector2D& pt)
		: x(pt.x), y(pt.y)
	{}

	T x;
	T y;
};

template <typename T>
struct Vector3D
{
	static constexpr int ndim = 3;

	Vector3D(const T& x_ = 0, const T& y_ = 0, const T& z_ = 0)
		: coord{ x_, y_, z_ }
	{}

	Vector3D(const Vector3D& pt)
		: coord{ pt.coord }
	{}

	Vector3D<T> operator-() const { return Vector3D<T>{-coord[0], -coord[1], -coord[2]}; }
	Vector3D<T> operator+(const Vector3D<T>& pt) const { return Vector3D<T>{coord[0] + pt.coord[0], coord[1] + pt.coord[1], coord[2] + pt.coord[2]}; }
	Vector3D<T> operator-(const Vector3D<T>& pt) const { return Vector3D<T>{coord[0] - pt.coord[0], coord[1] - pt.coord[1], coord[2] - pt.coord[2]}; }
	Vector3D<T> operator*(const T& scalar) const { return Vector3D<T>{coord[0] * scalar, coord[1] * scalar, coord[2] * scalar}; }
	Vector3D<T>& operator+=(const Vector3D<T>& pt) { coord[0] += pt.coord[0]; coord[1] += pt.coord[1]; coord[2] += pt.coord[2]; return *this; }
	Vector3D<T>& operator-=(const Vector3D<T>& pt) { coord[0] -= pt.coord[0]; coord[1] -= pt.coord[1]; coord[2] -= pt.coord[2]; return *this; }

	T* data() { return coord.data(); }
	const T* data() const { return coord.data(); }

	T& x() { return coord[0]; }
	T& y() { return coord[1]; }
	T& z() { return coord[2]; }
	const T& x() const { return coord[0]; }
	const T& y() const { return coord[1]; }
	const T& z() const { return coord[2]; }

	Vector3D<T> Normalize()
	{
		T norm = std::sqrt(coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2]);
		coord[0] /= norm;
		coord[1] /= norm;
		coord[2] /= norm;
		return *this;
	}

	Vector3D<T> CrossProduct(Vector3D<T> pt)
	{
		return Vector3D<T>{coord[1] * pt.coord[2] - coord[2] * pt.coord[1],
			coord[2] * pt.coord[0] - coord[0] * pt.coord[2],
			coord[0] * pt.coord[1] - coord[1] * pt.coord[0]};
	}

	std::array<T, 3> coord;
};

template <typename T>
Vector3D<T> operator*(const T& scalar, const Vector3D<T>& pt)
{
	return pt * scalar;
}


#endif // !MATH_HELPER_H