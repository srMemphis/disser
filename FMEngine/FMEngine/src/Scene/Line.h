#pragma once
#include "external/glm/glm/glm.hpp"
#include "src/Render/Buffer.h"
#include "src/Render/VertexArray.h"

#include <vector>
#include <memory>

class Line
{
public:

	Line();
	Line(std::vector<glm::vec3> vertecies, glm::vec4 color);
	~Line();

	// Accessors //
	const std::vector<glm::vec3>& GetData();
	const glm::vec3& GetVertex(uint32_t index);
	const glm::vec4& GetColor();
	uint32_t GetSize();

	// Modifiers //
	void AddPoint(const glm::vec3& point);
	void SetPoint(const glm::vec3& point, uint32_t index);
	void SetData(const std::vector<glm::vec3>& vertices);
	void SetColor(const glm::vec4& color);
	void Clear();

	void GenerateRenderBuffers();
	std::shared_ptr<VertexArray> GetVAO();
private:
	uint32_t m_Size;
	glm::vec4 m_Color;
	std::vector<glm::vec3> m_Vertices;

private:
	std::shared_ptr<VertexArray> m_VAO = nullptr;
};
