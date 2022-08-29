#include "CameraController.h"
#include "src/Events/KeyboardEvents.h"
#include <algorithm>
#include <iostream>

// square root of 1/2 
const float CameraController::SQRT05 = 0.70710678f;

CameraController::CameraController(std::shared_ptr<FPSCamera> camera)
{
	m_Camera = camera;
	m_OnKeyPressedListener = std::make_shared<EventListener>(std::bind(&CameraController::OnKeyPressed, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::KeyPress, m_OnKeyPressedListener);
}

CameraController::~CameraController()
{
	m_OnKeyPressedListener->SetActive(false);
}

void CameraController::SetCamera(std::shared_ptr<FPSCamera> camera)
{
	m_Camera = camera;
}

void CameraController::SetActive(bool active)
{	
	if (m_Active == false && active == true)
	{	
		// Retrieving initial mouse position
		m_LastMousePos = Input::GetMousePosition();
	}
	m_Active = active;
}

void CameraController::SetTranslationSpeed(float translationSpeed)
{
	m_TranslationSpeed = translationSpeed;
}

void CameraController::SetRotationSpeed(float yawSpeed, float pitchSpeed)
{
	m_RotationSpeed = { yawSpeed, pitchSpeed };
}

void CameraController::SetRotationSpeed(glm::vec2 rotationSpeed)
{
	m_RotationSpeed = rotationSpeed;
}

void CameraController::Update(float timestep)
{
	if (m_Active)
	{
		// rotate camera
		glm::vec2 newmousepos = Input::GetMousePosition();
		glm::vec2 dmousepose = (newmousepos - m_LastMousePos) * timestep;
		m_Camera->Turn(dmousepose.x*m_RotationSpeed.x, dmousepose.y* m_RotationSpeed.y);
		m_LastMousePos = newmousepos;

		// moove camera
		m_LastKeys = {KeyCode::UNKNOWN, KeyCode::UNKNOWN};
		int count = 0;
		for (KeyCode key : m_KeyPressOrder)
		{
			if (count != 2)
			{
				if (Input::IsKeyPressed(key))
				{
					m_LastKeys[count] = key;
					count++;
				}
			}
		}
		
		if (m_LastKeys[0] == KeyCode::W)
		{
			switch (m_LastKeys[1])
			{
			case(KeyCode::A): m_Camera->Move(glm::normalize(m_Camera->GetFront() - m_Camera->GetRight()) * m_TranslationSpeed * timestep); break; // front left
			case(KeyCode::D): m_Camera->Move(glm::normalize(m_Camera->GetFront() + m_Camera->GetRight()) * m_TranslationSpeed * timestep); break; // front right
			default:		  m_Camera->Move(m_Camera->GetFront() * m_TranslationSpeed * timestep);                                        break; // front
			}
		}
		
		if (m_LastKeys[0] == KeyCode::A)
		{
			switch (m_LastKeys[1])
			{
			case(KeyCode::W): m_Camera->Move(glm::normalize(m_Camera->GetFront() - m_Camera->GetRight()) * m_TranslationSpeed * timestep);    break; // front left
			case(KeyCode::S): m_Camera->Move(-(glm::normalize(m_Camera->GetFront() + m_Camera->GetRight())) * m_TranslationSpeed * timestep); break; // back left
			default:		  m_Camera->Move(-m_Camera->GetRight() * m_TranslationSpeed * timestep);                                          break; // left
			}
		}

		if (m_LastKeys[0] == KeyCode::S)
		{
			switch (m_LastKeys[1])
			{
			case(KeyCode::A): m_Camera->Move(-(glm::normalize(m_Camera->GetFront() + m_Camera->GetRight())) * m_TranslationSpeed * timestep); break; // back left
			case(KeyCode::D): m_Camera->Move(glm::normalize(m_Camera->GetRight() - m_Camera->GetFront()) * m_TranslationSpeed * timestep);    break; // back right
			default:		  m_Camera->Move(-m_Camera->GetFront() * m_TranslationSpeed * timestep);                                          break; // back
			}
		}

		if (m_LastKeys[0] == KeyCode::D)
		{
			switch (m_LastKeys[1])
			{
			case(KeyCode::W): m_Camera->Move(glm::normalize(m_Camera->GetFront() + m_Camera->GetRight()) * m_TranslationSpeed * timestep); break; // front right
			case(KeyCode::S): m_Camera->Move(glm::normalize(m_Camera->GetRight() - m_Camera->GetFront()) * m_TranslationSpeed * timestep); break; // back right
			default:		  m_Camera->Move(m_Camera->GetRight() * m_TranslationSpeed * timestep);                                        break; // right
			}
		}
		
		//if (Input::IsKeyPressed(KeyCode::SPACE))
		//	m_Camera->Move(m_Camera->GetUp() * m_TranslationSpeed * timestep);  // Up
		//if (Input::IsKeyPressed(KeyCode::C))
		//	m_Camera->Move(-m_Camera->GetUp() * m_TranslationSpeed * timestep); // Down

	}
}

void CameraController::OnKeyPressed(Event& event)
{
	KeyPressEvent& keyEvent = static_cast<KeyPressEvent&>(event);
	KeyCode key = keyEvent.GetKeyCode();
	if (key == KeyCode::W || key == KeyCode::A || key == KeyCode::S || key == KeyCode::D)
	{	
		// put pressed key in first position
		auto it = std::find(m_KeyPressOrder.begin(), m_KeyPressOrder.end(), key);
		m_KeyPressOrder.splice(
			m_KeyPressOrder.begin(),    // destination position
			m_KeyPressOrder,			// source list
			it);						// source position
	}
}
