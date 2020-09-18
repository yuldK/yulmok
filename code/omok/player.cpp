#include "player.h"

#include <map>
#include <random>

#include <thread>
#include <future>
#include <execution>
#include <algorithm>

#include <omok/rule.h>

namespace
{
	std::default_random_engine random_engine{ std::random_device{}() };
}

namespace omok
{
	player::player(state player_type)
		: my_state{ player_type }
		, my_board{}
	{
	}

	player::~player()
	{
	}

	void player::get(state player_type, coord coord)
	{
		rocommand_pos = omok::coord{ -1, -1 };
		if (player_type == state::space)
			my_board.undo(coord);
		else
			my_board.put(player_type, coord);
	}

	coord player::recommand()
	{
		if (rocommand_pos != coord{ -1, -1 })
			return rocommand_pos;

		using pos_type = coord_type::value_type;
		std::map<rule::weight_t, std::vector<coord>> recommands;

		std::mutex lock;
		std::vector<coord> elem;

		for (pos_type x = 0; x < omok_width; ++x)
			for (pos_type y = 0; y < omok_height; ++y)
				elem.emplace_back(x, y);

		std::for_each
		(
			std::execution::par_unseq,
			elem.begin(),
			elem.end(),
			[&](const coord& pos)
			{
				if (my_board[pos] != state::space)
					return;

				rule::weight_t value = rule::check::weight(my_board, pos, my_state);
				std::lock_guard<std::mutex> lock_guard{ lock };

				recommands[value].emplace_back(pos);
			}
		);

		const auto& best_pos = recommands.rbegin()->second;
		return rocommand_pos = best_pos[std::uniform_int_distribution<size_t>{ 0, best_pos.size() - 1}(random_engine)];
	}

}
