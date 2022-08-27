#include "Model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <cassert>
#include <iostream>

Model::Model()
{
}

Model::Model(const std::string& srcPath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(srcPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals |aiProcess_JoinIdenticalVertices);
	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		std::cerr << "Error loading model at" + srcPath + "\n" + importer.GetErrorString();
		assert(false);
	}

	m_Dir = srcPath.substr(0, srcPath.find_last_of("/"));

	ProcessNode(scene->mRootNode, scene);

}

Model::~Model()
{
}

void Model::AddMesh(Mesh newMesh)
{
	m_Meshes.push_back(newMesh);
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
	Mesh outputMesh;

	// vertex
	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex outputVertex;

		outputVertex.pos = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
		outputVertex.norm = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

		if (mesh->mTextureCoords[0])
		{
			outputVertex.tex = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
		}

		outputMesh.AddVertex(outputVertex);
	}

	// index
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		Face outputFace {
			mesh->mFaces[i].mIndices[0],
			mesh->mFaces[i].mIndices[1],
			mesh->mFaces[i].mIndices[2],
		};

		outputMesh.AddFace(outputFace);
	}

	// TODO: load textures

	// Generate render buffers
	outputMesh.GenerateRenderBuffers();

	return outputMesh;
}
