#include "sky_sphere/Skyphere.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

Skyphere::Skyphere(const std::shared_ptr<Texture>& skyphereTexture)
	: m_skyphereTexture(skyphereTexture)
{
	initializeSkyphere();
}

Skyphere::~Skyphere()
{
	GLCall(glDeleteVertexArrays(1, &m_vao));
	GLCall(glDeleteBuffers(1, &m_vbo));
}

void Skyphere::render(std::shared_ptr<Shader> shader) const
{
	GLCall(glDepthFunc(GL_LEQUAL)); // Pour que le ciel soit toujours visible

	shader->Bind();
	shader->SetUniformMat4f("model", Mat4f::Translation({ 0.f, 0.f, 0.f }) * Mat4f::Scale({ 10000.f, 10000.f, 10000.f }));
	m_skyphereTexture->Bind(0);

	GLCall(glBindVertexArray(m_vao));
	GLCall(glDrawElements(GL_TRIANGLES, GLsizei(m_indices.size()), GL_UNSIGNED_INT, 0));

	GLCall(glBindVertexArray(0));
	m_skyphereTexture->Unbind();
	shader->Unbind();

	GLCall(glDepthFunc(GL_LESS)); // Rétablir la fonction de profondeur par défaut
}

void Skyphere::initializeSkyphere()
{
	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;


	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		{
			float xSegment = static_cast<float>(x) / static_cast<float>(X_SEGMENTS);
			float ySegment = static_cast<float>(y) / static_cast<float>(Y_SEGMENTS);
			float xPos = std::cos(xSegment * 2.f * static_cast<float>(M_PI)) * std::sin(ySegment * static_cast<float>(M_PI));
			float yPos = std::cos(ySegment * static_cast<float>(M_PI));
			float zPos = std::sin(xSegment * 2.f * static_cast<float>(M_PI)) * std::sin(ySegment * static_cast<float>(M_PI));

			m_vertices.push_back(xPos);
			m_vertices.push_back(yPos);
			m_vertices.push_back(zPos);
			m_vertices.push_back(xSegment);
			m_vertices.push_back(ySegment);
		}
	}

	for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x < X_SEGMENTS; ++x)
		{
			m_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			m_indices.push_back(y * (X_SEGMENTS + 1) + x);
			m_indices.push_back(y * (X_SEGMENTS + 1) + x + 1);

			m_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			m_indices.push_back(y * (X_SEGMENTS + 1) + x + 1);
			m_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x + 1);
		}
	}

	GLCall(glGenVertexArrays(1, &m_vao));
	GLCall(glGenBuffers(1, &m_vbo));
	GLCall(glGenBuffers(1, &m_ebo));

	GLCall(glBindVertexArray(m_vao));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glBindVertexArray(0));
}

void Skyphere::release()
{
	GLCall(glDeleteVertexArrays(1, &m_vao));
	GLCall(glDeleteBuffers(1, &m_vbo));
	GLCall(glDeleteBuffers(1, &m_ebo));
	m_vertices.clear();
	m_indices.clear();
}
