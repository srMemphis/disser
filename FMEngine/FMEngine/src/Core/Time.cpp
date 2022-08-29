#include "Time.h"

#include "GLFW/glfw3.h"

float Time::CurTime()
{
	return (float)glfwGetTime();
}
