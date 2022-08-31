#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
	:m_WindowHandle(windowHandle)
{
}

OpenGLContext::~OpenGLContext()
{
}

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	// Iinitialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize glad\n");
	}
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
