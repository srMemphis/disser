#pragma once

#include "Window.h"

class App
{
public:
	App();
	~App();

	void Run();

private:

	Window* m_window;
	bool m_Running = true;

};
