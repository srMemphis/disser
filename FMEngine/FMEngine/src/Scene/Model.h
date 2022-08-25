#pragma once
#include "src/Scene/Mesh.h"



#include <vector>
#include <string>





class Texture;

struct aiScene;
struct aiNode;
struct aiMesh;

class Model
{
public:

	Model();
	Model(const std::string& srcPath);
	~Model();



private:

	std::vector<Mesh> m_Meshes;
	std::vector<Texture> m_Textures;

private:

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);


};
