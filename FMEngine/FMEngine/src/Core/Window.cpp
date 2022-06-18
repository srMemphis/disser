#include "src/Core/Window.h"

#include <iostream>
#include <memory>
#include <functional>

#include "src/Render/OpenGL/OpenGLContext.h"
#include "external/GLFW/include/GLFW/glfw3.h"

#include "src/Events/EventManager.h"
#include "src/Events/WindowEvents.h"
#include "src/Events/MouseEvents.h"
#include "src/Events/KeyboardEvents.h"


Window::Window()
{
	// Create Window
	InitGLFW();
	Create();

	// init Glad and make context current
	m_Context = new OpenGLContext(m_GLFWwindow);
	m_Context->Init();

	// Set event callback functions
	SetGLFWCallback();
	SetupEventListeners();
}

Window::Window(const char* title, int width, int hight, bool vsync)
	:m_Title(title), m_Width(width), m_Hight(hight), m_VSync(vsync)
{
	// Create Window
	InitGLFW();
	Create();

	// init Glad and make context current
	m_Context = new OpenGLContext(m_GLFWwindow);
	m_Context->Init();

	SetGLFWCallback();
	SetupEventListeners();
}

Window::~Window()
{
	// deletes m_GLFWwindow
	glfwTerminate();
}

void Window::Update()
{
	glfwPollEvents();
	m_Context->SwapBuffers();
}

void Window::InitGLFW()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
	}
}

void Window::Create()
{
	m_GLFWwindow = glfwCreateWindow(m_Width, m_Hight, m_Title.c_str(), NULL, NULL);
	if (m_GLFWwindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window\n");
	}
}

void Window::SetGLFWCallback()
{
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
