#include "Window.h"
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


Window::Window()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_GLFWwindow = glfwCreateWindow(1280, 800, "window", NULL, NULL);
	if (m_GLFWwindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_GLFWwindow);

	// Iinitialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize glad\n");
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

Window::~Window()
{

	glfwTerminate();
}
