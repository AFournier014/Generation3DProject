#ifndef MATRICE_H
#define MATRICE_H

#include <array>
#include <cmath>
#include "Point.h"
#include "List.h"

struct AxisX
{
	static constexpr int r1 = 1;
	static constexpr int r2 = 2;
	static constexpr int i1 = 0;
	static constexpr int i2 = 3;
};

struct AxisY
{
	static constexpr int r1 = 0;
	static constexpr int r2 = 2;
	static constexpr int i1 = 1;
	static constexpr int i2 = 3;
};

struct AxisZ
{
	static constexpr int r1 = 0;
	static constexpr int r2 = 1;
	static constexpr int i1 = 2;
	static constexpr int i2 = 3;
};

using AllAxis = typelist<AxisX, AxisY, AxisZ>;

template <typename T>
class Mat4
{
public:
	Mat4()
	{
		m_coeffs.fill(0);
	}

	T& operator()(int row, int col) { return m_coeffs[row + 4 * col]; }

	const T& operator()(int row, int col) const { return m_coeffs[row + 4 * col]; }

	const T* data() const { return m_coeffs.data(); }

	static Mat4<T> Identity()
	{
		Mat4<T> m;
		m(0, 0) = m(1, 1) = m(2, 2) = m(3, 3) = 1;
		return m;
	}

	static Mat4<T> Translation(const Point3D<T>& translation)
	{
		Mat4<T> m = Identity();
		m(0, 3) = translation.x();
		m(1, 3) = translation.y();
		m(2, 3) = translation.z();
		return m;
	}

	template <typename Axis>
	static Mat4<T> RotationAxisAligned(const T& angle)
	{
		static_assert(contains_v<Axis, AllAxis>, "Invalid axis type");
		Mat4<T> m = Identity();
		m(Axis::r1, Axis::r1) = std::cos(angle);
		m(Axis::r1, Axis::r2) = -std::sin(angle);
		m(Axis::r2, Axis::r1) = std::sin(angle);
		m(Axis::r2, Axis::r2) = std::cos(angle);
		return m;
	}

	static Mat4<T> RotationX(const T& angle)
	{
		return RotationAxisAligned<AxisX>(angle);
	}

	static Mat4<T> RotationY(const T& angle)
	{
		return RotationAxisAligned<AxisY>(angle);
	}

	static Mat4<T> RotationZ(const T& angle)
	{
		return RotationAxisAligned<AxisZ>(angle);
	}

	static Mat4<T> Rotation(const Mat4<T>& matrix, const Point3D<T>& axis, const T& angle)
	{
		T c = std::cos(angle);
		T s = std::sin(angle);
		//axis = axis.Normalize();
		Point3D<T> temp = (1 - c) * axis;

		Mat4<T> rotate = Identity();
		rotate(0, 0) = c + temp.x() * axis.x();
		rotate(0, 1) = temp.x() * axis.y() + s * axis.z();
		rotate(0, 2) = temp.x() * axis.z() - s * axis.y();
		rotate(0, 3) = 0;

		rotate(1, 0) = temp.y() * axis.x() - s * axis.z();
		rotate(1, 1) = c + temp.y() * axis.y();
		rotate(1, 2) = temp.y() * axis.z() + s * axis.x();
		rotate(1, 3) = 0;

		rotate(2, 0) = temp.z() * axis.x() + s * axis.y();
		rotate(2, 1) = temp.z() * axis.y() - s * axis.x();
		rotate(2, 2) = c + temp.z() * axis.z();
		rotate(2, 3) = 0;

		return matrix * rotate;
	}

	static Mat4<T> Scale(const Point3D<T>& scale)
	{
		Mat4<T> m = Identity();
		m(0, 0) = scale.x();
		m(1, 1) = scale.y();
		m(2, 2) = scale.z();
		return m;
	}

	static Mat4<T> Projection(const T& aspect, const T& fov, const T& nearPlane, const T& farPlane)
	{
		Mat4<T> P = Identity();
		P(0, 0) = 1.f / (aspect * std::tan(fov / 2.f));
		P(1, 1) = 1.f / (std::tan(fov / 2.f));
		P(2, 2) = -(farPlane + nearPlane) / (farPlane - nearPlane);
		P(2, 3) = -(2.f * farPlane * nearPlane) / (farPlane - nearPlane);
		P(3, 2) = -1.f;
		return P;
	}

private:
	std::array<T, 16> m_coeffs;
};

template <typename T>
Mat4<T> operator*(const Mat4<T>& op1, const Mat4<T>& op2)
{
	Mat4<T> result;

	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			result(row, col) = 0;
			for (int k = 0; k < 4; ++k)
				result(row, col) += op1(row, k) * op2(k, col);
		}
	}
	return result;
}

template <typename T>
Mat4<T> operator+(const Mat4<T>& op1, const Mat4<T>& op2)
{
	Mat4<T> result;

	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			result(row, col) = op1(row, col) + op2(row, col);
		}
	}
	return result;
}

#endif // !MATRICE_H