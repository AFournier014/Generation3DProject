#ifndef COLOR_H
#define COLOR_H

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

#endif // !COLOR_H