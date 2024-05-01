#pragma once
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>

class AltTexture
{
public:
	AltTexture(const std::string& path);
	~AltTexture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	GLuint m_rendererID;
	std::string m_filePath;
	sf::Image image;
	int m_width, m_height;
};