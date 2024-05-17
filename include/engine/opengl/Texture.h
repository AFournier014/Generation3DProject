#ifndef TEXTURE_H
#define TEXTURE_H

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
	uint8_t* m_data = nullptr;
	int m_width = 0;
	int m_height = 0;
	int m_channels = 0;
};

#endif // !TEXTURE_H