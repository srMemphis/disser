#include "fmepch.h"
#include "FrameBuffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLFrameBuffer.h"

FrameBuffer* FrameBuffer::Create(int32_t width, int32_t height, bool multisample)
{   
	switch (Renderer::GetAPI())
	{
	case(RendererAPI::API::None):		FME_LOG_ERROR("ERROR: Render API is None!\n"); return nullptr;
	case(RendererAPI::API::OpenGL):		return new OpenGLFrameBuffer(width, height, multisample);
	default:							FME_LOG_ERROR("ERROR: Render API is unknown!\n"); return nullptr;
	}
}
