#pragma once

#include "rule.h"
#include <limits>

namespace
{
	template <class _Ty, omok::coord_type::value_type n>
	constexpr omok::coord_type::value_type size(const _Ty(&)[n]) noexcept { return n; }
}

namespace omok::rule
{
	using weight_t = int32_t;

	weight_t my_weight_state_1 = 5;
	weight_t my_weight_state_2 = 25;
	weight_t my_weight_state_3 = 100;
	weight_t my_weight_state_4 = 500;
	weight_t my_weight_state_5 = 10'000;

	weight_t my_block_weight_state_1 = 3;
	weight_t my_block_weight_state_2 = 15;
	weight_t my_block_weight_state_3 = 50;
	weight_t my_block_weight_state_4 = 300;
	weight_t my_block_weight_state_5 = 10'000;

	weight_t opponent_weight_state_1 = 2;
	weight_t opponent_weight_state_2 = 15;
	weight_t opponent_weight_state_3 = 70;
	weight_t opponent_weight_state_4 = 400;
	weight_t opponent_weight_state_5 = 2'000;

	weight_t opponent_block_weight_state_1 = 1;
	weight_t opponent_block_weight_state_2 = 10;
	weight_t opponent_block_weight_state_3 = 35;
	weight_t opponent_block_weight_state_4 = 250;
	weight_t opponent_block_weight_state_5 = 2'000;

	weight_t do_not_put_this = std::numeric_limits<weight_t>::max();

	namespace check
	{
		bool correct_state(const board& board, const coord& pos, hint::state state, omok::state turn)
		{
			if (state == hint::W) return true;

			bool oor = (pos.x < 0 || pos.x >= omok_width)
					|| (pos.y < 0 || pos.y >= omok_height);

			constexpr auto check_block = group_compare::make_group_any(hint::B, hint::W);

			if (oor) return (state == check_block);

			switch (state)
			{
			case hint::S:
				return board[pos] == state::space;

			case hint::O:
				return board[pos] == turn;

			case hint::N:
				return board[pos] == state::space || board[pos] == turn;

			case hint::X:
			case hint::B:
				return (board[pos] != turn) && (board[pos] == player_state);
			}
			return false;
		}

		template<typename fn>
		weight_t calc_impl(fn&& func, state turn)
		{
			weight_t weight = 0;
			state opponent = state::unknowun ^ turn;

			// do not put this pos
			for (const auto& state : hint::state_6)
				if (0 != func(state, do_not_put_this, turn))
					return do_not_put_this;

			for (const auto& state : hint::state_1)
			{
				weight += func(state, my_weight_state_1, turn);
				weight += func(state, opponent_weight_state_1, opponent);
			}
			for (const auto& state : hint::state_2)
			{
				weight += func(state, my_weight_state_2, turn);
				weight += func(state, opponent_weight_state_2, opponent);
			}
			for (const auto& state : hint::state_3)
			{
				weight += func(state, my_weight_state_3, turn);
				weight += func(state, opponent_weight_state_3, opponent);
			}
			for (const auto& state : hint::state_4)
			{
				weight += func(state, my_weight_state_4, turn);
				weight += func(state, opponent_weight_state_4, opponent);
			}
			for (const auto& state : hint::state_5)
			{
				weight += func(state, my_weight_state_5, turn);
				weight += func(state, opponent_weight_state_5, opponent);
			}

			for (const auto& state : hint::block_state_1)
			{
				weight += func(state, my_block_weight_state_1, turn);
				weight += func(state, opponent_block_weight_state_1, opponent);
			}
			for (const auto& state : hint::block_state_2)
			{
				weight += func(state, my_block_weight_state_2, turn);
				weight += func(state, opponent_block_weight_state_2, opponent);
			}
			for (const auto& state : hint::block_state_3)
			{
				weight += func(state, my_block_weight_state_3, turn);
				weight += func(state, opponent_block_weight_state_3, opponent);
			}
			for (const auto& state : hint::block_state_4)
			{
				weight += func(state, my_block_weight_state_4, turn);
				weight += func(state, opponent_block_weight_state_4, opponent);
			}
			for (const auto& state : hint::block_state_5)
			{
				weight += func(state, my_block_weight_state_5, turn);
				weight += func(state, opponent_block_weight_state_5, opponent);
			}

			return weight;
		}

