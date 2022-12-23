#pragma once
#include "fmepch.h"

#include "src/GUI/GUI.h"
#include "src/Core/Window.h"
#include "src/Events/EventManager.h"
#include "src/Core/ComponentList.h"

// App is an singleton
class App
{
public:

	App();
	virtual ~App();
	void Run();

	static App& GetInstance() { return *s_Instance; }
	Window* GetWindow() { return m_window; }

protected:

	App(App const&) = delete;
	void operator=(App const&) = delete;
	
	Window* m_window;                                            // window
	bool m_Running = true;	                                     // running flag
	EventManager& m_EventManager = EventManager::GetInstance();  // event
	ComponentList m_ComponentList;	                             // app components
	
	virtual void OnWindowClose(Event& event);

private:
	static App* s_Instance;
	GUI m_gui;
};
