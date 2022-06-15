#pragma once

#include "src/GUI/GUIinterface.h"
#include "src/Events/KeyboardEvents.h"
#include "src/Events/MouseEvents.h"
#include "src/Events/WindowEvents.h"

class Component : public GUIinterface
{
public:
	Component();
	virtual ~Component();

	//GUI
	virtual void OnGuiRender();
	
	//????
	virtual void OnAttach();
	virtual void OnDetach();

	//Events
	virtual void OnMousePress(Event& event);
	virtual void OnMouseRelease(Event& event);
	virtual void OnMouseMoove(Event& event);
	virtual void OnMouseScroll(Event& event);

	virtual void OnKeyPress(Event& event);
	virtual void OnKeyRelease(Event& event);

	virtual void OnWindowClose(Event& event);
	virtual void OnWindowResize(Event& event);
};
