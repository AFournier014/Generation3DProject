#include "meshs/Mesh.h"
#include "Shader.h"
#include <MathIncludes.h>
#include "Renderer.h"
#include "GL/glew.h"

using Mat4f = Mat4<float>;

void Mesh::render(std::shared_ptr<Shader> shader)
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
		Vector3f direction = { 0.f, -1.f, 0.f };
		Color4f color = { 1.f, 1.f, 1.f, 1.f };
	} directionalLight;

	Mat4 M = getModelMatrix();

	shader->Bind();
	shader->SetUniformMat4f("model", M);
	shader->SetUniform1f("material.ambient", opticalProperties.ambient);
	shader->SetUniform1f("material.diffuse", opticalProperties.diffuse);
	shader->SetUniform1f("material.specular", opticalProperties.specular);
	shader->SetUniform1f("material.shininess", opticalProperties.shininess);
	shader->SetUniform3f("light.direction", directionalLight.direction);
	shader->SetUniform4f("light.color", directionalLight.color.r, directionalLight.color.g, directionalLight.color.b, directionalLight.color.a);

	GLCall(glBindVertexArray(m_vao));
	GLCall(glDrawElements(GL_TRIANGLES, GLsizei(m_indices.size()), GL_UNSIGNED_INT, nullptr));
	GLCall(glBindVertexArray(0));
}

Mat4f Mesh::getModelMatrix() const
{
	return Mat4f::Translation(m_location) * m_rotation * Mat4f::Scale(m_scale);
}

void Mesh::rotate(const Vector3f& axis, float angle)
{
	Vector3f normalizedAxis = axis;
	normalizedAxis.Normalize();
	Mat4f rotation = Mat4f::Rotation(Mat4f::Identity(), normalizedAxis, angle);
	Mat4f toOrigin = Mat4f::Translation(-m_location);
	Mat4f fromOrigin = Mat4f::Translation(m_location);

	m_rotation = fromOrigin * rotation * toOrigin * m_rotation;
}

void Mesh::rotateX(float angle)
{
	Mat4f m = Mat4f::RotationX(angle);
	m_rotation = m * m_rotation;
}

void Mesh::rotateY(float angle)
{
	Mat4f m = Mat4f::RotationY(angle);
	m_rotation = m * m_rotation;
}

void Mesh::rotateZ(float angle)
{
	Mat4f m = Mat4f::RotationZ(angle);
	m_rotation = m * m_rotation;
}

void Mesh::translate(const Vector3f& translation)
{
	m_location += translation;
}

void Mesh::scale(const Vector3f& scale)
{
	m_scale = scale;
}

void Mesh::load()
{
	GLCall(glGenVertexArrays(1, &m_vao));
	GLCall(glGenBuffers(1, &m_vbo));
	GLCall(glGenBuffers(1, &m_ebo));

	GLCall(glBindVertexArray(m_vao));

	updateBuffers();

	GLCall(glVertexAttribPointer(0, decltype(Vertexf::position)::ndim, GL_FLOAT, GL_FALSE, sizeof(Vertexf), (void*)offsetof(Vertexf, position)));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, decltype(Vertexf::normal)::ndim, GL_FLOAT, GL_FALSE, sizeof(Vertexf), (void*)offsetof(Vertexf, normal)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(2, decltype(Vertexf::color)::ndim, GL_FLOAT, GL_FALSE, sizeof(Vertexf), (void*)offsetof(Vertexf, color)));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(3, decltype(Vertexf::texture)::ndim , GL_FLOAT, GL_FALSE, sizeof(Vertexf), (void*)offsetof(Vertexf, texture)));
	GLCall(glEnableVertexAttribArray(3));

	GLCall(glBindVertexArray(0));
}

void Mesh::updateBuffers()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertexf), nullptr, GL_STREAM_DRAW));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertexf), m_vertices.data()));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), nullptr, GL_STREAM_DRAW));
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(unsigned int), m_indices.data()));
}

void Mesh::clearMesh() const
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}