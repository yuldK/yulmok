#include "pch.h"
#include <conio.h>

#include <string>
#include <algorithm>

#include "common/console_util.h"

#include "framework.h"

framework::framework()
	: stage{}
	, player{}
{
}

framework::~framework()
{

}

bool framework::initialize()
{
	std::wcout.imbue(std::locale("ko-kr"));
	{
		using namespace console_util;

		SetHideCursor(true);
		setbufferxy(omok::omok_width * 2 + 2, omok::omok_height + 8);
		removescrollbar();
		SetFont(16, L"consolas");
	}

	stage.initialize();
	player[0] = std::make_unique<omok::player>(omok::state::black);
	player[1] = std::make_unique<omok::player>(omok::state::white);

	currentPos.x = omok::omok_width / 2;
	currentPos.y = omok::omok_height / 2;

	update();
	draw(true);

	return true;
}

bool framework::exit() const
{
	return quit;
}

bool framework::input()
{
	state = key_state_t::none;

	if (_kbhit() == false)
		return false;

	switch (int key = tolower(_getwch()))
	{
		// 방향 키의 처리
	case 0:
	case 224:
		process_arrow_key();
		break;

		// 입력 키의 처리
	case 13:
	case 32:
	case 'x':
		process_enter_key();
		break;

		// 취소 키의 처리
	case 27:
	case 'c':
		process_cancel_key();
		break;

	case 'q':
		quit = true;
		break;
	default:
		std::cout << key << std::endl;
		break;
	}

	return true;
}

void framework::process_arrow_key()
{
	using std::cout;
	using std::endl;

	prevPos = currentPos;

	auto& x = currentPos.x;
	auto& y = currentPos.y;

	wint_t key = _getwch();

//	if (!player[0]->is_turn(get_player_turn()))
//		return;

	switch (key)
	{
	case 72:	// ↑
		y--;
		break;
	case 75:	// ←
		x--;
		break;
	case 77:	// →
		x++;
		break;
	case 80:	// ↓
		y++;
		break;
	}

	using type = omok::coord_type;
	x = std::min<type>(omok::omok_width - 1, std::max<type>(0, x));
	y = std::min<type>(omok::omok_height - 1, std::max<type>(0, y));
}

void framework::process_enter_key()
{
	state = key_state_t::enter;

	stage.put(get_player_turn(), currentPos);

	turn++;
}

void framework::process_cancel_key()
{
	state = key_state_t::cancel;
}

void framework::process_exit_key()
{
	state = key_state_t::exit;
}

void framework::update()
{
//	system("cls");
//	console_util::gotoxy(0, 0);
}

void framework::draw(bool isFullDraw)
{
	using std::wcout;
	using std::endl;

	if (isFullDraw)
	{
		console_util::gotoxy(0, 0);

		for (omok::coord_type i = 0; i < drawStartPos.y; ++i)
			wcout << '\n';

		for (omok::coord_type y = 0; y < omok::omok_height; ++y)
		{
			for (omok::coord_type i = 0; i < drawStartPos.x; ++i)
				wcout << L' ';
			for (omok::coord_type x = 0; x < omok::omok_width; ++x)
			{
				draw(omok::coord{ x, y });
			}
			wcout << L'\n';
		}
	}
	else
	{
		draw(prevPos);
		draw(currentPos);
	}
}

void framework::draw(omok::coord pos)
{
	console_util::gotoxy(drawStartPos.x + pos.x * 2, drawStartPos.y + pos.y);

	if (pos != currentPos)
		console_util::SetTextColor(TEXTCOLOR_ORIGIN);
	else if (stage[pos] == omok::player_state)
		console_util::SetTextColor(TEXTCOLOR_RED);
	else
		console_util::SetTextColor(TEXTCOLOR_ORIGIN);

	std::wcout << getObjectIcon(pos);

	console_util::SetTextColor(TEXTCOLOR_WHITE);
}

wchar_t framework::getObjectIcon(omok::coord pos)
{
	static constexpr auto right = omok::omok_width - 1;
	static constexpr auto bottom = omok::omok_height - 1;

	bool isFocus = pos == currentPos;

	switch (stage[pos])
	{
	case omok::state::space:
		switch (pos.y)
		{
		case 0:
			switch (pos.x)
			{
			case 0:		return isFocus ? L'┏' : L'┌';
			case right:	return isFocus ? L'┓' : L'┐';
			default:	return isFocus ? L'┳' : L'┬';
			}
			break;

		case bottom:
			switch (pos.x)
			{
			case 0:		return isFocus ? L'┗' : L'└';
			case right:	return isFocus ? L'┛' : L'┘';
			default:	return isFocus ? L'┻' : L'┴';
			}
			break;

		default:
			switch (pos.x)
			{
			case 0:		return isFocus ? L'┣' : L'├';
			case right:	return isFocus ? L'┫' : L'┤';
			default:	return isFocus ? L'╋' : L'┼';
			}
		}
		break;

	case omok::state::white:
		return isFocus ? L'◇' : L'○';

	case omok::state::black:
		return isFocus ? L'◆' : L'●';
	}
	return L'\x0';
}
