#include "fmepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLBuffer.h"

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{

	switch (Renderer::GetAPI())
	{
	case(RendererAPI::API::None):		FME_LOG_ERROR("ERROR: Render API is None!\n"); return nullptr;
	case(RendererAPI::API::OpenGL):		return new OpenGLVertexBuffer(vertices, size);
	default:							FME_LOG_ERROR("ERROR: Render API is unknown!\n"); return nullptr;
	}
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (Renderer::GetAPI())
	{
	case(RendererAPI::API::None):		FME_LOG_ERROR("ERROR: Render API is None!\n"); return nullptr;
	case(RendererAPI::API::OpenGL):		return new OpenGLIndexBuffer(indices, count);
	default:							FME_LOG_ERROR("ERROR: Render API is unknown!\n"); return nullptr;
	}
}
