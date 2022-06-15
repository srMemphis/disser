#pragma once
#include "src/Events/Event.h"

// Base class
class KeyEvent: public Event
{
public:
	int GetKeyCode() const { return m_KeyCode; }
protected:
	KeyEvent(int keyCode) : m_KeyCode(keyCode) {}
	int m_KeyCode;
};
 
// Key pressed
class KeyPressEvent : public KeyEvent
{
public:
	KeyPressEvent(int keyCode) : KeyEvent(keyCode){}
	EventType GetType() override { return EventType::KeyPress; }
};

// Key released
class KeyReleaseEvent : public KeyEvent
{
public:
	KeyReleaseEvent(int keyCode) : KeyEvent(keyCode) {}
	EventType GetType() override { return EventType::KeyRelease; }
};
