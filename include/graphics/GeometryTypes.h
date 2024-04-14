#pragma once

#include <array>
#include <GL/glew.h>
#include <Shader.h>
#include <MathHelper.h>
#include <utils/Paths.h>
#include <iostream>
#include <direct.h>

template <typename T>
struct Point2D
{
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
	Point3D(const T& x_ = 0, const T& y_ = 0, const T& z_ = 0)
		: x(x_), y(y_), z(z_)
	{}

	Point3D(const Point3D& pt)
		: x(pt.x), y(pt.y), z(pt.z)
	{}

	T x;
	T y;
	T z;
};

template <typename T>
struct Color3
{
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
	Point3D<T> position;
	Color4<T> color;
};

template <typename T>
class Triangle
{
public:
	using vertex_type = Vertex<T>;

	Triangle(const vertex_type& p0, const vertex_type& p1, const vertex_type& p2)
		: m_points{ p0, p1, p2 }
		, m_vao(0)
		, m_vbo(0)
		, m_programId(0)
	{
		load();
	}

	~Triangle() {}

	void load()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW);

		// Shader path à changer
		std::string vertPath = SHADER_PATH + "triangle.vert";
		std::string fragPath = SHADER_PATH + "triangle.frag";

		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, vertPath.c_str()}, // Chemins des fichiers potentiellement erroné
			{ GL_FRAGMENT_SHADER, fragPath.c_str() },
			{ GL_NONE, nullptr }
		};

		m_programId = Shader::LoadShaders(shaders);
		glUseProgram(m_programId);

		/*
		* WARNING: Ne fonctionne que pour les types T = float
		*/

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position));
		glEnableVertexAttribArray(1);
	}

	void render(const Mat4<float>& MVP)
	{
		glBindVertexArray(m_vao);
		GLuint mvpLocation = glGetUniformLocation(m_programId, "MVP");
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, MVP.data());
		glDrawArrays(GL_TRIANGLES, 0, int(m_points.size())); // C'est pas fou le cast en int ici, TODO: fix le cast
	}

private:
	std::array<Vertex<T>, 3> m_points;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_programId;
};