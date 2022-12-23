#pragma once
#include "fmepch.h"

#include "src/Render/RendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
	virtual void Init() override;
	virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	virtual void SetClearColor(const glm::vec4& color) override;
	virtual void Clear() override;

	virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	virtual void DrawLines(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count) override;

	virtual void SetLineWidth(float width) override;

	virtual void SetPolygonFill(bool fill) override;
	virtual void EnableDepthTest(bool enable) override;
	virtual void EnableBlend(bool enable) override;
};
