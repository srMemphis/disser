#pragma once
#include <memory>
#include "external/glm/glm/glm.hpp"
#include "src/Render/VertexArray.h"


class RendererAPI
{
public:
	enum class API
	{
		None = 0, OpenGL = 1
	};
public:
	virtual ~RendererAPI() = default;

	virtual void Init() = 0;
	virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
	virtual void SetClearColor(const glm::vec4& color) = 0;
	virtual void Clear() = 0;

	virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
	virtual void DrawLines(const std::shared_ptr<VertexArray>& vertexArraym, uint32_t count) = 0;

	virtual void SetLineWidth(float width) = 0;
	
	virtual void SetPolygonFill(bool fill) = 0;
	virtual void EnableDepthTest(bool enable) = 0;
	virtual void EnableBlend(bool enable) = 0;

	static API GetAPI() { return s_API; }
	static RendererAPI* Create();
private:
	static API s_API;
};
