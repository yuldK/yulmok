#pragma once
#include <stack>
#include <memory>
#include <omok/player.h>

enum class key_state_t
{
	none = 0,
	clear,
	enter,
	cancel,
	redo,
	exit
};

class framework
{
public:
	framework();
	~framework();

	bool initialize();
	
	bool check_exit() const;
	bool check_game_end() const;

	bool input();
	void process_arrow_key();
	void process_enter_key();
	void process_cancel_key();
	void process_redo_key();
	void process_exit_key();

	void update();
	void draw(bool draw_all = false, bool redraw = false) const;
	void draw_info() const;
	void draw_help() const;

public:
	omok::state get_turn(uint8_t t) const { return (t + 1) & 1 ? omok::state::black : omok::state::white; }
	omok::state get_player_turn() const { return get_turn(turn); }

public:
	void draw(omok::coord pos) const;
	wchar_t draw_board(omok::coord pos) const;
	wchar_t get_object_icon(omok::coord pos) const;
	wchar_t get_object_icon(omok::coord pos, omok::state state) const;

private:
	key_state_t key_state = key_state_t::none;

	omok::coord draw_start_pos{ 1, 1 };

	omok::coord prev_pos{};
	omok::coord current_pos{};

	omok::board board;

	std::stack<omok::coord> history;
	std::stack<omok::coord> undo_stack;

	std::unique_ptr<omok::player> player[2];
	uint8_t turn = 0;

	omok::state winner = omok::state::unknowun;
	bool exit = false;
};
