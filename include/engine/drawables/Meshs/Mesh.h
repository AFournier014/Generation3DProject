#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#include <MathIncludes.h>
#include <Drawable.h>
#include <Texture.h>
#include <memory>

class Shader;

class Mesh : public Drawable
{
public:
	explicit Mesh(const std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices, const std::shared_ptr<Texture> texture)
		: m_vertices(std::vector<Vertexf>(vertices))
		, m_indices(std::vector<unsigned int>(indices))
		, m_texture(texture)
	{
		load();
	}

	~Mesh() override
	{
		m_vertices.clear();
		m_indices.clear();
	}

	void update() override
	{
		// Nothing to do
	}

	void render(std::shared_ptr<Shader> shader) override;

	void release() override
	{
		clearMesh();
	}

	Mat4f getModelMatrix() const;

	void rotate(const Vector3f& axis, float angle);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void translate(const Vector3f& translation);
	void scale(const Vector3f& scale);

	void setLocation(const Vector3f& location) { m_location = location; }
	Vector3f getLocation() const { return m_location; }
	Vector3f getScale() const { return m_scale; }
	Mat4f getRotation() const { return m_rotation; }

private:
	void load();

	void updateBuffers();

	void clearMesh() const;

	std::vector<Vertexf> m_vertices;
	std::vector<unsigned int> m_indices;
	std::shared_ptr<Texture> m_texture;
	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_ebo = 0;

	Vector3f m_location = { 0.f, 0.f, 0.f };
	Mat4f m_rotation = Mat4f::Identity();
	Vector3f m_scale = { 1.f, 1.f, 1.f };
};

#endif // !MESH_H