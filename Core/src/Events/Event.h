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
	virtual EventType GetType() = 0;
protected:
	bool m_Handled = false;
};
