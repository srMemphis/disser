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
	WindowResizeEvent(int width, int height)
		: m_Width(width), m_Height(height) {}

	EventType GetType() override { return EventType::WindowResize; }
	int GetWidth() const { return m_Width; }
	int GetHight() const { return m_Height; }

private:
	int m_Width, m_Height;
};
