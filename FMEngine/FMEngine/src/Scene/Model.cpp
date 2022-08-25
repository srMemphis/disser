#include "Model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <cassert>

Model::Model()
{
}

Model::Model(const std::string& srcPath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(srcPath, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		assert(false && "Error loading model " && srcPath.c_str() && importer.GetErrorString());
	}





}

Model::~Model()
{
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// process parent node
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));

	}

	// process all child nodes
	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{

	for()
	{
	}





	return Mesh();
}
