#pragma once
#include "src/Scene/Mesh.h"

#include <vector>
#include <string>

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
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};
