#include "OpenGLContext.h"
#include <iostream>

#include "external/glad/include/glad/glad.h"
#include "external/GLFW/include/GLFW/glfw3.h"

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
	:m_WindowHandle(windowHandle)
{
}

OpenGLContext::~OpenGLContext()
{
	delete m_WindowHandle;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
