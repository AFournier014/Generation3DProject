#include "engine/opengl/AltTexture.h"
#include "GL/glew.h"
#include <engine/opengl/Renderer.h>


AltTexture::AltTexture(const std::string& path)
	: m_rendererID(0), m_filePath(path), m_width(0), m_height(0)
{
	image.loadFromFile(path);
	image.flipVertically();

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	auto size = image.getSize();
	m_width = size.x;
	m_height = size.y;

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

AltTexture::~AltTexture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void AltTexture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void AltTexture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
