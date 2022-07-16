#pragma once
#include <iostream>
#include <string>

class Log
{
public:
	enum class TextColor
	{
		Black,
		Green,
		Ellow,
		Red
	};
	
	static void Info();
	static void Warning();
	static void Error();

private:
	std::string GetColorCode(TextColor color);
};
 
std::string Log::GetColorCode(TextColor color)
{
	switch (color)
	{
	case Log::TextColor::Black:		return ""	break;
	case Log::TextColor::Green:			break;
	case Log::TextColor::Ellow:			break;
	case Log::TextColor::Red:			break;
	default:						return "";
	}


}








