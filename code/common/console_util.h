#pragma once

#ifndef _WINDOWS_
#define NOMINMAX
#include <windows.h>
#endif

#include <conio.h>

namespace console_util 
{
	#define TEXTCOLOR_RED		(FOREGROUND_RED		| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_GREEN		(FOREGROUND_GREEN	| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_BLUE		(FOREGROUND_BLUE	| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_CYAN		(FOREGROUND_GREEN	| FOREGROUND_BLUE	| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_YELLOW	(FOREGROUND_RED		| FOREGROUND_GREEN	| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_ORIGIN	(FOREGROUND_RED		| FOREGROUND_GREEN	| FOREGROUND_BLUE)
	#define TEXTCOLOR_WHITE		(FOREGROUND_RED		| FOREGROUND_GREEN	| FOREGROUND_BLUE	| FOREGROUND_INTENSITY)

	inline HANDLE get_handler() { return (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE); }

	// 텍스트의 색상을 변경합니다. 기본 색은 다음과 같습니다 :
	// TEXTCOLOR_RED	 : 밝은 빨간색입니다.
	// TEXTCOLOR_GREEN	 : 밝은 초록색입니다.
	// TEXTCOLOR_BLUE	 : 밝은 파랑색입니다.
	// TEXTCOLOR_CYAN	 : 밝은 하늘색입니다.
	// TEXTCOLOR_YELLOW	 : 밝은 노란색입니다.
	// TEXTCOLOR_WHITE	 : 밝은 하얀색입니다.
	inline void SetTextColor(WORD colors) { SetConsoleTextAttribute(get_handler(), colors); }

	//원하는 위치로 커서를 옮길 수 있습니다.
	inline bool gotoxy(int x, int y)
	{
		if (get_handler() == INVALID_HANDLE_VALUE) return false;

		COORD coords = { static_cast<short>(x), static_cast<short>(y) };
		SetConsoleCursorPosition(get_handler(), coords);
		return true;
	}
	// 현재 커서의 x 위치입니다.
	inline int wherex()
	{
		if (get_handler() == INVALID_HANDLE_VALUE) return 0;

		CONSOLE_SCREEN_BUFFER_INFO screenInfo;
		::GetConsoleScreenBufferInfo(get_handler(), &screenInfo);
		return screenInfo.dwCursorPosition.X;
	}
	// 현재 캐럿의 x 위치입니다.
	inline int wherey()
	{
		if (get_handler() == INVALID_HANDLE_VALUE) return 0;

		CONSOLE_SCREEN_BUFFER_INFO screenInfo;
		::GetConsoleScreenBufferInfo(get_handler(), &screenInfo);
		return screenInfo.dwCursorPosition.Y;
	}
	// 현재 콘솔의 x 최대값입니다.
	inline int buffer_max_x()
	{
		if (get_handler() == INVALID_HANDLE_VALUE) return 0;

		CONSOLE_SCREEN_BUFFER_INFO screenInfo;
		::GetConsoleScreenBufferInfo(get_handler(), &screenInfo);
		return screenInfo.dwMaximumWindowSize.X;
	}
	// 현재 콘솔의 y 최대값입니다.
	inline int buffer_max_y()
	{
		if (get_handler() == INVALID_HANDLE_VALUE) return 0;

		CONSOLE_SCREEN_BUFFER_INFO screenInfo;
		::GetConsoleScreenBufferInfo(get_handler(), &screenInfo);
		return screenInfo.dwMaximumWindowSize.Y;
	}
};
