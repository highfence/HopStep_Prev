#pragma once
#include <iostream>
#include <stdarg.h>
#include <mutex>

namespace HopStep
{
	constexpr int consoleLogMaxLength = 256;

	enum class LogType : int
	{
		Trace = 1,
		Info = 2,
		Error = 3,
		Warn = 4,
		Debug= 5,
	};

	inline namespace Internal
	{
		class LoggerBase
		{
		public:

			LoggerBase() {};
			virtual ~LoggerBase() {};

			virtual void Write(const LogType type, const char * argFormat, ...)
			{
				char logText[consoleLogMaxLength];

				va_list args;
				va_start(args, argFormat);
				vsprintf_s(logText, consoleLogMaxLength, argFormat, args);
				va_end(args);

				switch (type)
				{
				case LogType::Info:
					info(logText);
					break;

				case LogType::Error:
					error(logText);
					break;

				case LogType::Warn:
					warn(logText);
					break;

				case LogType::Debug:
					debug(logText);
					break;

				case LogType::Trace:
					info(logText);
					break;

				default:
					break;
				}
			}

		protected:

			enum class ConsoleColor : unsigned short
			{
				GREEN = 2,
				BLUE = 9,
				RED = 12,
				YELLOW = 14,
				WHITE = 15,
			};

			std::mutex _lock;

			virtual void error(const char * pText) = 0;
			virtual void warn(const char * pText) = 0;
			virtual void debug(const char * pText) = 0;
			virtual void trace(const char * pText) = 0;
			virtual void info(const char * pText) = 0;
		};
	}
}
