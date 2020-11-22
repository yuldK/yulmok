#pragma once

#include "hint.h"
#include "board.h"
#include <common/group.h>

namespace omok::rule
{
	using weight_t = int32_t;
}

namespace omok::rule::check
{
	weight_t weight(const board& board, const coord& pos, state turn);
	
	bool win(const board& board, state turn);
	
	bool multiple_3_point(const board& board, const coord& pos, state turn);
}
