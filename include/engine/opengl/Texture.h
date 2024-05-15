#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics/Image.hpp>
#include <filesystem>

class Texture
{
public:
	explicit Texture(const std::filesystem::path& path);

	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	void Release() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline std::filesystem::path GetFilePath() const { return m_filePath; }

private:
	unsigned int m_rendererID;
	std::filesystem::path m_filePath;
	sf::Image image;
	int m_width = 0;
	int m_height = 0;
};

#endif // !TEXTURE_H