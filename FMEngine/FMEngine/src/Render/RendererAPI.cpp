#include "RendererAPI.h"
#include <iostream>
#include "OpenGL/OpenGLRendererAPI.h"

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

RendererAPI* RendererAPI::Create()
{
	switch (s_API)
	{
	case RendererAPI::API::None:    std::cerr << "ERROR: RendererAPI::None!\n"; return nullptr;
	case RendererAPI::API::OpenGL:  return new OpenGLRendererAPI();
	}

	std::cerr << "ERROR: RendererAPI is unknown!\n";
	return nullptr;
}
