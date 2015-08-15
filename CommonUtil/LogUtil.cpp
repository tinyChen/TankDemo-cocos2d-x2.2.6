#include "LogUtil.h"
#include <stdarg.h>
#include <stdio.h>
#include <wtypes.h>
#include <WinCon.h>

void LogUtil::log(const char *pszFormat, ...)
{
	static const int kMaxLen = 10000;
	char szBuf[kMaxLen];

	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf_s(szBuf, kMaxLen, kMaxLen, pszFormat, ap);
	va_end(ap);

	WCHAR wszBuf[kMaxLen] = {0};
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugStringW(wszBuf);
	OutputDebugStringA("\n");

	WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
	printf("%s\n", szBuf);
}

void LogUtil::openConsole()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
}

void LogUtil::closeConsole()
{
	FreeConsole();
}