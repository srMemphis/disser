#pragma once
#include "fmepch.h"
#include "src/Scene/Mesh.h"

struct aiScene;
struct aiNode;
struct aiMesh;

class Model
{
public:

	Model();
	Model(const std::string& srcPath);
	~Model();

	const std::string& GetDirectory() const { return m_Dir; };
	const std::vector<Mesh>& GetMeshes() const { return m_Meshes; };

	void AddMesh(Mesh newMesh);

private:
	std::vector<Mesh> m_Meshes;
	std::string m_Dir;

private:
	void ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& transform);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform);
};
