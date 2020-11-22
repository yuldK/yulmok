#pragma once

#include <cstdint>

namespace omok::hint
{
	enum state
	{
		W = 0b0'00,	// 벽 또는 상대 돌, 또는 빈 공간	| whatever
		S = 0b0'01, // 빈 공간							| space
		O = 0b0'10, // 내 돌							| ○
		N = 0b0'11, // 놓을 위치						| next
		X = 0b1'00,	// 상대 돌							| ×
		B = 0b1'01,	// 벽 또는 상대 돌					| block
	};

	//TODO : N 또는 O가 끝에 있을 땐 무조건 그 옆의 조건은 S여야 한다

	// since cpp 14
	template<int8_t size>
	constexpr int8_t start_offset(const state(&arr)[size])
	{
		for (int8_t i = 0; i < size; ++i) if (arr[i] == state::N) return i;
		return -1;
	}

	using hint_t = state[7];

	constexpr hint_t state_win
	{
		W, O, O, O, O, O, W
	};

	// free
	constexpr hint_t state_1[]
	{
		{ S, N, S, S, S, S, W },
		{ W, S, N, S, S, S, W },
		{ W, S, S, N, S, S, W },
		{ W, S, S, S, N, S, W },
		{ W, S, S, S, S, N, S }
	};

	constexpr hint_t state_2[]
	{
		{ W, O, S, S, S, N, W },

		{ S, O, S, S, N, S, W },
		{ W, S, O, S, S, N, S },

		{ S, O, S, N, S, S, W },
		{ W, S, O, S, N, S, W },
		{ W, S, S, O, S, N, S },

		{ S, O, N, S, S, S, W },
		{ W, S, O, N, S, S, W },
		{ W, S, S, O, N, S, W },
		{ W, S, S, S, O, N, S },



		{ W, N, S, S, S, O, W },

		{ S, N, S, S, O, S, W },
		{ W, S, N, S, S, O, S },

		{ S, N, S, O, S, S, W },
		{ W, S, N, S, O, S, W },
		{ W, S, S, N, S, O, S },

		{ S, N, O, S, S, S, W },
		{ W, S, N, O, S, S, W },
		{ W, S, S, N, O, S, W },
		{ W, S, S, S, N, O, S },
	};

	constexpr hint_t state_3[]
	{
		{ W, O, O, S, S, N, W },

		{ S, O, O, S, N, S, W },
		{ W, S, O, O, S, N, S },

		{ S, O, O, N, S, S, W },
		{ W, S, O, O, N, S, W },
		{ W, S, S, O, O, N, S },


		{ W, O, S, O, S, N, W },

		{ S, O, S, O, N, S, W },
		{ W, S, O, S, O, N, S },


		{ W, O, S, S, O, N, W },



		{ W, O, N, S, S, O, W },

		{ S, O, N, S, O, S, W },
		{ W, S, O, N, S, O, S },

		{ S, O, N, O, S, S, W },
		{ W, S, O, N, O, S, W },
		{ W, S, S, O, N, O, S },


		{ W, O, S, N, S, O, W },

		{ S, O, S, N, O, S, W },
		{ W, S, O, S, N, O, S },


		{ W, O, S, S, N, O, W },



		{ W, N, O, S, S, O, W },

		{ S, N, O, S, O, S, W },
		{ W, S, N, O, S, O, S },

		{ S, N, O, O, S, S, W },
		{ W, S, N, O, O, S, W },
		{ W, S, S, N, O, O, S },


		{ W, N, S, O, S, O, W },

		{ S, N, S, O, O, S, W },
		{ W, S, N, S, O, O, S },


		{ W, N, S, S, O, O, W },
	};

	constexpr hint_t state_4[]
	{
		{ S, N, O, O, O, S, W },
		{ W, N, O, O, S, O, W },
		{ W, N, O, S, O, O, W },
		{ W, N, S, O, O, O, W },
		{ W, S, N, O, O, O, S },

		{ S, O, N, O, O, S, W },
		{ W, O, N, O, S, O, W },
		{ W, O, N, S, O, O, W },
		{ W, O, S, N, O, O, W },
		{ W, S, O, N, O, O, S },

		{ S, O, O, N, O, S, W },
		{ W, O, O, N, S, O, W },
		{ W, O, O, S, N, O, W },
		{ W, O, S, O, N, O, W },
		{ W, S, O, O, N, O, S },

		{ S, O, O, O, N, S, W },
		{ W, O, O, O, S, N, W },
		{ W, O, O, S, O, N, W },
		{ W, O, S, O, O, N, W },
		{ W, S, O, O, O, N, S },
	};

	constexpr hint_t state_5[]
	{
		{ W, N, O, O, O, O, W },
		{ W, O, N, O, O, O, W },
		{ W, O, O, N, O, O, W },
		{ W, O, O, O, N, O, W },
		{ W, O, O, O, O, N, W }
	};

	constexpr hint_t state_6[]
	{
		{ O, N, O, O, O, O },
		{ O, O, N, O, O, O },
		{ O, O, O, N, O, O },
		{ O, O, O, O, N, O },


		{ O, N, O, O, O, O },
		{ O, O, N, O, O, O },
		{ O, O, O, N, O, O },
		{ O, O, O, O, N, O },
	};

	constexpr hint_t block_state_1[]
	{
		{ B, N, S, S, S, S, W },
		{ W, S, S, S, S, N, B }
	};

	constexpr hint_t block_state_2[]
	{
		{ B, O, S, S, N, S, W },
		{ B, O, S, N, S, S, W },
		{ B, O, N, S, S, S, W },
		{ W, S, O, S, S, N, B },
		{ W, S, S, O, S, N, B },
		{ W, S, S, S, O, N, B },

		{ W, S, N, S, S, O, B },
		{ W, S, S, N, S, O, B },
		{ W, S, S, S, N, O, B },
		{ B, N, S, S, O, S, W },
		{ B, N, S, O, S, S, W },
		{ B, N, O, S, S, S, W },
	};

	constexpr hint_t block_state_3[]
	{
		{ W, S, O, O, S, N, B },
		{ W, S, S, O, O, N, B },
		{ W, S, O, S, O, N, B },

		{ W, S, N, O, S, O, B },
		{ W, S, N, S, O, O, B },
		{ W, S, O, N, S, O, B },
		{ W, S, S, N, O, O, B },
		{ W, S, O, S, N, O, B },
		{ W, S, S, O, N, O, B },


		{ B, N, O, S, O, S, W },
		{ B, N, O, O, S, S, W },
		{ B, N, S, O, O, S, W },

		{ B, O, O, S, N, S, W },
		{ B, O, S, O, N, S, W },
		{ B, O, O, N, S, S, W },
		{ B, O, S, N, O, S, W },
		{ B, O, N, O, S, S, W },
		{ B, O, N, S, O, S, W },
	};

	constexpr hint_t block_state_4[]
	{
		{ B, N, O, O, O, S, W },
		{ B, N, O, O, S, O, W },
		{ B, N, O, S, O, O, W },
		{ B, N, S, O, O, O, W },
		{ B, O, O, O, N, S, W },
		{ B, O, O, N, O, S, W },
		{ B, O, N, O, O, S, W },

		{ W, O, O, O, S, N, B },
		{ W, O, O, S, O, N, B },
		{ W, O, S, O, O, N, B },
		{ W, S, O, O, O, N, B },
		{ W, S, O, O, N, O, B },
		{ W, S, O, N, O, O, B },
		{ W, S, N, O, O, O, B },
	};

}
