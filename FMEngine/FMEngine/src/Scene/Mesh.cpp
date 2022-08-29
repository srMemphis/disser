#include "Mesh.h"

Mesh::~Mesh()
{
}

void Mesh::AddVertex(const Vertex& vert)
{
	m_Vertices.push_back(vert);
}

void Mesh::AddFace(const Face& face)
{
	m_Faces.push_back(face);
}

void Mesh::SetTransform(const glm::mat4& transform)
{
	m_Transform = transform;
}

const glm::mat4& Mesh::GetTransform() const
{
	return m_Transform;
}

void Mesh::GenerateRenderBuffers()
{
	m_VAO.reset(VertexArray::Create());

	std::shared_ptr<VertexBuffer> VBO;
	VBO.reset(VertexBuffer::Create((float*)m_Vertices.data(), sizeof(Vertex) * (uint32_t)m_Vertices.size()));
	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float3, "a_Norm" },
		{ ShaderDataType::Float2, "a_TexCoord" }
	};
	VBO->SetLayout(layout);
	m_VAO->AddVertexBuffer(VBO);

	std::shared_ptr<IndexBuffer> EBO;
	EBO.reset(IndexBuffer::Create((uint32_t*)m_Faces.data(),(uint32_t)m_Faces.size() * 3));
	m_VAO->SetIndexBuffer(EBO);

}
