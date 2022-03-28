#pragma once
#include "Event.h"

class MouseButtonEvent : public Event
{
public:
	int GetButton() const { return m_Button; }

protected:
	MouseButtonEvent(int button)
		: m_Button(button) {}
	int m_Button;
};

class MousePressEvent : public MouseButtonEvent
{
public:
	MousePressEvent(int button)
		: MouseButtonEvent(button) {}
	EventType GetType() override { return EventType::MousePress; }
};

class MouseReleaseEvent : public MouseButtonEvent
{
public:
	MouseReleaseEvent(int button)
		: MouseButtonEvent(button) {}
	EventType GetType() override { return EventType::MouseRelease; }
};

class MouseScrollEvent : public Event
{
public:
	MouseScrollEvent(float xoffset, float yoffset)
		: m_XOffset(xoffset), m_YOffset(yoffset) {}

	EventType GetType() override { return EventType::MouseScroll; }
	float GetXOffset() const { return m_XOffset; }
	float GetYOffset() const { return m_YOffset; }

private:
	float m_XOffset, m_YOffset;
};

class MouseMoveEvent : public Event
{
public:
	MouseMoveEvent(float posx, float posy)
		: m_PosX(posx), m_PosY(posy) {}

	EventType GetType() override { return EventType::MouseMove; }
	float GetPosX() const { return m_PosX; }
	float GetPosY() const { return m_PosY; }

private:
	float m_PosX, m_PosY;
};
