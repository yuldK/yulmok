#pragma once
#include <cstdint>
#include "common/group.h"
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

	private:
		state my_state;
		board my_board;
	};
}
