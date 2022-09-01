#pragma once
#include "src/Render/Buffer.h"
#include "src/Render/VertexArray.h"
#include "external/glm/glm/glm.hpp"

#include <vector>

struct Vertex
{
	glm::vec3 pos{ 0 };
	glm::vec3 norm{ 0 };
	glm::vec2 tex{ 0 };
};

// Vertex indices
struct Face
{
	uint32_t vert1{ 0 };
	uint32_t vert2{ 0 };
	uint32_t vert3{ 0 };
};

class Mesh
{
public:
	Mesh() = default;
	~Mesh();
	
	void AddVertex(const Vertex& vert);
	void AddFace(const Face& face);
	void SetTransform(const glm::mat4& transform);
	const glm::mat4& GetTransform() const;

	void GenerateRenderBuffers();
	const std::shared_ptr<VertexArray> GetVAO() const { return m_VAO; };

private:
	std::vector<Face> m_Faces;
	std::vector<Vertex> m_Vertices;
	glm::mat4 m_Transform{1};

private:
	std::shared_ptr<VertexArray> m_VAO = nullptr;
};
