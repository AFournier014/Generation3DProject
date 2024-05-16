#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#include <MathIncludes.h>
#include <Drawable.h>
#include <memory>
#include <RenderConfig.h>

class Shader;

class Mesh : public Drawable
{
public:
	explicit Mesh(const std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices, const std::shared_ptr<RenderConfig> renderConfig)
		: m_renderConfig(renderConfig)
		, m_vertices(std::vector<Vertexf>(vertices))
		, m_indices(std::vector<unsigned int>(indices))
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

	void render() override;

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

	void setLocation(const Vector3f& location) { m_renderConfig->transform.position = location; }
	Vector3f getLocation() const { return m_renderConfig->transform.position; }
	Vector3f getScale() const { return m_renderConfig->transform.scale; }
	Mat4f getRotation() const { return m_renderConfig->transform.rotation; }

protected:
	std::shared_ptr<RenderConfig> m_renderConfig;

	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_ebo = 0;

private:
	void load();

	void updateBuffers();

	void clearMesh() const;

	std::vector<Vertexf> m_vertices;
	std::vector<unsigned int> m_indices;


};

#endif // !MESH_H