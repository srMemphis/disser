#include "fmepch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "OpenGL/OpenGLVertexArray.h"


VertexArray* VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None:    FME_LOG_ERROR("ERROR: RendererAPI::None!\n"); return nullptr;
	case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
	}

	FME_LOG_ERROR("ERROR: RendererAPI is unknown!\n");
	return nullptr;
}
