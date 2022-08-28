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
	std::shared_ptr<Model> m_Model;

	std::shared_ptr<FPSCamera> m_Camera;
	std::shared_ptr<CameraController> m_CamControll;
	std::shared_ptr<FrameBuffer> m_FrameBuffer;

};

