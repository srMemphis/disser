#pragma once
#include "fmepch.h"
#include "src/Events/Event.h"
#include "KeyCodes.h"

//base class
class MouseButtonEvent : public Event
{
public:
	MouseCode GetButton() const { return m_Button; }

protected:
	MouseButtonEvent(int16_t button)
		: m_Button(MouseCode(button)) {}
	MouseCode m_Button;
};

// Mouse psressed
class MousePressEvent : public MouseButtonEvent
{
public:
	MousePressEvent(int16_t button)
		: MouseButtonEvent(button) {}
	EventType GetType() override { return EventType::MousePress; }
};

// Mouse released
class MouseReleaseEvent : public MouseButtonEvent
{
public:
	MouseReleaseEvent(int16_t button)
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
