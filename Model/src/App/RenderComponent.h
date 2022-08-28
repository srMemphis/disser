#pragma once
#include <FMEngine.h>

class RenderComponent : public Component
{
public:
	RenderComponent();
	virtual ~RenderComponent();

	virtual void OnGuiRender() override;
private:
	float m_Time;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<VertexArray> m_VertexArray;

	std::shared_ptr<FPSCamera> m_Camera;
	std::shared_ptr<CameraController> m_CamControll;
	std::shared_ptr<FrameBuffer> m_FrameBuffer;
};
