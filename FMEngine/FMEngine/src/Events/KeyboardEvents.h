#pragma once
#include "fmepch.h"
#include "src/Events/Event.h"
#include "KeyCodes.h"

// Base class
class KeyEvent: public Event
{
public:
	KeyCode GetKeyCode() const { return m_KeyCode; }
protected:
	KeyEvent(int16_t keyCode) : m_KeyCode(KeyCode(keyCode)) {}
	KeyCode m_KeyCode;
};

// Key pressed
class KeyPressEvent : public KeyEvent
{
public:
	KeyPressEvent(int16_t keyCode) : KeyEvent(keyCode){}
	EventType GetType() override { return EventType::KeyPress; }
};

// Key released
class KeyReleaseEvent : public KeyEvent
{
public:
	KeyReleaseEvent(int16_t keyCode) : KeyEvent(keyCode) {}
	EventType GetType() override { return EventType::KeyRelease; }
};
