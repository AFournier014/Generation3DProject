#pragma once

#include <array>

template <typename T>
class Mat4
{
public:
	Mat4()
	{
		m_coeffs.fill(0);
	}

	T& operator()(int i, int j)
	{
		return m_coeffs[i + 4 * j];
	}

	const T& operator()(int row, int col) const
	{
		return m_coeffs[row + 4 * col];
	}

	const T* data() const
	{
		return m_coeffs.data();
	}

	static Mat4<T> Identity()
	{
		Mat4<T> m;
		m(0, 0) = m(1, 1) = m(2, 2) = m(3, 3) = 1;
		return m;
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
			{
				result(row, col) += op1(row, k) * op2(k, col);
			}
		}
	}
	return result;
}