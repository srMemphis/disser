#include "RenderComponent.h"
#include <iostream>

RenderComponent::RenderComponent()
{
	RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

	m_Camera.reset(new FPSCamera());
	m_Camera->SetPos({0,0,2});

	m_CamControll.reset(new CameraController(m_Camera));
	m_CamControll->SetTranslationSpeed(1.);

	m_VertexArray.reset(VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" }
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader.reset(Shader::Create("Common", "Shaders/Common.vert", "Shaders/Common.frag"));
	m_Time = Time::CurTime();






	m_FrameBuffer.reset(FrameBuffer::Create(512, 512));




}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::OnGuiRender()
{	


	ImGui::DockSpaceOverViewport();
	ImGui::Begin("Viewport");

	// Yellow is content region min/max
	ImVec2 vMin = ImGui::GetWindowContentRegionMin();
	ImVec2 vMax = ImGui::GetWindowContentRegionMax();

	vMin.x += ImGui::GetWindowPos().x;
	vMin.y += ImGui::GetWindowPos().y;
	vMax.x += ImGui::GetWindowPos().x;
	vMax.y += ImGui::GetWindowPos().y;

	ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));


	ImVec2 viewportSize = { vMax.x - vMin.x, vMax.y - vMin.y };


	m_FrameBuffer->Resize(viewportSize.x, viewportSize.y);
	m_FrameBuffer->Bind();
	RenderCommand::Clear();

	m_Camera->SetAspectRatio(viewportSize.x / viewportSize.y);

	float timestep = Time::CurTime() - m_Time;
	m_Time = Time::CurTime();
	m_CamControll->Update(timestep);

	Renderer::BeginScene(*m_Camera);

	glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(0,0,0));
	Renderer::Submit(m_Shader, m_VertexArray, transform);

	Renderer::EndScene();


	m_FrameBuffer->Unbind();


	ImGui::Image((void*)m_FrameBuffer->GetTextureID(), ImVec2(viewportSize.x, viewportSize.y));
	ImGui::End();
	ImGui::ShowMetricsWindow();






}
