#pragma once
#include <string>
#include "src/Events/EventManager.h"
#include "src/Events/WindowEvents.h"
struct GLFWwindow;

class Window
{
public:

	Window();
	Window(const char* title, int width, int hight, bool vsync = true);
	~Window();

	void Update();
	GLFWwindow* getGLFWwindow() { return m_GLFWwindow; };
	int GetWidth() { return m_Width; }
	int GetHight() { return m_Hight; }

private:
	// window data
	int m_Width = 1280;
	int m_Hight = 720;
	std::string m_Title{ "Window" };
	bool m_VSync = true;
	GLFWwindow* m_GLFWwindow;
	
	// init
	bool InitGLFW();
	bool InitGlad();
	bool Create();

	bool static GLFWisInit;
	bool static GladisInit;

	// Events
	void SetupEventListeners();
	void OnWindowResize(Event& event);
};
