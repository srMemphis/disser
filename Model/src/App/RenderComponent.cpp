#include "RenderComponent.h"
#include <iostream>

RenderComponent::RenderComponent()
{
	RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

	m_Camera.reset(new Camera());
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
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::OnGuiRender()
{	
	if (Input::IsKeyPressed(KeyCode::F))
		std::cout << "PRESS F\n";

	RenderCommand::Clear();

	float hight = App::GetInstance().GetWindow()->GetHight();
	float width = App::GetInstance().GetWindow()->GetWidth();
	m_Camera->SetAspectRatio(width/ hight);
	//std::cout << width << "/" << hight << '\n';

	float timestep = Time::CurTime() - m_Time;
	m_Time = Time::CurTime();
	m_CamControll->Update(timestep);
	
	Renderer::BeginScene(*m_Camera);

	glm::mat4 transform = glm::mat4(1);
	Renderer::Submit(m_Shader, m_VertexArray, transform);

	Renderer::EndScene();

}
