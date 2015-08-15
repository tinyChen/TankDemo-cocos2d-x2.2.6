#ifndef INCLUDED_DD_LOG_UTIL
#define INCLUDED_DD_LOG_UTIL

struct LogUtil
{
	static void openConsole();
	static void closeConsole();
	static void log(const char *pszFormat, ...);
};
#endif