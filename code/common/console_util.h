#pragma once

#pragma push_macro("NOMINMAX")

#include <conio.h>
#include <windows.h>
#include <string_view>

namespace console_util 
{
	#define TEXTCOLOR_RED		(FOREGROUND_RED		| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_GREEN		(FOREGROUND_GREEN	| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_BLUE		(FOREGROUND_BLUE	| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_CYAN		(FOREGROUND_GREEN	| FOREGROUND_BLUE	| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_YELLOW	(FOREGROUND_RED		| FOREGROUND_GREEN	| FOREGROUND_INTENSITY)
	#define TEXTCOLOR_ORIGIN	(FOREGROUND_RED		| FOREGROUND_GREEN	| FOREGROUND_BLUE	)
	#define TEXTCOLOR_WHITE		(FOREGROUND_RED		| FOREGROUND_GREEN	| FOREGROUND_BLUE	| FOREGROUND_INTENSITY)

	inline HANDLE get_handler()
	{
		return (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// 텍스트의 색상을 변경합니다. 기본 색은 다음과 같습니다 :
	// TEXTCOLOR_RED	 : 밝은 빨간색입니다.
	// TEXTCOLOR_GREEN	 : 밝은 초록색입니다.
	// TEXTCOLOR_BLUE	 : 밝은 파랑색입니다.
	// TEXTCOLOR_CYAN	 : 밝은 하늘색입니다.
	// TEXTCOLOR_YELLOW	 : 밝은 노란색입니다.
	// TEXTCOLOR_WHITE	 : 밝은 하얀색입니다.
	inline void SetTextColor(WORD colors)
	{
		::SetConsoleTextAttribute(get_handler(), colors);
	}

	inline void SetHideCursor(bool hide)
	{
		CONSOLE_CURSOR_INFO info;
		::GetConsoleCursorInfo(get_handler(), &info);

		info.bVisible = static_cast<BOOL>(!hide);
		::SetConsoleCursorInfo(get_handler(), &info);
	}

	inline void SetFont(short size, wchar_t* fontName = nullptr)
	{
		auto handler = get_handler();

		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);

		::GetCurrentConsoleFontEx(get_handler(), FALSE, &cfi);

		// Height
		cfi.dwFontSize.Y = size;

		if (fontName != nullptr)
		{
			std::wstring_view font{ fontName };

			// Choose your font
			std::copy(font.begin(), font.end(), cfi.FaceName);
		}

		::SetCurrentConsoleFontEx(handler, FALSE, &cfi);

	}

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
	// 현재 콘솔의 x, y값을 설정합니다.
	inline void setbufferxy(short x, short y)
	{
		auto handler = get_handler();
		if (handler == INVALID_HANDLE_VALUE) return;

		CONSOLE_SCREEN_BUFFER_INFOEX screenInfo;
		screenInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		::GetConsoleScreenBufferInfoEx(handler, &screenInfo);

		screenInfo.dwSize.X = x;
		screenInfo.dwSize.Y = y;
		::SetConsoleScreenBufferInfoEx(handler, &screenInfo);
	}

	inline void removescrollbar()
	{
		auto handler = get_handler();
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		::GetConsoleScreenBufferInfo(handler, &csbi);

		COORD scrollbar 
		{
			csbi.srWindow.Right - csbi.srWindow.Left + 1,
			csbi.srWindow.Bottom - csbi.srWindow.Top + 1
		};

		::SetConsoleScreenBufferSize(handler, scrollbar);
	}
};

#pragma pop_macro("NOMINMAX")