		weight_t horizontal(const board& board, const coord& pos, state turn)
		{
			return calc_impl([&board, &pos](const auto& state, weight_t weight, omok::state turn) -> weight_t
			{
				using value_type = coord_type::value_type;

				value_type size = ::size(state);
				value_type left = hint::start_offset(state);

				bool flag = true;
				for (value_type dist = 0; flag && dist < size; ++dist)
					flag = flag && correct_state(board, coord{ pos.x + dist - left, pos.y }, state[dist], turn);

				if (flag == false) return 0;
				return weight;
			}, turn);
		}

		weight_t vertical(const board& board, const coord& pos, state turn)
		{
			return calc_impl([&board, &pos](const auto& state, weight_t weight, omok::state turn) -> weight_t
			{
				using value_type = coord_type::value_type;

				value_type size = ::size(state);
				value_type left = hint::start_offset(state);

				bool flag = true;
				for (value_type dist = 0; flag && dist < size; ++dist)
					flag = flag && correct_state(board, coord{ pos.x, pos.y + dist - left }, state[dist], turn);

				if (flag == false) return 0;
				return weight;
			}, turn);
		}

		weight_t straight_diagonal(const board& board, const coord& pos, state turn)
		{
			return calc_impl([&board, &pos](const auto& state, weight_t weight, omok::state turn) -> weight_t
			{
				using value_type = coord_type::value_type;

				value_type size = ::size(state);
				value_type left = hint::start_offset(state);

				bool flag = true;
				for (value_type dist = 0; flag && dist < size; ++dist)
					flag = flag && correct_state(board, coord{ pos.x + dist - left , pos.y + dist - left }, state[dist], turn);

				if (flag == false) return 0;
				return weight;
			}, turn);
		}
		
		weight_t reverse_diagonal(const board& board, const coord& pos, state turn)
		{
			return calc_impl([&board, &pos](const auto& state, weight_t weight, omok::state turn) -> weight_t
			{
				using value_type = coord_type::value_type;

				value_type size = ::size(state);
				value_type left = hint::start_offset(state);

				bool flag = true;
				for (value_type dist = 0; flag && dist < size; ++dist)
					flag = flag && correct_state(board, coord{ pos.x + dist - left , pos.y - dist + left }, state[dist], turn);

				if (flag == false) return 0;
				return weight;
			}, turn);
		}

		weight_t weight(const board& board, const coord& pos, state turn)
		{
			weight_t weight_h = horizontal(board, pos, turn);
			if (weight_h == do_not_put_this) return 0;
			weight_t weight_v = vertical(board, pos, turn);
			if (weight_v == do_not_put_this) return 0;
			weight_t weight_s = straight_diagonal(board, pos, turn);
			if (weight_s == do_not_put_this) return 0;
			weight_t weight_r = reverse_diagonal(board, pos, turn);
			if (weight_r == do_not_put_this) return 0;

			return weight_h + weight_v + weight_s + weight_r;
		}

		bool win(const board& board, state turn)
		{
			using value_type = coord_type::value_type;
			constexpr value_type state_size = ::size(hint::state_win);

			for (value_type x = -1; x < omok_width; ++x)
			{
				for (value_type y = -1; y < omok_height; ++y)
				{
					bool flag;

					// horizontal
					flag = true;
					for (value_type i = 0; flag == true && i < state_size; ++i)
						flag = flag && correct_state(board, coord{ x + i, y }, hint::state_win[i], turn);
					if (flag) return true;

					// vertical
					flag = true;
					for (value_type i = 0; flag == true && i < state_size; ++i)
						flag = flag && correct_state(board, coord{ x, y + i }, hint::state_win[i], turn);
					if (flag) return true;

					// straight diagonal
					flag = true;
					for (value_type i = 0; flag == true && i < state_size; ++i)
						flag = flag && correct_state(board, coord{ x + i, y + i }, hint::state_win[i], turn);
					if (flag) return true;

					// reverse diagonal
					flag = true;
					for (value_type i = 0; flag == true && i < state_size; ++i)
						flag = flag && correct_state(board, coord{ x + i, y - i }, hint::state_win[i], turn);
					if (flag) return true;
				}
			}

			return false;
		}

	}
}
