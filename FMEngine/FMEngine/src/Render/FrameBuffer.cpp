#include "FrameBuffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLFrameBuffer.h"

FrameBuffer* FrameBuffer::Create(int32_t width, int32_t height)
{   
	switch (Renderer::GetAPI())
	{
	case(RendererAPI::API::None):		std::cerr << "ERROR: Render API is None!\n"; return nullptr;
	case(RendererAPI::API::OpenGL):		return new OpenGLFrameBuffer(width, height);
	default:							std::cerr << "ERROR: Render API is unknown!\n"; return nullptr;
	}
}
