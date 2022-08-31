#include "MVCameraController.h"

#include "src/Events/MouseEvents.h"
#include <algorithm>
#include <iostream>

MVCameraController::MVCameraController(const std::shared_ptr<MVCamera>& camera)
{
	m_Camera = camera;
	m_OnMouseClickListener = std::make_shared<EventListener>(std::bind(&MVCameraController::OnMouseClick, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::MousePress, m_OnMouseClickListener);
	m_OnMouseScrollListener = std::make_shared<EventListener>(std::bind(&MVCameraController::OnMouseScroll, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::MouseScroll, m_OnMouseScrollListener);
}

MVCameraController::~MVCameraController()
{
	m_OnMouseClickListener->SetActive(false);
	m_OnMouseScrollListener->SetActive(false);
}

void MVCameraController::SetCamera(std::shared_ptr<MVCamera> camera)
{
	m_Camera = camera;
}

void MVCameraController::SetActive(bool active)
{
	if (m_Active == false && active == true)
	{
		// Retrieving initial mouse position
		m_LastMousePos = Input::GetMousePosition();
	}
	m_Active = active;
}

void MVCameraController::SetTranslationSpeed(float_t translationSpeed)
{
	m_TranslationSpeed = translationSpeed;
}

void MVCameraController::SetRotationSpeed(glm::vec2 rotationSpeed)
{
	m_RotationSpeed = rotationSpeed;
}

void MVCameraController::Update(float_t timestep)
{
	if (m_Active)
	{
		glm::vec2 newmousepos = Input::GetMousePosition();
		glm::vec2 dmousepose = (newmousepos - m_LastMousePos) * timestep;
		m_LastMousePos = newmousepos;

		m_LastKey = MouseCode::UNKNOWN;

		if (Input::IsMouseButtonPressed(m_KeyPressOrder[0]))
		{
			m_LastKey = m_KeyPressOrder[0];
		}
		else if (Input::IsMouseButtonPressed(m_KeyPressOrder[1]))
		{
			m_LastKey = m_KeyPressOrder[1];
		}

		// do stuff
		switch (m_LastKey)
		{
		case MouseCode::LEFT: // rotate
		{
			m_Camera->SetPitch(m_Camera->GetPitch() - dmousepose.x * m_RotationSpeed.x);
			m_Camera->SetYaw(m_Camera->GetYaw() - dmousepose.y * m_RotationSpeed.y);
			break;
		}
		case MouseCode::RIGHT: // move
		{
			m_Camera->SetFocalPoint(m_Camera->GetFocalPoint() - m_Camera->GetRightDirection() * dmousepose.x * m_TranslationSpeed * m_Camera->GetDistance());
			m_Camera->SetFocalPoint(m_Camera->GetFocalPoint() - m_Camera->GetUpDirection() * dmousepose.y * m_TranslationSpeed * m_Camera->GetDistance());
			break;
		}
		}

		// zoom
		float_t dst = m_Camera->GetDistance() * (1 + m_ScrollOffset * m_ZoomSpeed);
		dst = dst < 0.1f ? 0.1f : dst;
		m_Camera->SetDistance(dst);
		m_ScrollOffset = 0;





		std::cout << " Position: " << m_Camera->GetPosition().x << ", " << m_Camera->GetPosition().y << ", " << m_Camera->GetPosition().z << ";\n";
		std::cout << " Target: " << m_Camera->GetFocalPoint().x << ", " << m_Camera->GetFocalPoint().y << ", " << m_Camera->GetFocalPoint().z << ";\n";
		std::cout << "Yaw: " << m_Camera->GetYaw() << "; Pitch: " << m_Camera->GetPitch() << ";\n";
		std::cout << "Distance: " << m_Camera->GetDistance() << ";\n\n";

		// update
		m_Camera->UpdateVPMatrix();

	}
}

void MVCameraController::OnMouseClick(Event& event)
{
	if (m_Active)
	{
		MousePressEvent& MCEvent = static_cast<MousePressEvent&>(event);
		MouseCode button = MCEvent.GetButton();
		if (button == MouseCode::LEFT || button == MouseCode::RIGHT)
		{
			if (button == m_KeyPressOrder[1])
			{
				std::swap(m_KeyPressOrder[0], m_KeyPressOrder[1]);
			}
		}
	}
}

void MVCameraController::OnMouseScroll(Event& event)
{
	if (m_Active)
	{
		MouseScrollEvent& MSEvent = static_cast<MouseScrollEvent&>(event);
		double_t offset = MSEvent.GetYOffset();
		m_ScrollOffset += (float_t)offset;
	}
}
