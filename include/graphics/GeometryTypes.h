#pragma once

#include <array>
#include <GL/glew.h>
#include <Shader.h>
#include <MathHelper.h>
#include <utils/Paths.h>
#include <iostream>
#include <direct.h>
#include <MathHelper.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <Paths.h>
#include <OpenGL/Renderer.h>

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
struct Vertex // possible de templater pour gerer opengl en sachant ce qu'il contient (pas tout compris)
{
	Point3D<T> position;
	Point2D<T> texture;
};

struct Texture
{
	explicit Texture(const std::filesystem::path& path)
	{
		GLCall(glGenTextures(1, &m_texture));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));

		sf::Image image;
		image.loadFromFile(path.generic_string());

		auto size = image.getSize();

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	}

	void Bind()
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
	}

private:
	GLuint m_texture;
};

template <typename T>
class Triangle
{
public:
	using vertex_type = Vertex<T>;

	Triangle(const vertex_type& p0, const vertex_type& p1, const vertex_type& p2)
		: m_points{ p0, p1, p2 } // Initialisation de m_points, doit etre possible de faire autrement sans stocker le point
		, m_vao(0)
		, m_vbo(0)
		, m_programId(0),
		m_texture(TEXTURES_PATH + "texture2.png")
	{
		load();
	}

	~Triangle() {}

	void load()
	{
		GLCall(glGenVertexArrays(1, &m_vao));
		GLCall(glBindVertexArray(m_vao));

		GLCall(glGenBuffers(1, &m_vbo));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW));

		// Shader path à changer
		std::string vertPath = SHADER_PATH + "triangle.vert";
		std::string fragPath = SHADER_PATH + "triangle.frag";

		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, vertPath.c_str()}, // Chemins des fichiers potentiellement erroné
			{ GL_FRAGMENT_SHADER, fragPath.c_str() },
			{ GL_NONE, nullptr }
		};

		m_programId = Shader::LoadShaders(shaders);
		GLCall(glUseProgram(m_programId));

		/*
		* WARNING: Ne fonctionne que pour les types T = float, a changer pour les autres types
		*/

		GLCall(glVertexAttribPointer(0, decltype(vertex_type::position)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0));
		GLCall(glEnableVertexAttribArray(0));

		GLCall(glVertexAttribPointer(1, decltype(vertex_type::texture)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position)));
		GLCall(glEnableVertexAttribArray(1));
	}

	void Update()
	{
		m_angle += 0.025f;
	}

	void render(const Mat4<float>& VP)
	{
		Mat4<float> rot = Mat4<float>::RotationY(m_angle);

		Mat4<float> trans = Mat4<float>::Translation({ 0.f, 0.f, -5.f });

		Mat4<float> M = trans * rot;

		// Matrice de transformation
		Mat4<float> MVP = VP * M;

		GLCall(glBindVertexArray(m_vao));
		GLCall(GLuint mvpLocation = glGetUniformLocation(m_programId, "MVP"));
		GLCall(glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, MVP.data()));

		m_texture.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, int(m_points.size()))); // C'est pas fou le cast en int ici, TODO: fix le cast
	}

private:
	std::array<vertex_type, 3> m_points;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_programId;
	float m_angle = 0.f;
	Texture m_texture;
};

template<typename T>
struct CubeVertex
{
	Point3D<T> position;
	Color3<T> color;
};

template <typename T>
class Cube
{
public:
	using vertex_type = CubeVertex<T>;

	Cube()
		: m_vao(0)
		, m_vbo(0)
		, m_programId(0)
	{
		load();
	}

	~Cube() {}

