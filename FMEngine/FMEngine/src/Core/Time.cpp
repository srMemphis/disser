#include "fmepch.h"
#include "Time.h"
#include <ctime>

#include "GLFW/glfw3.h"

float Time::CurTime()
{
	return (float)glfwGetTime();
}

TimeStamp Time::LocalTime()
{
	std::time_t timeSinceEpoch = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &timeSinceEpoch);
	
	return TimeStamp(tm.tm_year+1900, tm.tm_mon+1,
		tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
