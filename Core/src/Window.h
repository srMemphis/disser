#pragma once
#include <string>

struct GLFWwindow;

class Window
{
public:

	Window();
	Window(const char* title, int width, int hight, bool vsync = true);
	~Window();

	void Update();
	GLFWwindow* getGLFWwindow() { return m_GLFWwindow; };

private:

	int m_Width = 1280;
	int m_Hight = 720;
	std::string m_Title{ "Window" };
	bool m_VSync = true;

	bool InitGLFW();
	bool InitGlad();
	bool Create();

	bool static GLFWisInit;
	bool static GladisInit;

	GLFWwindow *m_GLFWwindow;
};
