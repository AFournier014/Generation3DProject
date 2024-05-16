#include "water/WaterPlane.h"
#include "MathIncludes.h"
#include "RenderConfig.h"
#include "Shader.h"
#include "Texture.h"
#include "lights/Light.h"
#include "Renderer.h"
#include "Log.h"

constexpr auto REFLECTION_WIDTH = 512;
constexpr auto REFLECTION_HEIGHT = 512;
constexpr auto REFRACTION_WIDTH = 512;
constexpr auto REFRACTION_HEIGHT = 512;

WaterPlane::WaterPlane(const std::shared_ptr<RenderConfig> renderConfig)
	: Mesh(createVertices(), createIndices(), renderConfig)
{
	m_reflectionFrameBuffer = createReflectionFrameBuffer(m_reflectionTexture);
	m_refractionFrameBuffer = createRefractionFrameBuffer(m_refractionTexture);
}

void WaterPlane::render() {
	Mat4 M = getModelMatrix();

	m_renderConfig->shader->Bind();
	m_renderConfig->texture->Bind(0);

	m_renderConfig->dudvMap->Bind(1);

	GLCall(glActiveTexture(GL_TEXTURE0 + 2));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_reflectionTexture));
	m_renderConfig->shader->SetUniform1i("reflectionTexture", 2);

	GLCall(glActiveTexture(GL_TEXTURE0 + 3));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_refractionTexture));
	m_renderConfig->shader->SetUniform1i("refractionTexture", 3);

	m_renderConfig->shader->SetUniformMat4f("model", M);
	m_renderConfig->directionalLight->setupUniforms(m_renderConfig->shader);
	m_renderConfig->opticalProperties->setupUniforms(m_renderConfig->shader);

	GLCall(glBindVertexArray(m_vao));
	GLCall(glDrawElements(GL_TRIANGLES, GLsizei(6), GL_UNSIGNED_INT, nullptr));
	GLCall(glBindVertexArray(0));
}

std::vector<Vertexf> WaterPlane::createVertices()
{
	std::vector<Vertexf> vertices;
	vertices.emplace_back(Vector3f(-1.0f, 0.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f), Color3f(1.0f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f));
	vertices.emplace_back(Vector3f(1.0f, 0.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f), Color3f(1.0f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f));
	vertices.emplace_back(Vector3f(1.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f), Color3f(1.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f));
	vertices.emplace_back(Vector3f(-1.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f), Color3f(1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f));
	return vertices;
}

std::vector<unsigned int> WaterPlane::createIndices()
{
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	return indices;
}

GLuint WaterPlane::createReflectionFrameBuffer(unsigned int& reflectionTexture) const
{
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Création de la texture de réflexion
	glGenTextures(1, &reflectionTexture);
	glBindTexture(GL_TEXTURE_2D, reflectionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, REFLECTION_WIDTH, REFLECTION_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, reflectionTexture, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG_ERROR("Error: Reflection Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return framebuffer;
}

GLuint WaterPlane::createRefractionFrameBuffer(unsigned int& refractionTexture) const
{
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Création de la texture de réfraction
	glGenTextures(1, &refractionTexture);
	glBindTexture(GL_TEXTURE_2D, refractionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, REFRACTION_WIDTH, REFRACTION_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, refractionTexture, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG_ERROR("Error: Refraction Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return framebuffer;
}
