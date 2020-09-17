#pragma once
#include "coord.h"
#include "board.h"

namespace omok
{
	class player
	{
	public:
		player(state player_type);
		~player();

		void get(state player_type, coord coord);

	public:
		operator state() const { return my_state; }
		bool is_turn(state type) const { return type == my_state; }

	public:
		coord recommand();

	private:
		state my_state;
		board my_board;

		coord rocommand_pos = omok::coord{ -1, -1 };
	};
}
