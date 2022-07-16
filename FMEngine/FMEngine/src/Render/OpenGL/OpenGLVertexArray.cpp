#include "OpenGLVertexArray.h"
#include "glad/glad.h"

OpenGLVertexArray::OpenGLVertexArray()
{
	
	glGenVertexArrays(1, &m_ArrayID);
	glBindVertexArray(m_ArrayID);

}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &m_ArrayID);
}

void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(m_ArrayID);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(m_ArrayID);
	m_VexrtexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_ArrayID);
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;

}
