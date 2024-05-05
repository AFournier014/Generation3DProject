#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const class VertexBuffer& vb, const class VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_rendererId;
};