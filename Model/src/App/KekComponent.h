#pragma once
#include <FMEngine.h>

class KekComponent : public Component
{
public:
	KekComponent();
	~KekComponent();

	virtual void OnGuiRender() override;
private:

	float m_Time;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Shader> m_LineShader;
	std::shared_ptr<Model> m_Model;
	std::shared_ptr<Line> m_Line;

	std::shared_ptr<Camera> m_Camera;
	std::shared_ptr<MVCameraController> m_CamControll;
	std::shared_ptr<FrameBuffer> m_FrameBuffer;
	std::shared_ptr<FrameBuffer> m_MSFrameBuffer;
};

