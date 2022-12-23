#include "fmepch.h"
#include "RendererAPI.h"

#include "OpenGL/OpenGLRendererAPI.h"


RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

RendererAPI* RendererAPI::Create()
{
	switch (s_API)
	{
	case RendererAPI::API::None:    FME_LOG_ERROR("ERROR: RendererAPI::None!\n"); return nullptr;
	case RendererAPI::API::OpenGL:  return new OpenGLRendererAPI();
	}

	FME_LOG_ERROR("ERROR: RendererAPI is unknown!\n");
	return nullptr;
}
