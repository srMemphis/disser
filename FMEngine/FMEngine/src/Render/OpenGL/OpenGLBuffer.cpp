#include "OpenGLBuffer.h"

#include "glad/glad.h"

// ----------------------------------------------------------------------------
// ------------------- Vertex BUffer ------------------------------------------
// ----------------------------------------------------------------------------

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
{
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void OpenGLVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void OpenGLVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void* data, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
{
	// FIXME
}

// ----------------------------------------------------------------------------
// ------------------- Index BUffer -------------------------------------------
// ----------------------------------------------------------------------------

OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
	: m_Count(count)
{
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void OpenGLIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void OpenGLIndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
