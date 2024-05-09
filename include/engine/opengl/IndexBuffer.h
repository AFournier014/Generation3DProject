#pragma once
#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, GLuint count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline GLuint GetCount() const { return m_count; }

private:
	GLuint m_rendererId;
	GLuint m_count;
};