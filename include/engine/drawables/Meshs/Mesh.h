#ifndef MESH_H
#define MESH_H

#include <vector>
#include <MathHelper.h>
#include <GeometryTypes.h>
#include <Drawable.h>
#include <Texture.h>

class Shader;

class Mesh : public Drawable
{
public:
	using vertex_type = Vertex<float>;
	using Point3f = Point3D<float>;
	using Mat4f = Mat4<float>;
	using Color4f = Color4<float>;

	Mesh(const std::vector<vertex_type>& vertices, const std::vector<unsigned int>& indices, const Texture& texture)
		: m_vertices(vertices)
		, m_indices(indices)
		, m_texture(texture)
	{
		load();
	}

	~Mesh() override
	{
		clearMesh();
	}

	void update() override
	{
		// TODO: Mettre à jour les données du mesh
	}

	void render(Shader& shader, const Mat4f& VP, const Point3f& cameraPositionWorld) override;

	Mat4f getModelMatrix() const;

	void rotate(const Point3f& axis, float angle);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void translate(const Point3f& translation);
	void scale(const Point3f& scale);

	void setLocation(const Point3f& location) { m_location = location; }
	Point3f getLocation() const { return m_location; }
	Point3f getScale() const { return m_scale; }
	Mat4f getRotation() const { return m_rotation; }

private:
	void load();

	void updateBuffers();

	void clearMesh() const;

	std::vector<vertex_type> m_vertices;
	std::vector<unsigned int> m_indices;
	Texture m_texture;
	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_ebo = 0;

	Point3f m_location = { 0.f, 0.f, 0.f };
	Mat4f m_rotation = Mat4f::Identity();
	Point3f m_scale = { 1.f, 1.f, 1.f };
};

#endif // !MESH_H