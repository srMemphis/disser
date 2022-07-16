#include "Buffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLBuffer.h"
#include <iostream>

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{

	switch (Renderer::GetAPI())
	{
	case(RendererAPI::API::None):		std::cerr << "ERROR: Render API is None!\n"; return nullptr;
	case(RendererAPI::API::OpenGL):		return new OpenGLVertexBuffer(vertices, size);
	default:							std::cerr << "ERROR: Render API is unknown!\n"; return nullptr;
	}
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (Renderer::GetAPI())
	{
	case(RendererAPI::API::None):		std::cerr << "ERROR: Render API is None!\n"; return nullptr;
	case(RendererAPI::API::OpenGL):		return new OpenGLIndexBuffer(indices, count);
	default:							std::cerr << "ERROR: Render API is unknown!\n"; return nullptr;
	}
}
