#include "src/Core/Window.h"

#include <iostream>
#include <memory>
#include <functional>

#include "external/glad/include/glad/glad.h"
#include "external/GLFW/include/GLFW/glfw3.h"

#include "src/Events/EventManager.h"
#include "src/Events/WindowEvents.h"
#include "src/Events/MouseEvents.h"
#include "src/Events/KeyboardEvents.h"

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

	SetupEventListeners();
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
	glfwSwapBuffers(m_GLFWwindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

bool Window::InitGLFW()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	// GLWF hints
	//glfwWindowHint(GLFW_SAMPLES, 4);								// 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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

	m_GLFWwindow = glfwCreateWindow(m_Width, m_Hight, m_Title.c_str(), NULL, NULL);
	if (m_GLFWwindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_GLFWwindow);


	// seting up GLFW callback function. input events generation

	glfwSetKeyCallback(m_GLFWwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				EventManager::GetInstance().PushEvent(new KeyPressEvent(key));
			}
			else if (action == GLFW_RELEASE)
			{
				EventManager::GetInstance().PushEvent(new KeyPressEvent(key));
			}
		});

	glfwSetCursorPosCallback(m_GLFWwindow, [](GLFWwindow* window, double xpos, double ypos)
		{
			EventManager::GetInstance().PushEvent(new MouseMoveEvent(xpos, ypos));
		});

	glfwSetMouseButtonCallback(m_GLFWwindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				EventManager::GetInstance().PushEvent(new MousePressEvent(button));
			}
			else if (action == GLFW_RELEASE)
			{
				EventManager::GetInstance().PushEvent(new MouseReleaseEvent(button));
			}
		});

	glfwSetScrollCallback(m_GLFWwindow, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			EventManager::GetInstance().PushEvent(new MouseScrollEvent(xoffset, yoffset));
		});

	glfwSetWindowCloseCallback(m_GLFWwindow, [](GLFWwindow* window)
		{
			EventManager::GetInstance().PushEvent(new WindowCloseEvent());
		});

	glfwSetWindowSizeCallback(m_GLFWwindow, [](GLFWwindow* window, int width, int height)
		{
			EventManager::GetInstance().PushEvent(new WindowResizeEvent(width, height));
		});

	std::cout << "GOOD POINTER! " << m_GLFWwindow << std::endl;
	return true;
}

void Window::SetupEventListeners()
{
	std::shared_ptr<EventListener> OnResizeListener = std::make_shared<EventListener>(std::bind(&Window::OnWindowResize, this, std::placeholders::_1));
	EventManager::GetInstance().AddListener(EventType::WindowResize, OnResizeListener);
}

void Window::OnWindowResize(Event& event)
{
	std::cout << "Window resize event!\n";
	WindowResizeEvent& resizeEvent = dynamic_cast<WindowResizeEvent&>(event);
	m_Width = resizeEvent.GetWidth();
	m_Hight = resizeEvent.GetHight();
	glViewport(0, 0, m_Width, m_Hight);
}
