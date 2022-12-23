#include "fmepch.h"
#include "src/Scene/FPSCamera.h"
#include "src/Events/InputPolling.h"
#include "src/Events/EventManager.h"

class CameraController
{
public:
	CameraController() = default;
	CameraController(std::shared_ptr<FPSCamera> camera);
	~CameraController();

	void SetCamera(std::shared_ptr<FPSCamera> camera);
	void SetActive(bool active);

	void SetTranslationSpeed(float translationSpeed);
	void SetRotationSpeed(float yawSpeed, float pitchSpeed);
	void SetRotationSpeed(glm::vec2 rotationSpeed);

	void Update(float timestep);

private:
	float m_TranslationSpeed{ 1.f };
	glm::vec2 m_RotationSpeed{ 1.f, 1.f };   // Yaw, Pitch

	glm::vec2 m_LastMousePos{ 0.f, 0.f };

	std::list<KeyCode> m_KeyPressOrder{ KeyCode::W, KeyCode::A, KeyCode::S, KeyCode::D };
	std::array<KeyCode, 2> m_LastKeys{ KeyCode::UNKNOWN, KeyCode::UNKNOWN };

	bool m_Active = false;

	std::shared_ptr<FPSCamera> m_Camera = nullptr;

private:
	void OnKeyPressed(Event& event);
	std::shared_ptr<EventListener> m_OnKeyPressedListener = nullptr;

private:
	static const float SQRT05;
};
