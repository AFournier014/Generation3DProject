#pragma once

#include <vector>
#include <GL/glew.h>
#include "MathHelper.h"
#include "GeometryTypes.h"
#include "OpenGL/AltShader.h"

template <typename T>
class Drawable
{
public:
	virtual ~Drawable() {}

	virtual void load() = 0;
	virtual void update() = 0;
	virtual void render(const Mat4<T>& VP, Point3D<T> cameraPositionWorld) = 0;
};

template <typename T>
class Mesh : public Drawable<T>
{
public:
	Mesh(const std::vector<Vertex<T>>& vertices, const std::vector<unsigned int>& indices,
		const std::string& vertexPath = "", const std::string& fragmentPath = "")
		: m_vertices(vertices)
		, m_indices(indices)
		, m_vao(0), m_vbo(0)
		, shader(vertexPath, fragmentPath)
	{
	}

	~Mesh()
	{
		clearMesh();
	}

	virtual void load() override
	{
		GLCall(glGenVertexArrays(1, &m_vao));
		GLCall(glBindVertexArray(m_vao));

		GLCall(glGenBuffers(1, &m_vbo));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW));

		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, position)));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, normal)));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, color)));
		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, texture)));

		GLCall(glBindVertexArray(0));
	}

	virtual void update() override
	{
	}

	virtual void render(const Mat4<T>& VP, Point3D<T> cameraPositionWorld) override
	{
		// Temporaire propriétés optiques de l'objet
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

		shader.Bind();
		GLCall(glBindVertexArray(m_vao));

		shader.SetUniformMat4f("MVP", MVP);
		shader.SetUniformMat4f("model", M);
		shader.SetUniform3f("cameraPositionWorld", cameraPositionWorld);
		shader.SetUniform1f("material.ambient", opticalProperties.ambient);
		shader.SetUniform1f("material.diffuse", opticalProperties.diffuse);
		shader.SetUniform1f("material.specular", opticalProperties.specular);
		shader.SetUniform1f("material.shininess", opticalProperties.shininess);
		shader.SetUniform3f("light.direction", directionalLight.direction);
		shader.SetUniform4f("light.color", directionalLight.color.r, directionalLight.color.g, directionalLight.color.b, directionalLight.color.a);

		//glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, GLsizei(m_vertices.size())));
		GLCall(glBindVertexArray(0));
	}

	void clearMesh()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}

	void setShaderPaths(const std::string& vertexPath, const std::string& fragmentPath)
	{
		shader = AltShader(vertexPath, fragmentPath);
	}

	float alpha = 0.f;
	float beta = 0.f;

protected:
	AltShader shader;

private:
	std::vector<Vertex<T>> m_vertices;
	std::vector<unsigned int> m_indices;
	GLuint m_vao, m_vbo;
};