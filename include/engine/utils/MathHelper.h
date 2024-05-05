#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <array>
#include <type_traits>
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
		: x(x_), y(y_), z(z_)
	{}

	Point3D(const Point3D& pt)
		: x(pt.x), y(pt.y), z(pt.z)
	{}

	Point3D<T> operator-() const { return Point3D(-x, -y, -z); }
	
	T* data() { return std::array<T, 3>{x, y, z}.data(); }
	const T* data() const { return std::array<T, 3>{x, y, z}.data(); }

	T x;
	T y;
	T z;
};


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

template<typename... Ts>
struct typelist {};

template <typename T, typename TypeListTypes>
struct contains
{};

template <typename T, typename... Ts>
struct contains<T, typelist<Ts...>>
{
	static constexpr bool value = (std::is_same_v<T, Ts> || ...);
};

template <typename T, typename... Ts>
constexpr bool contains_v = contains<T, Ts...>::value;

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
		m(0, 3) = translation.x;
		m(1, 3) = translation.y;
		m(2, 3) = translation.z;
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

#endif // !MATH_HELPER_H