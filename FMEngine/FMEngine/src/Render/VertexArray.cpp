#include "VertexArray.h"
#include "Renderer.h"
#include <iostream>
#include "OpenGL/OpenGLVertexArray.h"

VertexArray* VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None:    std::cerr << "ERROR: RendererAPI::None!\n"; return nullptr;
	case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
	}

	std::cerr << "ERROR: RendererAPI is unknown!\n";
	return nullptr;
}
