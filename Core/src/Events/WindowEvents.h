#pragma once
#include "Event.h"

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {}
	EventType GetType() { return EventType::WindowClose; }
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(int width, int hight)
		: m_Width(width), m_Hight(hight) {}

	EventType GetType() { return EventType::WindowResize; }
	int GetWidth() const { return m_Width; }
	int GetHight() const { return m_Hight; }

private:
	int m_Width, m_Hight;
};
