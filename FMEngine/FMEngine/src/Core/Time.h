#pragma once

struct TimeStamp
{	
	TimeStamp(int y, int mo, int d, int h, int mi, int s)
		: year(y), mon(mo), day(d), hour(h), min(mi), sec(s) {}
	int sec = 0;
	int min = 0;
	int hour = 0;
	int day = 0;
	int mon = 0;
	int year = 0;
};

class Time
{
public:
	static float CurTime();          // returns the number of seconds since glfwInit
	static TimeStamp LocalTime();    // returns local time 

};
