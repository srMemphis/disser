#pragma once
#include "src/Render/RendererAPI.h"
#include "src/Render/OpenGL/OpenGLRendererAPI.h"

class RenderCommand
{
public:
	static void Init()
	{
		s_RendererAPI->Init();
	}

	static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	static void SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	static void Clear()
	{
		s_RendererAPI->Clear();
	}

	static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	static void DrawLines(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count)
	{
		s_RendererAPI->DrawLines(vertexArray, count);
	}

	static void SetLineWidth(float width)
	{
		s_RendererAPI->SetLineWidth(width);
	}

	static void SetPolygonFill(bool fill)
	{
		s_RendererAPI->SetPolygonFill(fill);
	}

	static void EnableDepthTest(bool enable)
	{
		s_RendererAPI->EnableDepthTest(enable);
	}

	static void EnableBlend(bool enable)
	{
		s_RendererAPI->EnableBlend(enable);
	}

private:
	static RendererAPI * s_RendererAPI;
};
