#include "Line.h"

Line::Line()
	: m_Size(0), m_Color(1)
{
}

Line::Line(std::vector<glm::vec3> vertecies, glm::vec4 color)
	: m_Color(color), m_Vertices(vertecies)
{
	m_Size = m_Vertices.size();
}

Line::~Line()
{
}

const std::vector<glm::vec3>& Line::GetData()
{
	return m_Vertices;
}

const glm::vec3& Line::GetVertex(uint32_t index)
{
	return m_Vertices.at(index);
}

const glm::vec4& Line::GetColor()
{
	return m_Color;
}

uint32_t Line::GetSize()
{
	return m_Size;
}

void Line::AddPoint(const glm::vec3& point)
{
	m_Vertices.push_back(point);
	m_Size++;
}

void Line::SetPoint(const glm::vec3& point, uint32_t index)
{
	m_Vertices.at(index) = point;
}

void Line::SetData(const std::vector<glm::vec3>& vertices)
{
	m_Vertices = vertices;
	m_Size = m_Vertices.size();
}

void Line::SetColor(const glm::vec4& color)
{
	m_Color = color;
}

void Line::Clear()
{
	m_Vertices.clear();
	m_Size = 0;
}

void Line::GenerateRenderBuffers()
{
	m_VAO.reset(VertexArray::Create());

	std::shared_ptr<VertexBuffer> VBO;
	VBO.reset(VertexBuffer::Create((float*)m_Vertices.data(), sizeof(float) * 3 * m_Size));
	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" }
	};
	VBO->SetLayout(layout);
	m_VAO->AddVertexBuffer(VBO);

	m_VAO->SetIndexBuffer(nullptr);

}

std::shared_ptr<VertexArray> Line::GetVAO()
{
	return m_VAO;
}
