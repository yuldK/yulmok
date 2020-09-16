#pragma once
#include <cstdint>
#include "coord.h"
#include <common/group.h>
#include <common/bit_op.h>

namespace omok
{
	constexpr inline int8_t omok_width = 15;
	constexpr inline int8_t omok_height = 15;

	enum class state : coord_type::value_type
	{
		space = 0b00,
		white = 0b01,
		black = 0b10,
		unknowun = 0b11
	};

	constexpr auto player_state = group_compare::make_group_any(state::white, state::black);

	class board
	{
	public:
		using width_type = uint32_t;

		board() { initialize(); }
		~board() = default;

		void initialize()
		{
			// 0이 space이기 때문에 초기값으로 전부 초기화  
			for (auto& line : value)
				line = width_type{};
		}

		bool put(state player_type, coord coord)
		{
			if (player_type != player_state) return false;
			if (get(coord) != state::space) return false;

			value[coord.y] |= (static_cast<width_type>(player_type) << (coord.x * 2));

			return true;
		}

		bool undo(coord coord)
		{
			if (get(coord) == state::space) return false;

			value[coord.y] -= ((value[coord.y] >> (coord.x * 2)) & static_cast<width_type>(state::unknowun)) << (coord.x * 2);

			return true;
		}

		state operator[](coord coord) const
		{
			return get(coord);
		}

		state operator[](coord::super_type coord) const
		{
			if (coord.max_dimension() != 2) return state::unknowun;
			return get(omok::coord{ coord.get(0), coord.get(1) });
		}

	private:
		state get(coord coord) const
		{
			if (coord.x < 0 || coord.x >= omok_width) return state::unknowun;
			if (coord.y < 0 || coord.y >= omok_height) return state::unknowun;

			return (state)((value[coord.y] >> (coord.x * 2)) & 0b11);
		}

	private:
		width_type value[omok_height];
	};
}

use_bit_op(omok::state);
