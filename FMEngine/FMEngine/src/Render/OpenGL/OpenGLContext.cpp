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

	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);



}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
