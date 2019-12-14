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
	std::wcout.imbue(std::locale("ko"));

	stage.initialize();
	player[0] = std::make_unique<omok::player>(omok::state::black);
	player[1] = std::make_unique<omok::player>(omok::state::white);

	return true;
}

bool framework::input()
{
	state = key_state_t::none;

	while (_kbhit());

	switch (int key = tolower(_getch()))
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
		return false;
		break;
	default:
//		std::cout << key << std::endl;
		break;
	}

	return true;
}

void framework::process_arrow_key()
{
	using std::cout;
	using std::endl;

	auto& x = currentPos.x;
	auto& y = currentPos.y;

	int key = _getch();

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
	system("cls");
}

void framework::draw()
{
	using std::wcout;
	using std::endl;

	static constexpr auto right = omok::omok_width - 1;
	static constexpr auto bottom = omok::omok_height - 1;

	std::wstring buffer;

	auto drawBoard = [this](omok::coord_type x, omok::coord_type y)
	{
		switch (stage[x, y])
		{
		case omok::state::space:
			switch (y)
			{
			case 0:
				switch (x)
				{
				case 0:		return L"┌";
				case right:	return L"┐";
				default:	return L"┬";
				}
				break;

			case bottom:
				switch (x)
				{
				case 0:		return L"└";
				case right:	return L"┘";
				default:	return L"┴";
				}
				break;

			default:
				switch (x)
				{
				case 0:		return L"├";
				case right:	return L"┤";
				default:	return L"┼";
				}
			}
			break;

		case omok::state::white:
			return L"○";

		case omok::state::black:
			return L"●";
		}
		return L"";
	};

	for (uint8_t y = 0; y < omok::omok_height; ++y)
	{
		buffer += L"\t";
		for (uint8_t x = 0; x < omok::omok_width; ++x)
		{
			if (currentPos == omok::coord{ x, y })
				buffer += L"※";
			else
				buffer += drawBoard(x, y);
			buffer += L" ";
		}
		buffer += L"\n";
	}

	wcout << buffer << endl;
	wcout.flush();
}
