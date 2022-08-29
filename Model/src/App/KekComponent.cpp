#include "KekComponent.h"
#include <iostream>

KekComponent::KekComponent()
{
	RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

	m_Camera.reset(new MVCamera({ 1.09159, 0.721172, -0.511793 }, { 0.0378288, 0.393665, -0.0402839 }));
	m_Camera->SetPos({ 0,0,2 });

	m_CamControll.reset(new MVCameraController(std::dynamic_pointer_cast<MVCamera>(m_Camera)));
	m_CamControll->SetTranslationSpeed(0.1);

	// model loading
	m_Model.reset(new Model("assets/models/MS3D/jeep1.ms3d"));

	m_FrameBuffer.reset(FrameBuffer::Create(512, 512));

	m_Shader.reset(Shader::Create("Common", "assets/Shaders/Common.vert", "assets/Shaders/Common.frag"));
	m_Time = Time::CurTime();

}

KekComponent::~KekComponent()
{
}

void KekComponent::OnGuiRender()
{
	ImGui::DockSpaceOverViewport();
	ImGui::Begin("Viewport");
	bool focus = ImGui::IsWindowFocused();

	// Yellow is content region min/max
	ImVec2 vMin = ImGui::GetWindowContentRegionMin();
	ImVec2 vMax = ImGui::GetWindowContentRegionMax();

	vMin.x += ImGui::GetWindowPos().x;
	vMin.y += ImGui::GetWindowPos().y;
	vMax.x += ImGui::GetWindowPos().x;
	vMax.y += ImGui::GetWindowPos().y;

	ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));


	ImVec2 viewportSize = { vMax.x - vMin.x, vMax.y - vMin.y };


	m_FrameBuffer->Resize((int32_t)viewportSize.x, (int32_t)viewportSize.y);
	m_FrameBuffer->Bind();
	RenderCommand::Clear();

	m_Camera->SetView(viewportSize.x, viewportSize.y);

	float timestep = Time::CurTime() - m_Time;
	m_Time = Time::CurTime();
	m_CamControll->SetActive(focus);
	m_CamControll->Update(timestep);

	Renderer::BeginScene(m_Camera);

	glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	transform = glm::scale(transform, glm::vec3(0.1, 0.1, 0.1));
	Renderer::Submit(m_Shader, m_Model, transform);

	Renderer::EndScene();


	m_FrameBuffer->Unbind();


	ImGui::Image((void*)m_FrameBuffer->GetTextureID(), ImVec2(viewportSize.x, viewportSize.y));
	ImGui::End();
	ImGui::ShowMetricsWindow();

}