	void load()
	{
		GLCall(glGenVertexArrays(1, &m_vao));
		GLCall(glBindVertexArray(m_vao));

		GLCall(glGenBuffers(1, &m_vbo));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

		// Allocate storage size units of OpenGL
		// Copy data from client to server

		static std::array<vertex_type, 36> points = {
			vertex_type{ {-1.f, -1.f, -1.f}, {1.f, 0.f, 0.f}}, vertex_type{ {+1.f, -1.f, -1.f}, {1., 0., 0.}}, vertex_type{ {+1.f, +1.f, -1.f}, {1., 0., 0.}}
		  , vertex_type{ {-1.f, -1.f, -1.f}, {1.f, 0.f, 0.f}}, vertex_type{ {+1.f, +1.f, -1.f}, {1., 0., 0.}}, vertex_type{ {-1.f, +1.f, -1.f}, {1., 0., 0.}}
		  , vertex_type{ {-1.f, -1.f, +1.f}, {0.f, 1.f, 1.f}}, vertex_type{ {+1.f, -1.f, +1.f}, {0., 1., 1.}}, vertex_type{ {+1.f, +1.f, +1.f}, {0., 1., 1.}}
		  , vertex_type{ {-1.f, -1.f, +1.f}, {0.f, 1.f, 1.f}}, vertex_type{ {+1.f, +1.f, +1.f}, {0., 1., 1.}}, vertex_type{ {-1.f, +1.f, +1.f}, {0., 1., 1.}}

		  , vertex_type{ {-1.f, -1.f, -1.f}, {0.f, 1.f, 0.f}}, vertex_type{ {+1.f, -1.f, -1.f}, {0., 1., 0.}}, vertex_type{ {+1.f, -1.f, +1.f}, {0., 1., 0.}}
		  , vertex_type{ {-1.f, -1.f, -1.f}, {0.f, 1.f, 0.f}}, vertex_type{ {+1.f, -1.f, +1.f}, {0., 1., 0.}}, vertex_type{ {-1.f, -1.f, +1.f}, {0., 1., 0.}}
		  , vertex_type{ {-1.f, +1.f, -1.f}, {1.f, 0.f, 1.f}}, vertex_type{ {+1.f, +1.f, -1.f}, {1., 0., 1.}}, vertex_type{ {+1.f, +1.f, +1.f}, {1., 0., 1.}}
		  , vertex_type{ {-1.f, +1.f, -1.f}, {1.f, 0.f, 1.f}}, vertex_type{ {+1.f, +1.f, +1.f}, {1., 0., 1.}}, vertex_type{ {-1.f, +1.f, +1.f}, {1., 0., 1.}}

		  , vertex_type{ {-1.f, -1.f, -1.f}, {0.f, 0.f, 1.f}}, vertex_type{ {-1.f, +1.f, -1.f}, {0., 0., 1.}}, vertex_type{ {-1.f, +1.f, +1.f}, {0., 0., 1.}}
		  , vertex_type{ {-1.f, -1.f, -1.f}, {0.f, 0.f, 1.f}}, vertex_type{ {-1.f, +1.f, +1.f}, {0., 0., 1.}}, vertex_type{ {-1.f, -1.f, +1.f}, {0., 0., 1.}}
		  , vertex_type{ {+1.f, -1.f, -1.f}, {1.f, 1.f, 0.f}}, vertex_type{ {+1.f, +1.f, -1.f}, {1., 1., 0.}}, vertex_type{ {+1.f, +1.f, +1.f}, {1., 1., 0.}}
		  , vertex_type{ {+1.f, -1.f, -1.f}, {1.f, 1.f, 0.f}}, vertex_type{ {+1.f, +1.f, +1.f}, {1., 1., 0.}}, vertex_type{ {+1.f, -1.f, +1.f}, {1., 1., 0.}}
		};

		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(points), points.data(), GL_STATIC_DRAW));

		std::string vertPath = SHADER_PATH + "cube.vert";
		std::string fragPath = SHADER_PATH + "cube.frag";

		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, vertPath.c_str() },
			{ GL_FRAGMENT_SHADER, fragPath.c_str() },
			{ GL_NONE, nullptr }
		};

		m_programId = Shader::LoadShaders(shaders);
		GLCall(glUseProgram(m_programId));

		// /!\ Attention, ca ne marche que si T=float : c'est un peu dommage.
		GLCall(glVertexAttribPointer(0, decltype(vertex_type::position)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, decltype(vertex_type::color)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position)));
		GLCall(glEnableVertexAttribArray(1));
	}

	void Update()
	{
		m_angle += 0.025f;
	}

	void render(const Mat4<float>& VP)
	{
		Mat4<float> rot = Mat4<float>::RotationY(m_angle);

		Mat4<float> trans = Mat4<float>::Translation({ 0.f, 0.f, -5.f });

		Mat4<float> M = trans * rot;
		Mat4<float> MVP = VP * M;

		GLCall(glBindVertexArray(m_vao));

		GLCall(GLuint mvpLocation = glGetUniformLocation(m_programId, "MVP"));
		ASSERT(mvpLocation != -1);

		GLCall(glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data()));

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	}

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_programId;
	float m_angle = 0.f;
};