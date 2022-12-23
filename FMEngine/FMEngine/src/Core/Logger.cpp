#include "fmepch.h"
#include "Logger.h"

#include "Utils.h"
#include "Time.h"
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <bitset>

Logger* Logger::s_Instance = nullptr;
MAKE_BIT_FLAGS(Logger::Saverity)

Logger::Logger()
{
	m_Filter = ~(Saverity)0;
	m_OldFilter = (Saverity)0;
	m_MessageCount = 0;
	m_FilteredCount = 0;
	m_MessageOffset.push_back(0);
	m_MessageBuffer.push_back(NULL);
	m_FilteredOffset.push_back(0);
	m_FilteredBuffer.push_back(NULL);
}

Logger::~Logger()
{
}

const char* Logger::SvToStr(Saverity sv)
{
	switch (sv)
	{
	case Logger::Saverity::Debug:
		return "[DEBUG]  ";
	case Logger::Saverity::Info:
		return "[INFO]   ";
	case Logger::Saverity::Sucess:
		return "[SUCESS] ";
	case Logger::Saverity::Warning:
		return "[WARNING]";
	case Logger::Saverity::Error:
		return "[ERROR]  ";
	case Logger::Saverity::None:
		return "[       ]";
	default:
		return "[       ]";
	}
}

void Logger::Init()
{
	if (!s_Instance)
		s_Instance = new Logger();
}

void Logger::Log(const char* message)
{
	Log(Saverity::None, message);
}

void Logger::Log(Saverity sv, const char* message)
{
	// pop null terminator
	s_Instance->m_MessageBuffer.pop_back();

	// write Saverity without null terminator
	auto it = s_Instance->m_MessageBuffer.end();
	auto svStr = SvToStr(sv);
	s_Instance->m_MessageBuffer.insert(it, svStr, svStr + c_SaverityOffset);

	// write time without null terminator
	auto time = Time::LocalTime();
	char timeStr[11]{};
	sprintf_s(timeStr, "[%02d:%02d:%02d]", time.hour, time.min, time.sec);
	it = s_Instance->m_MessageBuffer.end();
	s_Instance->m_MessageBuffer.insert(it, timeStr, timeStr + c_TimeOffset);

	// write message without null terminator
	it = s_Instance->m_MessageBuffer.end();
	auto mesLen = std::strlen(message);
	s_Instance->m_MessageBuffer.insert(it, message, message + mesLen);

	// checking for \n at the end of the message
	if (message[mesLen - 1] != '\n')
	{
		s_Instance->m_MessageBuffer.push_back('\n');
		mesLen++;
	}

	// writing null terminator
	s_Instance->m_MessageBuffer.push_back(NULL);

	// calculate next message offset
	auto prevOffset = s_Instance->m_MessageOffset.back();
	s_Instance->m_MessageOffset.push_back(prevOffset + (int)mesLen + c_SaverityOffset + c_TimeOffset);

	// update message count
	s_Instance->m_MessageCount++;
	s_Instance->m_Saverity.push_back(sv);

	
	// Add message to filtered buffer
	int messageIndex = s_Instance->m_MessageCount - 1;
	if (std::underlying_type_t<Saverity>(s_Instance->m_Filter & sv))
	{
		s_Instance->m_FilteredBuffer.insert(s_Instance->m_FilteredBuffer.end(),
			s_Instance->GetMessage(messageIndex), s_Instance->GetMessage(messageIndex + 1));

		auto prevOffset = s_Instance->m_FilteredOffset.back();
		s_Instance->m_FilteredOffset.push_back(prevOffset + s_Instance->GetMessageLength(messageIndex));

		s_Instance->m_FilteredCount++;
	}

}

char* Logger::GetMessage(int index)
{
	return &s_Instance->m_MessageBuffer.at(s_Instance->m_MessageOffset.at(index));
}

int Logger::GetMessageLength(int index)
{
	return s_Instance->m_MessageOffset.at(index + 1) - s_Instance->m_MessageOffset.at(index);
}

int Logger::GetMessageCount()
{
	return s_Instance->m_MessageCount;
}

char* Logger::GetBufferEnd()
{
	return &s_Instance->m_MessageBuffer.back();
}

char* Logger::GetFilteredMessage(int index)
{
	return &s_Instance->m_FilteredBuffer.at(s_Instance->m_FilteredOffset.at(index));
}

int Logger::GetFilteredMessageLength(int index)
{
	return s_Instance->m_FilteredOffset.at(index + 1) - s_Instance->m_FilteredOffset.at(index);
}

int Logger::GetFilteredMessageCount()
{
	return s_Instance->m_FilteredCount;
}

char* Logger::GetFilteredBufferEnd()
{
	return &s_Instance->m_FilteredBuffer.back();
}

void Logger::Filter()
{
	if (std::underlying_type_t<Saverity>(s_Instance->m_Filter ^ s_Instance->m_OldFilter))
	{
		s_Instance->m_FilteredBuffer.clear();
		s_Instance->m_FilteredOffset.clear();
		s_Instance->m_FilteredCount = 0;
		s_Instance->m_FilteredOffset.push_back(0);

		for (int i = 0; i < s_Instance->m_MessageCount; i++)
		{
			Saverity sv = s_Instance->m_Saverity.at(i);
			if (std::underlying_type_t<Saverity>(s_Instance->m_Filter & sv))
			{
				s_Instance->m_FilteredBuffer.insert(s_Instance->m_FilteredBuffer.end(),
					s_Instance->GetMessage(i), s_Instance->GetMessage(i + 1));

				auto prevOffset = s_Instance->m_FilteredOffset.back();
				s_Instance->m_FilteredOffset.push_back(prevOffset + s_Instance->GetMessageLength(i));

				s_Instance->m_FilteredCount++;
			}
		}
		s_Instance->m_OldFilter = s_Instance->m_Filter;
	}
}

void Logger::SetFilter(Saverity sv)
{
	s_Instance->m_Filter = sv;
}

void Logger::FilterEnable(Saverity sv)
{
	s_Instance->m_Filter |= sv;
}

void Logger::FilterDisable(Saverity sv)
{
	s_Instance->m_Filter &= ~sv;
}

void Logger::FilterFlip(Saverity sv)
{
	s_Instance->m_Filter ^= sv;
}

void Logger::FilterClear()
{
	s_Instance->m_Filter = ~(Saverity)0;
}
