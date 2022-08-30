#pragma once
#include "src/Scene/MVCamera.h"
#include "src/Events/InputPolling.h"
#include "src/Events/EventManager.h"

#include <array>
#include <memory>

class MVCameraController
{
public:
	MVCameraController() = default;
	MVCameraController(const std::shared_ptr<MVCamera>& camera);
	~MVCameraController();

	void SetCamera(std::shared_ptr<MVCamera> camera);
	void SetActive(bool active);

	void SetTranslationSpeed(float_t translationSpeed);
	void SetRotationSpeed(glm::vec2 rotationSpeed);

	void Update(float_t timestep);

private:
	float_t m_ZoomSpeed{ 0.1f };
	float_t m_TranslationSpeed{ 0.1f };
	glm::vec2 m_RotationSpeed{ 1.f, 1.f };   // Yaw, Pitch

	glm::vec2 m_LastMousePos{ 0.f, 0.f };
	float_t m_ScrollOffset{ 0 };

	std::array<MouseCode, 2> m_KeyPressOrder{ MouseCode::LEFT, MouseCode::RIGHT };
	MouseCode m_LastKey{ MouseCode::UNKNOWN };

	bool m_Active = false;

	std::shared_ptr<MVCamera> m_Camera = nullptr;

private:
	void OnMouseScroll(Event& event);
	void OnMouseClick(Event& event);
	std::shared_ptr<EventListener> m_OnMouseScrollListener = nullptr;
	std::shared_ptr<EventListener> m_OnMouseClickListener = nullptr;
};
