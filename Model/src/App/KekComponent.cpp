#include "KekComponent.h"
#include <iostream>

KekComponent::KekComponent()
{
	RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

	m_Camera.reset(new MVCamera({ 0,0,0 }, 2.87645, -4.19934, 0.5));

	m_CamControll.reset(new MVCameraController(std::dynamic_pointer_cast<MVCamera>(m_Camera)));
	m_CamControll->SetTranslationSpeed(0.1);

	// model loading
	m_Model.reset(new Model("assets/sample/source/CCars09-10-sport.3ds"));
	m_Line.reset(new Line(std::vector<glm::vec3>{ glm::vec3{0,0,0}, glm::vec3{10, 10, 10} }, { 0.7, 0.2, 0.2, 1 }));
	m_Line->GenerateRenderBuffers();




	m_FrameBuffer.reset(FrameBuffer::Create(512, 512, false));
	m_MSFrameBuffer.reset(FrameBuffer::Create(512, 512, true));
	m_MSFrameBuffer->SetSamples(4);

	//m_Shader.reset(Shader::Create("Common", "assets/Shaders/Common.vert", "assets/Shaders/Common.frag"));
	m_Shader.reset(Shader::Create("Diffuse", "assets/Shaders/Diffuse.vert", "assets/Shaders/Diffuse.frag"));
	m_LineShader.reset(Shader::Create("Line", "assets/Shaders/Line.vert", "assets/Shaders/Line.frag"));

	m_Time = Time::CurTime(); 

	RenderCommand::EnableBlend(true);
	RenderCommand::EnableDepthTest(true);
	RenderCommand::SetPolygonFill(true);
	RenderCommand::SetLineWidth(3);
}

KekComponent::~KekComponent()
{
}

void KekComponent::OnGuiRender()
{
	ImGui::DockSpaceOverViewport();
	ImGui::Begin("Viewport");
	bool focus = ImGui::IsWindowFocused();
	bool hover = ImGui::IsWindowHovered();

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
	m_MSFrameBuffer->Resize((int32_t)viewportSize.x, (int32_t)viewportSize.y);
	m_MSFrameBuffer->Bind();
	RenderCommand::Clear();

	m_Camera->SetView(viewportSize.x, viewportSize.y);
	m_Camera->UpdateVPMatrix();
	float timestep = Time::CurTime() - m_Time;
	m_Time = Time::CurTime();
	m_CamControll->SetActive(focus && hover);
	m_CamControll->Update(timestep);

	Renderer::BeginScene(m_Camera);

	glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	transform = glm::scale(transform, glm::vec3(0.1, 0.1, 0.1));
	Renderer::Submit(m_Shader, m_Model, transform);
	Renderer::SubmitLine(m_LineShader, m_Line, transform);


	Renderer::EndScene();

	m_FrameBuffer->BlitFrom(m_MSFrameBuffer);
	m_FrameBuffer->Unbind();

	ImGui::Image((void*)m_FrameBuffer->GetTextureID(), ImVec2(viewportSize.x, viewportSize.y));
	ImGui::End();
	ImGui::ShowMetricsWindow();

}
