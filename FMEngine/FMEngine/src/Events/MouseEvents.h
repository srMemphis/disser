#pragma once
#include "src/Events/Event.h"

//base class
class MouseButtonEvent : public Event
{
public:
	int GetButton() const { return m_Button; }

protected:
	MouseButtonEvent(int button)
		: m_Button(button) {}
	int m_Button;
};

// Mouse psressed
class MousePressEvent : public MouseButtonEvent
{
public:
	MousePressEvent(int button)
		: MouseButtonEvent(button) {}
	EventType GetType() override { return EventType::MousePress; }
};

// Mouse released
class MouseReleaseEvent : public MouseButtonEvent
{
public:
	MouseReleaseEvent(int button)
		: MouseButtonEvent(button) {}
	EventType GetType() override { return EventType::MouseRelease; }
};

// Mouse scrolled
class MouseScrollEvent : public Event
{
public:
	MouseScrollEvent(double xoffset, double yoffset)
		: m_XOffset(xoffset), m_YOffset(yoffset) {}

	EventType GetType() override { return EventType::MouseScroll; }
	double GetXOffset() const { return m_XOffset; }
	double GetYOffset() const { return m_YOffset; }

private:
	double m_XOffset, m_YOffset;
};

// Mouse moved
class MouseMoveEvent : public Event
{
public:
	MouseMoveEvent(double posx, double posy)
		: m_PosX(posx), m_PosY(posy) {}

	EventType GetType() override { return EventType::MouseMove; }
	double GetPosX() const { return m_PosX; }
	double GetPosY() const { return m_PosY; }

private:
	double m_PosX, m_PosY;
};
