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
		std::vector<pos_type> elem;

		for (pos_type x = 0; x < omok_width; ++x)
				elem.emplace_back(x);

		std::for_each
		(
			std::execution::par_unseq,
			elem.begin(),
			elem.end(),
			[&](pos_type x)
			{
				std::array<rule::weight_t, omok_height> temp;
				for (pos_type y = 0; y < omok_height; ++y)
				{
					coord pos{ x, y };
					if (my_board[pos] != state::space) continue;
					if (omok::rule::check::multiple_3_point(my_board, pos, my_state)) continue;

					temp[y] = rule::check::weight(my_board, pos, my_state);
				}

				std::lock_guard<std::mutex> lock_guard{ lock };

				for (pos_type y = 0; y < omok_height; ++y)
				{
					coord pos{ x, y };
					if (my_board[pos] != state::space) continue;
					if (temp[y] == 0) continue;
					recommands[temp[y]].emplace_back(std::move(pos));
				}
			}
		);

		const auto& best_pos = recommands.rbegin()->second;
		return rocommand_pos = best_pos[std::uniform_int_distribution<size_t>{ 0, best_pos.size() - 1}(random_engine)];
	}

}
