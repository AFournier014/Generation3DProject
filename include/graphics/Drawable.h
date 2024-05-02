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

	virtual load() = 0;
	virtual void update() = 0;
	virtual void render(const Mat4<T>& VP) = 0;
};

template <typename T>
struct Vertex
{
	Point3D<T> position;
	Point3D<T> normal;
	Color3<T> color;
	Point2D<T> texCoord;
};

template <typename T>
class Mesh : public Drawable<T>
{
public:
	Mesh(const std::vector<Vertex<T>>& vertices, std::vector<unsigned int>& indices)
		: m_vertices(vertices)
		, m_indices(indices)
	{
		load();
	}
	virtual ~Mesh()
	{
		clearMesh();
	}

	virtual void load() override
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex<T>), m_vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, color));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, texCoord));

		glBindVertexArray(0);
	}

	virtual void update() = 0;
	virtual void render(const Mat4<T>& VP) override
	{
		m_shader.Bind();
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void clearMesh()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
	}

protected:
	AltShader shader;

private:
	std::vector<Vertex<T>> m_vertices;
	std::vector<unsigned int> m_indices;
	GLuint m_vao, m_vbo, m_ebo;

};