#pragma once

enum class EventType
{
	None,
	KeyPress, KeyRelease,
	MousePress, MouseRelease, MouseScroll, MouseMove,
	WindowClose, WindowResize
};

class Event
{
public:
	virtual ~Event() {}
	virtual EventType GetType() { return EventType::None; };
protected:
	bool m_Handled = false;
};
