#pragma once
#include "Event.h"

class KeyEvent: public Event
{
public:
	int GetKeyCode() const { return m_KeyCode; }
protected:
	KeyEvent(int keyCode) : m_KeyCode(keyCode) {}
	int m_KeyCode;
};
 
class KeyPressEvent : public KeyEvent
{
public:
	KeyPressEvent(int keyCode) : KeyEvent(keyCode){}
	EventType GetType() override { return EventType::KeyPress; }
};

class KeyReleaseEvent : public KeyEvent
{
public:
	KeyReleaseEvent(int keyCode) : KeyEvent(keyCode) {}
	EventType GetType() override { return EventType::KeyRelease; }
};




