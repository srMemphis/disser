#include "App.h"
#include "Events/MouseEvents.h"
#include <iostream>
App::App()
{
	m_window = new Window();
	SetupEvents();
}

App::~App()
{
	delete m_window;
}

void App::Run()
{
	while (m_Running)
	{	
		m_EventManager.ProcessEvents();
		m_window->Update();

	}
}

void App::SetupEvents()
{

	std::shared_ptr<EventListener> OnMouseMooveListener = std::make_shared<EventListener>(std::bind(&App::OnMouseMoove, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::MouseMove, OnMouseMooveListener);

	std::shared_ptr<EventListener> OnMouseClickListener = std::make_shared<EventListener>(std::bind(&App::OnMouseClick, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::MousePress, OnMouseClickListener);

	std::shared_ptr<EventListener> OnWindowCloseListener = std::make_shared<EventListener>(std::bind(&App::OnWindowClose, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::WindowClose, OnWindowCloseListener);


}

void App::OnMouseMoove(Event& event)
{
	MouseMoveEvent& myEvent = dynamic_cast<MouseMoveEvent&>(event);
	std::cout << "Mouse mooved to: X = " << myEvent.GetPosX() << "; Y = " << myEvent.GetPosY() << std::endl;
}

void App::OnMouseClick(Event& event)
{
	MousePressEvent& myEvent = dynamic_cast<MousePressEvent&>(event);
	std::cout << "Mouse click! Button: " << myEvent.GetButton() << std::endl;
}

void App::OnWindowClose(Event& event)
{
	std::cout << "Window shood close" << std::endl;
	m_Running = false;
}
