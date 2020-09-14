#pragma once
#include <memory>
#include <omok/player.h>

enum class key_state_t
{
	none = 0,
	clear,
	enter,
	cancel,
	exit
};

class framework
{
public:
	framework();
	~framework();

	bool initialize();
	
	bool exit() const;
	bool input();
	void process_arrow_key();
	void process_enter_key();
	void process_cancel_key();
	void process_exit_key();

	void update();
	void draw(bool isFullDraw = false);
	void draw(omok::coord pos);
	wchar_t getObjectIcon(omok::coord pos);

public:
	omok::state get_player_turn() const { return turn & 1 ? omok::state::black : omok::state::white; }

private:
	key_state_t state = key_state_t::none;

	omok::coord drawStartPos{ 1, 1 };
	omok::coord prevPos{};
	omok::coord currentPos{};
	omok::board stage;

	std::unique_ptr<omok::player> player[2];
	uint8_t turn = 0;

	bool quit = false;
};
