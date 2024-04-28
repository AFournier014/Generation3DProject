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
		, m_programId(0)
		m_texture(TEXTURES_PATH + "texture.png")
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

		Mat4<float> trans = Mat4<float>::Translation({ 2.f, 0.f, -5.f });

		Mat4<float> M = trans * rot;

		// Matrice de transformation
		Mat4<float> MVP = VP * M;

		GLCall(glUseProgram(m_programId));
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
	Point3D<T> normal;
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

		// Points du cube et couleurs associées (en dur)
		Point3D<T> P000 = { -1, -1, -1 }; Point3D<T> P100 = { +1, -1, -1 }; Point3D<T> P010 = { -1, +1, -1 }; Point3D<T> P110 = { +1, +1, -1 };
		Point3D<T> P001 = { -1, -1, +1 }; Point3D<T> P101 = { +1, -1, +1 }; Point3D<T> P011 = { -1, +1, +1 }; Point3D<T> P111 = { +1, +1, +1 };
		Color3<T> c100 = { +1, +0, +0 }; Color3<T> c010 = { +0, +1, +0 }; Color3<T> c001 = { +0, +0, +1 };
		Color3<T> c011 = { +0, +1, +1 }; Color3<T> c101 = { +1, +0, +1 }; Color3<T> c110 = { +1, +1, +0 };
		Point3D<T> nxn = { -1, 0, 0 }; Point3D<T> nyn = { 0, -1, 0 }; Point3D<T> nzn = { 0, 0, -1 };
		Point3D<T> nxp = { +1, 0, 0 }; Point3D<T> nyp = { 0, +1, 0 }; Point3D<T> nzp = { 0, 0, +1 };

		// Vertex du cube
		using vt = vertex_type;
		static std::array<vertex_type, 36> points = {
		   vt{P000, nzn, c100}, vt{P100, nzn, c100}, vt{P110, nzn, c100}, vt{P000, nzn, c100}, vt{P110, nzn, c100}, vt{P010, nzn, c100}
		 , vt{P001, nzp, c011}, vt{P101, nzp, c011}, vt{P111, nzp, c011}, vt{P001, nzp, c011}, vt{P111, nzp, c011}, vt{P011, nzp, c011}
		 , vt{P000, nyn, c010}, vt{P100, nyn, c010}, vt{P101, nyn, c010}, vt{P000, nyn, c010}, vt{P101, nyn, c010}, vt{P001, nyn, c010}
		 , vt{P010, nyp, c101}, vt{P110, nyp, c101}, vt{P111, nyp, c101}, vt{P010, nyp, c101}, vt{P111, nyp, c101}, vt{P011, nyp, c101}
		 , vt{P000, nxn, c001}, vt{P010, nxn, c001}, vt{P011, nxn, c001}, vt{P000, nxn, c001}, vt{P011, nxn, c001}, vt{P001, nxn, c001}
		 , vt{P100, nxp, c110}, vt{P110, nxp, c110}, vt{P111, nxp, c110}, vt{P100, nxp, c110}, vt{P111, nxp, c110}, vt{P101, nxp, c110}
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
		GLCall(glEnableVertexAttribArray(0)); // Position
		GLCall(glVertexAttribPointer(1, decltype(vertex_type::normal)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position)));
		GLCall(glEnableVertexAttribArray(1)); // Normale
		GLCall(glVertexAttribPointer(2, decltype(vertex_type::color)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position) + sizeof(vertex_type::normal)));
		GLCall(glEnableVertexAttribArray(2)); // Couleur
	}

	void Update()
	{
	}

	void render(const Mat4<float>& VP, Point3D<T> cameraPositionWorld)
	{
		// Propriétés optiques du cube
		struct OpticalProperties
		{
			float ambient = 0.3f;
			float diffuse = 0.7f;
			float specular = 70.f;
			float shininess = 1.f;
		} opticalProperties;

		// Propriétés de la lumière
		struct DirectionalLight
		{
			Point3D<T> direction = { 0.f, -1.f, 0.f };
			Color4<T> color = { 1.f, 1.f, 1.f, 1.f };
		} directionalLight;

		Mat4<float> rot = Mat4<float>::RotationX(beta) * Mat4<float>::RotationY(alpha);

		Mat4<float> trans = Mat4<float>::Translation({ -2.f, 0.f, -5.f });

		Mat4<float> M = trans * rot;
		Mat4<float> MVP = VP * M;

		GLCall(glUseProgram(m_programId));
		GLCall(glBindVertexArray(m_vao));

		GLCall(glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data()));

		GLuint modelLocation = glGetUniformLocation(m_programId, "model");
		glUniformMatrix4fv(modelLocation, 1, 0, M.data());

		GLuint cameraPositionWorldLoc = glGetUniformLocation(m_programId, "cameraPositionWorld");
		glUniform3fv(cameraPositionWorldLoc, 1, reinterpret_cast<float*>(&cameraPositionWorld));

		GLuint ambient = glGetUniformLocation(m_programId, "material.ambient");
		glUniform1fv(ambient, 1, &opticalProperties.ambient);

		GLuint diffuse = glGetUniformLocation(m_programId, "material.diffuse");
		glUniform1fv(diffuse, 1, &opticalProperties.diffuse);

		GLuint specular = glGetUniformLocation(m_programId, "material.specular");
		glUniform1fv(specular, 1, &opticalProperties.specular);

		GLuint shininess = glGetUniformLocation(m_programId, "material.shininess");
		glUniform1fv(shininess, 1, &opticalProperties.shininess);

		GLuint lightLocation = glGetUniformLocation(m_programId, "light.direction");
		glUniform3fv(lightLocation, 1, reinterpret_cast<float*>(&directionalLight.direction));

		GLuint lightColor = glGetUniformLocation(m_programId, "light.color");
		glUniform4fv(lightColor, 1, reinterpret_cast<float*>(& directionalLight.color));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	float alpha = 0.f;
	float beta = 0.f;

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_programId;
};