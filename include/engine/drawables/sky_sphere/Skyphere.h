#ifndef SKYPHERE_H
#define SKYPHERE_H

#include "MathIncludes.h"
#include "Texture.h"
#include "GL/glew.h"
#include <memory>

class Shader;

class Skyphere
{
public:
	explicit Skyphere(const std::shared_ptr<Texture>& skyphereTexture);
	~Skyphere();

	void render(std::shared_ptr<Shader> shader) const;

	void initializeSkyphere();

	void release();


private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	std::shared_ptr<Texture> m_skyphereTexture;

	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
};

#endif // !SKYPHERE_H
