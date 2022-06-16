#include "src/Core/App.h"


#include <iostream>
#include <exception>

App* App::s_Instance = nullptr;

App::App()
{
	// There should be only one App
	if (s_Instance)
	{
		std::cerr << "ERROR: Application already exists!\n";
		std::terminate();
	}
	s_Instance = this;

	m_window = new Window();
	m_gui.Init();

	// setup Window close event listener
	std::shared_ptr<EventListener> OnWindowCloseListener = std::make_shared<EventListener>(std::bind(&App::OnWindowClose, this, std::placeholders::_1));
	m_EventManager.AddListener(EventType::WindowClose, OnWindowCloseListener);
}

App::~App()
{
	delete m_window;
}

void App::Run()
{
	while (m_Running)
	{	
		// polling and procecing events
		m_EventManager.ProcessEvents();







		// rendering gui
		m_gui.Begin();
		for (auto component : m_ComponentList)
			component->OnGuiRender();
		m_gui.End();



		m_window->Update();

	}
}

void App::OnWindowClose(Event& event)
{
	m_Running = false;
}
