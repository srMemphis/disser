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
	uint32_t vert1;
	uint32_t vert2;
	uint32_t vert3;
};

class Mesh
{
public:
	Mesh() = default;
	~Mesh();
	
	void AddVertex(const Vertex& vert);
	void AddFace(const Face& face);

	void GenerateRenderBuffers();
	const std::shared_ptr<VertexArray> GetVAO() const { return m_VAO; };

private:
	std::vector<Face> m_Faces;
	std::vector<Vertex> m_Vertices;

private:
	std::shared_ptr<VertexArray> m_VAO = nullptr;
};
