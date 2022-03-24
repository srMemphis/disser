#pragma once

struct GLFWwindow;

class Window
{
public:

	Window();
	~Window();

	GLFWwindow* getGLFWwindow() { return m_GLFWwindow; };
private:

	GLFWwindow *m_GLFWwindow;
};
