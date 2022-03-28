#include "Window.h"
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

bool Window::GLFWisInit = false;
bool Window::GladisInit = false;

Window::Window()
{
	// init GLFW
	if (!GLFWisInit)
		GLFWisInit = InitGLFW();

	// Create Window
	Create();

	// Init Glad
	if(!GladisInit)
		GladisInit = InitGlad();

	// Dark blue background
	glClearColor(1.0f, 0.0f, 0.4f, 0.0f);
}

Window::Window(const char* title, int width, int hight, bool vsync)
{
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Update()
{
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(m_GLFWwindow);
}


bool Window::InitGLFW()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

	return true;
}

bool Window::InitGlad()
{
	// Iinitialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize glad\n");
		glfwTerminate();
		return false;
	}

	return true;
}

bool Window::Create()
{
	// Open a window and create its OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_GLFWwindow = glfwCreateWindow(m_Width, m_Hight, m_Title.c_str(), NULL, NULL);
	if (m_GLFWwindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_GLFWwindow);

	return true;
}
