#pragma once
#include <vector>

class Logger
{
public:
	enum class Saverity : std::uint8_t
	{
		Debug	= 1ull << 0,
		Info	= 1ull << 1,
		Sucess	= 1ull << 2,
		Warning = 1ull << 3,
		Error	= 1ull << 4,
		None	= 1ull << 5
	};												

	friend Saverity operator| (const Saverity lhs, const Saverity rhs);

	static void Init();
	static void Log(const char* message);
	static void Log(Saverity sv, const char* message);

	static char* GetMessage(int index);
	static int GetMessageLength(int index);
	static int GetMessageCount();
	static char* GetBufferEnd();

	static char* GetFilteredMessage(int index);
	static int GetFilteredMessageLength(int index);
	static int GetFilteredMessageCount();
	static char* GetFilteredBufferEnd();

	static void Filter();
	static void SetFilter(Saverity sv);
	static void FilterEnable(Saverity sv);
	static void FilterDisable(Saverity sv);
	static void FilterFlip(Saverity sv);
	static void FilterClear();

	static const int c_SaverityOffset = 9;
	static const int c_TimeOffset = 10;

private:
	Logger();
	~Logger();
	static Logger* s_Instance;
	static const char* SvToStr(Saverity sv);

	std::vector<int>  m_MessageOffset;
	std::vector<char> m_MessageBuffer;
	int m_MessageCount;

	std::vector<int>  m_FilteredOffset;
	std::vector<char> m_FilteredBuffer;
	int m_FilteredCount;

	std::vector<Saverity> m_Saverity;
	Saverity m_Filter;
	Saverity m_OldFilter;
};

#define FME_LOG_DEBUG(message)	 Logger::Log(Logger::Saverity::Debug,   message)
#define FME_LOG_INFO(message)	 Logger::Log(Logger::Saverity::Info,    message)
#define FME_LOG_ERROR(message)	 Logger::Log(Logger::Saverity::Error,   message)
#define FME_LOG_SUCESS(message)	 Logger::Log(Logger::Saverity::Sucess,  message)
#define FME_LOG_WARNING(message) Logger::Log(Logger::Saverity::Warning, message)
