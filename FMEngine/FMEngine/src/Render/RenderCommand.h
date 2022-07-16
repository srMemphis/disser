#pragma once
#include "src/Render/RendererAPI.h"
#include "src/Render/OpenGL/OpenGLRendererAPI.h"

class RenderCommand
{
public:
	static void Init()
	{
		s_RenderAPI->Init();
	}

	static void SetClearColor()
	{
		s_RenderAPI->SetClearColor();
	}

	static void Clear()
	{
		s_RenderAPI->Clear();
	}

	static void DrawIndexed()
	{
		s_RenderAPI->DrawIndexed();
	}

	static void DrawLines()
	{
		s_RenderAPI->DrawIndexed();
	}

	static void SetLineWidth()
	{
		s_RenderAPI->SetLineWidth();
	}

private:

	static RendererAPI *s_RenderAPI;

};

RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRendererAPI();    // FIXME
