#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#include <MathHelper.h>
#include <GeometryTypes.h>
#include <Drawable.h>
#include <Texture.h>
#include <Shader.h>
#include <Renderer.h>

template <typename T>
class Mesh : public Drawable<T>
{
public:
	using vertex_type = Vertex<T>;
	using Point3D = Point3D<T>;
	using Mat4 = Mat4<T>;

	Mesh(const std::vector<vertex_type>& vertices, const std::vector<unsigned int>& indices, const Texture& texture)
		: m_vertices(vertices)
		, m_indices(indices)
		, m_texture(texture)
	{
		load();
	}

	~Mesh()
	{
		clearMesh();
	}

	void update() override
	{
		// TODO: Mettre à jour les données du mesh
	}

	void render(Shader& shader, const Mat4& VP, const Point3D& cameraPositionWorld) override
	{
		// Temporaire propriétés optiques de l'objet et de la lumière
		struct OpticalProperties
		{
			float ambient = 0.3f;
			float diffuse = 0.7f;
			float specular = 1.f;
			float shininess = 70.f;
		} opticalProperties;

		// Propriétés de la lumière directionnelle (temporaire)
		struct DirectionalLight
		{
			Point3D direction = { 0.f, -1.f, 0.f };
			Color4<T> color = { 1.f, 1.f, 1.f, 1.f };
		} directionalLight;

		Mat4 rot = Mat4::RotationX(beta) * Mat4::RotationY(alpha);

		Mat4 trans = Mat4::Translation({ 0.f, 0.f, -5.f });

		Mat4 M = trans * rot;
		Mat4 MVP = VP * M;

		shader.Bind();
		shader.SetUniformMat4f("MVP", MVP);
		shader.SetUniformMat4f("model", M);
		shader.SetUniform3f("cameraPositionWorld", cameraPositionWorld);
		shader.SetUniform1f("material.ambient", opticalProperties.ambient);
		shader.SetUniform1f("material.diffuse", opticalProperties.diffuse);
		shader.SetUniform1f("material.specular", opticalProperties.specular);
		shader.SetUniform1f("material.shininess", opticalProperties.shininess);
		shader.SetUniform3f("light.direction", directionalLight.direction);
		shader.SetUniform4f("light.color", directionalLight.color.r, directionalLight.color.g, directionalLight.color.b, directionalLight.color.a);

		GLCall(glBindVertexArray(m_vao));
		GLCall(glDrawElements(GL_TRIANGLES, GLsizei(m_indices.size()), GL_UNSIGNED_INT, nullptr));
		GLCall(glBindVertexArray(0));
	}

	void setLocation(const Point3D& location) { m_location = location; }

	Point3D getLocation() const { return m_location; }

	float alpha = 0.f;
	float beta = 0.f;

private:
	void load()
	{
		GLCall(glGenVertexArrays(1, &m_vao));
		GLCall(glGenBuffers(1, &m_vbo));
		GLCall(glGenBuffers(1, &m_ebo));

		GLCall(glBindVertexArray(m_vao));

		updateBuffers();

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), (void*)offsetof(vertex_type, position)));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), (void*)offsetof(vertex_type, normal)));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), (void*)offsetof(vertex_type, color)));
		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_type), (void*)offsetof(vertex_type, texture)));

		GLCall(glBindVertexArray(0));
	}

	void updateBuffers()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GLCall(glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex_type), nullptr, GL_STREAM_DRAW));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(vertex_type), m_vertices.data()));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), nullptr, GL_STREAM_DRAW));
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(unsigned int), m_indices.data()));
	}

	void clearMesh() const
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}

	std::vector<vertex_type> m_vertices;
	std::vector<unsigned int> m_indices;
	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_ebo = 0;
	Point3D m_location = { 0.f, 0.f, 0.f };
	Texture m_texture;
};

#endif // !MESH_H