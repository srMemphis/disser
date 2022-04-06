#pragma once

#include "Window.h"
#include "Events/EventManager.h"


class App
{
public:
	App();
	~App();

	void Run();

private:

	Window* m_window;
	EventManager& m_EventManager = EventManager::GetInstance();
	bool m_Running = true;

	// events
	void SetupEvents();

	void OnMouseMoove(Event& event);
	void OnMouseClick(Event& event);
	void OnWindowClose(Event& event);

};
