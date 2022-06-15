#include "src/Core/Component.h"
#include "src/Events/EventManager.h"

#include <memory>
#include <functional>

Component::Component()
{
	// Mouse events
	std::shared_ptr<EventListener> OnMouseMooveListener = std::make_shared<EventListener>(std::bind(&Component::OnMouseMoove, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::MouseMove, OnMouseMooveListener);

	std::shared_ptr<EventListener> OnMousePressListener = std::make_shared<EventListener>(std::bind(&Component::OnMousePress, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::MousePress, OnMousePressListener);

	std::shared_ptr<EventListener> OnMouseReleaseListener = std::make_shared<EventListener>(std::bind(&Component::OnMouseRelease, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::MouseRelease, OnMouseReleaseListener);

	std::shared_ptr<EventListener> OnMouseScrollListener = std::make_shared<EventListener>(std::bind(&Component::OnMouseScroll, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::MouseScroll, OnMouseScrollListener);

	// keyboard events
	std::shared_ptr<EventListener> OnKeyPressListener = std::make_shared<EventListener>(std::bind(&Component::OnKeyPress, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::KeyPress, OnKeyPressListener);

	std::shared_ptr<EventListener> OnKeyReleaseListener = std::make_shared<EventListener>(std::bind(&Component::OnKeyRelease, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::KeyRelease, OnKeyReleaseListener);

	// window events
	std::shared_ptr<EventListener> OnWindowCloseListener = std::make_shared<EventListener>(std::bind(&Component::OnWindowClose, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::WindowClose, OnWindowCloseListener);

	std::shared_ptr<EventListener> OnWindowResizeListener = std::make_shared<EventListener>(std::bind(&Component::OnWindowResize, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::WindowResize, OnWindowResizeListener);
}

Component::~Component()
{
}

void Component::OnGuiRender()
{
}

void Component::OnAttach()
{
}

void Component::OnDetach()
{
}

void Component::OnMousePress(Event& event)
{
	//MousePressEvent& myEvent = dynamic_cast<MousePressEvent&>(event);
}

void Component::OnMouseRelease(Event& event)
{
	//MouseReleaseEvent& myEvent = dynamic_cast<MouseReleaseEvent&>(event);
}

void Component::OnMouseMoove(Event& event)
{
	//MouseMoveEvent& myEvent = dynamic_cast<MouseMoveEvent&>(event);
}

void Component::OnMouseScroll(Event& event)
{
	//MouseScrollEvent& myEvent = dynamic_cast<MouseScrollEvent&>(event);
}

void Component::OnKeyPress(Event& event)
{
	//KeyPressEvent& myEvent = dynamic_cast<KeyPressEvent&>(event);
}

void Component::OnKeyRelease(Event& event)
{
	//KeyReleaseEvent& myEvent = dynamic_cast<KeyReleaseEvent&>(event);
}

void Component::OnWindowClose(Event& event)
{
	//WindowCloseEvent& myEvent = dynamic_cast<WindowCloseEvent&>(event);
}

void Component::OnWindowResize(Event& event)
{
	//WindowResizeEvent& myEvent = dynamic_cast<WindowResizeEvent&>(event);
}
