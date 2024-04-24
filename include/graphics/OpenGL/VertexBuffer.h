#pragma once
#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, GLuint size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	GLuint m_rendererId;
};