#include "Renderer.h"
#include "RenderCommand.h"
#include "src/Scene/Mesh.h"

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

void Renderer::Init()
{
	RenderCommand::Init();
}

void Renderer::Shutdown()
{
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	//RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene(const std::shared_ptr<Camera>& camera)
{
	s_SceneData->ViewProjectionMatrix = camera->GetVPMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
	shader->Bind();
	shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	shader->SetMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Model>& model , const glm::mat4& transform)
{
	shader->Bind();
	shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	
	for (const Mesh& mesh : model->GetMeshes())
	{
		shader->SetMat4("u_Transform", mesh.GetTransform() * transform);
		mesh.GetVAO()->Bind();
		RenderCommand::DrawIndexed(mesh.GetVAO());
	}

}
