#include "Model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <cassert>
#include <iostream>

glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4* from)
{
	glm::mat4 to(1);

	to[0][0] = (float_t)from->a1; to[0][1] = (float_t)from->b1;  to[0][2] = (float_t)from->c1; to[0][3] = (float_t)from->d1;
	to[1][0] = (float_t)from->a2; to[1][1] = (float_t)from->b2;  to[1][2] = (float_t)from->c2; to[1][3] = (float_t)from->d2;
	to[2][0] = (float_t)from->a3; to[2][1] = (float_t)from->b3;  to[2][2] = (float_t)from->c3; to[2][3] = (float_t)from->d3;
	to[3][0] = (float_t)from->a4; to[3][1] = (float_t)from->b4;  to[3][2] = (float_t)from->c4; to[3][3] = (float_t)from->d4;

	return to;
}

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

	ProcessNode(scene->mRootNode, scene, glm::mat4(1));
}

Model::~Model()
{
}

void Model::AddMesh(Mesh newMesh)
{
	m_Meshes.push_back(newMesh);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parantTransform)
{
	glm::mat4 childTransform = parantTransform * aiMatrix4x4ToGlm(&node->mTransformation);

	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene, childTransform));

	}

	// process all child nodes
	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, childTransform);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& nodeTransform)
{
	std::unique_ptr<Mesh> outputMesh = std::make_unique<Mesh>();

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

		outputMesh->AddVertex(outputVertex);
	}

	// index
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		Face outputFace {
			mesh->mFaces[i].mIndices[0],
			mesh->mFaces[i].mIndices[1],
			mesh->mFaces[i].mIndices[2],
		};

		outputMesh->AddFace(outputFace);
	}

	// TODO: load textures
	// texture code goes here! haha, never

	// transform;
	outputMesh->SetTransform(nodeTransform);

	// Generate render buffers
	outputMesh->GenerateRenderBuffers();

	return *outputMesh;
}
