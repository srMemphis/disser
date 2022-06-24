#pragma once

struct BufferLayout
{

};

class OpenGLVertexBuffer
{
public:
	OpenGLVertexBuffer(float* vertices, unsigned int size);
	~OpenGLVertexBuffer();

	void Bind();
	void Unbind();

	void SetData(const void* data, unsigned int size);

	const BufferLayout& GetLayout() { return m_Layout; }
	void SetLayout(const BufferLayout& layout);

private:
	unsigned int m_BufferID;
	BufferLayout m_Layout;
};

class OpenGLIndexBuffer
{
public:
	OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
	~OpenGLIndexBuffer();

	void Bind();
	void Unbind();

	unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_BufferID;
	unsigned int m_Count;
};
