#include "pch.h"
#include <conio.h>
#include <iomanip>

#include <string>
#include <algorithm>

#include "common/console_util.h"

#include "framework.h"

#include "omok/rule.h"

framework::framework()
	: board{}
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

		set_hide_cursor(true);
		set_font(16, L"consolas");

		set_buffer_xy(
			  (draw_start_pos.x + omok::omok_width) * 2
			, (draw_start_pos.y + omok::omok_height) + 8
		);
	}

	board.initialize();

	player[0] = std::make_unique<omok::player>(omok::state::black);
	player[1] = std::make_unique<omok::player>(omok::state::white);

	current_pos.x = omok::omok_width / 2;
	current_pos.y = omok::omok_height / 2;

	update();
	draw(true, true);

	return true;
}

bool framework::check_exit() const
{
	if (exit)
	{
		console_util::gotoxy(0, draw_start_pos.y + omok::omok_height + 3);
		Sleep(10);
		return true;
	}

	return false;
}

bool framework::check_game_end() const
{

	return false;
}

bool framework::input()
{
	key_state = key_state_t::none;

	if (::_kbhit() == false)
		return false;

	switch (int key = ::tolower(::_getch()))
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
	case 'u':
	case 'c':
		process_cancel_key();
		break;

	case 'r':
		process_redo_key();
		break;

	case 27:
	case 'q':
		process_exit_key();
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

	prev_pos = current_pos;

	auto& x = current_pos.x;
	auto& y = current_pos.y;

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
	key_state = key_state_t::enter;

	auto state = get_player_turn();

	prev_pos = current_pos;

	if (board.put(state, current_pos) == false)
		return;

	player[0]->get(state, current_pos);
	player[1]->get(state, current_pos);

	history.push(current_pos);
	undo_stack = decltype(undo_stack){};

	if (omok::rule::check::win(board, state))
	{
		winner = state;
		return;
	}

	turn++;
}

void framework::process_cancel_key()
{
	key_state = key_state_t::cancel;

	if (history.empty()) return;

	auto pos = history.top();
	history.pop();
	undo_stack.push(pos);

	prev_pos = current_pos;
	current_pos = pos;

	board.undo(current_pos);

	player[0]->get(omok::state::space, current_pos);
	player[1]->get(omok::state::space, current_pos);

	turn--;
}

void framework::process_redo_key()
{
	key_state = key_state_t::cancel;

	if (undo_stack.empty()) return;

	auto pos = undo_stack.top();
	undo_stack.pop();
	history.push(pos);

	auto state = get_player_turn();

	prev_pos = current_pos;
	current_pos = pos;

	board.put(state, current_pos);

	player[0]->get(state, current_pos);
	player[1]->get(state, current_pos);

	turn++;
}

void framework::process_exit_key()
{
	key_state = key_state_t::exit;
	exit = true;
}

void framework::update()
{
	if (winner != omok::state::unknowun)
		exit = true;
}

void framework::draw(bool draw_all, bool redraw) const
{
	using std::wcout;
	using std::endl;

	if (redraw)
		system("cls");

	draw_info();

	if (draw_all == false)
	{
		draw(prev_pos);
		draw(current_pos);

		return;
	}

	for (omok::coord_type y = 0; y < omok::omok_height; ++y)
		for (omok::coord_type x = 0; x < omok::omok_width; ++x)
			draw(omok::coord{ x, y });

	draw_help();
}

void framework::draw_info() const
{
	console_util::gotoxy(10, 0);
	std::wcout << L"< turn " << std::setw(2) << turn + 1 << L" >    \n";

	console_util::gotoxy(0, draw_start_pos.y + omok::omok_height);


	if (winner != omok::state::unknowun)
	{
		constexpr wchar_t* state_word[2]
		{
			  L"백돌"
			, L"흑돌"
		};
		std::wcout << L" " << state_word[winner == omok::state::white ? 0 : 1] << L"의 승리!                  \n";

		return;
	}

	auto weight = omok::rule::check::weight(board, current_pos, get_player_turn());
	std::wcout << L" weight : " << std::setw(4) << weight << L"      \n";
}

void framework::draw_help() const
{
	console_util::gotoxy(0, draw_start_pos.y + omok::omok_height + 2);

	std::wcout << L" ==============================\n";
	std::wcout << L" put	| x space enter\n";
	std::wcout << L" quit	| q esc\n";
	std::wcout << L" undo	| c u\n";
	std::wcout << L" redo	| r";
}

void framework::draw(omok::coord pos) const
{
	using namespace console_util;
	gotoxy(draw_start_pos.x + pos.x * 2, draw_start_pos.y + pos.y);

	set_text_color(TEXTCOLOR_ORIGIN);

	if (pos == current_pos && board[pos] == omok::player_state)
		set_text_color(TEXTCOLOR_RED);

	std::wcout << get_object_icon(pos);

	if (board[pos] == omok::state::space)
		std::wcout << L' ';

	set_text_color(TEXTCOLOR_WHITE);
}

wchar_t framework::draw_board(omok::coord pos) const
{
	return get_object_icon(pos, omok::state::space);
}

wchar_t framework::get_object_icon(omok::coord pos) const
{
	return get_object_icon(pos, board[pos]);
}

wchar_t framework::get_object_icon(omok::coord pos, omok::state state) const
{
	static constexpr auto left = 0;
	static constexpr auto right = omok::omok_width - 1;
	static constexpr auto top = 0;
	static constexpr auto bottom = omok::omok_height - 1;

	bool isFocus = pos == current_pos;

	switch (state)
	{
	case omok::state::space:
		switch (pos.y)
		{
		case top:
			switch (pos.x)
			{
			case left:	return isFocus ? L'┏' : L'┌';
			case right:	return isFocus ? L'┓' : L'┐';
			default:	return isFocus ? L'┳' : L'┬';
			}
			break;

		case bottom:
			switch (pos.x)
			{
			case left:	return isFocus ? L'┗' : L'└';
			case right:	return isFocus ? L'┛' : L'┘';
			default:	return isFocus ? L'┻' : L'┴';
			}
			break;

		default:
			switch (pos.x)
			{
			case left:	return isFocus ? L'┣' : L'├';
			case right:	return isFocus ? L'┫' : L'┤';
			default:	return isFocus ? L'╋' : L'┼';
			}
		}
		break;

	case omok::state::white:
		return isFocus ? L'◆' : L'●';

	case omok::state::black:
		return isFocus ? L'◇' : L'○';
	}
	return L'\0';
}
