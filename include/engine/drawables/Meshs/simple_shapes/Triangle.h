#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Drawable.h"
#include <MathIncludes.h>
#include <array>
#include <Texture.h>
#include <Shader.h>
#include <Renderer.h>
#include <GL/glew.h>
#include <Paths.h>

class Triangle : public Drawable
{
public:
	using vertex_type = Vertex<float>;
	using Vector3f = Vector3D<float>;
	using Mat4 = Mat4<float>;

	Triangle(const vertex_type& v0, const vertex_type& v1, const vertex_type& v2, Texture const& texture)
		: m_points{ v0, v1, v2 }, m_texture(texture)
	{
		load();
	}

	void update() override
	{
		m_rotation += 0.025f;
	}

	void render(Shader& shader, const Mat4& VP, const Vector3f& cameraPositionWorld) override
	{
		Mat4 Rotation = Mat4::RotationY(m_rotation);
		Mat4 Translation = Mat4::Translation({ 0.f, 0.f, 0.f });
		Mat4 Model = Translation * Rotation;

		Mat4 MVP = VP * Model;

		shader.Bind();
		GLCall(glBindVertexArray(m_vao));
		Vector3D CameraPosition = cameraPositionWorld; // Ne sert pas ici, évite l'erreur de compilation
		shader.SetUniformMat4f("MVP", MVP);
		m_texture.Bind();
		shader.SetUniform1i("tex1", 0);

		
		GLCall(glDrawArrays(GL_TRIANGLES, 0, GLsizei(m_points.size())));

		GLCall(glBindVertexArray(0));
		shader.Unbind();
		m_texture.Unbind();
	}

private:
	void load()
	{
		GLCall(glGenVertexArrays(1, &m_vao));
		GLCall(glBindVertexArray(m_vao));

		GLCall(glGenBuffers(1, &m_vbo));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW));

		GLCall(glVertexAttribPointer(0, decltype(vertex_type::position)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), (void*)offsetof(vertex_type, position)));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, decltype(vertex_type::normal)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), (void*)offsetof(vertex_type, normal)));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(2, decltype(vertex_type::color)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), (void*)offsetof(vertex_type, color)));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(3, decltype(vertex_type::texture)::ndim, GL_FLOAT, GL_FALSE, sizeof(vertex_type), (void*)offsetof(vertex_type, texture)));
		GLCall(glEnableVertexAttribArray(3));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	std::array<vertex_type, 3> m_points;
	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	Vector3f m_position = { 0.f, 0.f, 0.f };
	Texture m_texture;
	float m_rotation = 0.f;
};

#endif // !TRIANGLE_H