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

	// since cpp 14
	template<int8_t size>
	constexpr int8_t start_offset(const state(&arr)[size])
	{
		for (int8_t i = 0; i < size; ++i) if (arr[i] == state::N) return i;
		return -1;
	}

	constexpr state state_win[]
	{
		W, O, O, O, O, O, W
	};

	// free
	constexpr state state_1[][7]
	{
		{ S, N, S, S, S, S, W },
		{ W, S, N, S, S, S, W },
		{ W, S, S, N, S, S, W },
		{ W, S, S, S, N, S, W },
		{ W, S, S, S, S, N, S }
	};

	constexpr state state_2[][7]
	{
		{ W, O, S, S, S, N, S },

		{ W, O, S, S, N, S, W },
		{ W, S, O, S, S, N, S },

		{ W, O, S, N, S, S, W },
		{ W, S, O, S, N, S, W },
		{ W, S, S, O, S, N, S },

		{ W, O, N, S, S, S, W },
		{ W, S, O, N, S, S, W },
		{ W, S, S, O, N, S, W },
		{ W, S, S, S, O, N, S },



		{ S, N, S, S, S, O, W },

		{ S, N, S, S, O, S, W },
		{ W, S, N, S, S, O, W },

		{ S, N, S, O, S, S, W },
		{ W, S, N, S, O, S, W },
		{ W, S, S, N, S, O, W },

		{ S, N, O, S, S, S, W },
		{ W, S, N, O, S, S, W },
		{ W, S, S, N, O, S, W },
		{ W, S, S, S, N, O, W },
	};

	constexpr state state_3[][7]
	{
		{ W, O, O, S, S, N, S },

		{ W, O, O, S, N, S, W },
		{ W, S, O, O, S, N, S },

		{ W, O, O, N, S, S, W },
		{ W, S, O, O, N, S, W },
		{ W, S, S, O, O, N, S },


		{ W, O, S, O, S, N, S },

		{ W, O, S, O, N, S, W },
		{ W, S, O, S, O, N, S },


		{ W, O, S, S, O, N, S },



		{ W, O, N, S, S, O, W },

		{ W, O, N, S, O, S, W },
		{ W, S, O, N, S, O, W },

		{ W, O, N, O, S, S, W },
		{ W, S, O, N, O, S, W },
		{ W, S, S, O, N, O, W },


		{ W, O, S, N, S, O, W },

		{ W, O, S, N, O, S, W },
		{ W, S, O, S, N, O, W },


		{ W, O, S, S, N, O, W },



		{ S, N, O, S, S, O, W },

		{ S, N, O, S, O, S, W },
		{ W, S, N, O, S, O, W },

		{ S, N, O, O, S, S, W },
		{ W, S, N, O, O, S, W },
		{ W, S, S, N, O, O, W },


		{ S, N, S, O, S, O, W },

		{ S, N, S, O, O, S, W },
		{ W, S, N, S, O, O, W },


		{ S, N, S, S, O, O, W },
	};

	constexpr state state_4[][7]
	{
		{ S, N, O, O, O, S, W },
		{ S, N, O, O, S, O, W },
		{ S, N, O, S, O, O, W },
		{ S, N, S, O, O, O, W },
		{ W, S, N, O, O, O, W },

		{ W, O, N, O, O, S, W },
		{ W, O, N, O, S, O, W },
		{ W, O, N, S, O, O, W },
		{ W, O, S, N, O, O, W },
		{ W, S, O, N, O, O, W },

		{ W, O, O, N, O, S, W },
		{ W, O, O, N, S, O, W },
		{ W, O, O, S, N, O, W },
		{ W, O, S, O, N, O, W },
		{ W, S, O, O, N, O, W },

		{ W, O, O, O, N, S, W },
		{ W, O, O, O, S, N, S },
		{ W, O, O, S, O, N, S },
		{ W, O, S, O, O, N, S },
		{ W, S, O, O, O, N, S },
	};

	constexpr state state_5[][7]
	{
		{ S, N, O, O, O, O, W },
		{ W, O, N, O, O, O, W },
		{ W, O, O, N, O, O, W },
		{ W, O, O, O, N, O, W },
		{ W, O, O, O, O, N, S }
	};

	constexpr state state_6[][6]
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

	constexpr state block_state_1[][7]
	{
		{ B, N, S, S, S, S, W },
		{ W, S, S, S, S, N, B }
	};

	constexpr state block_state_2[][7]
	{
		{ W, O, S, S, S, N, B },
		{ W, S, O, S, S, N, B },
		{ W, S, S, O, S, N, B },
		{ W, S, S, S, O, N, B },

		{ B, N, S, S, S, O, W },
		{ B, N, S, S, O, S, W },
		{ B, N, S, O, S, S, W },
		{ B, N, O, S, S, S, W },
	};

	constexpr state block_state_4[][7]
	{
		{ B, N, O, O, O, S, W },
		{ B, N, O, O, S, O, W },
		{ B, N, O, S, O, O, W },
		{ B, N, S, O, O, O, W },

		{ W, O, O, O, S, N, B },
		{ W, O, O, S, O, N, B },
		{ W, O, S, O, O, N, B },
		{ W, S, O, O, O, N, B },
	};

	constexpr state block_state_3[][7]
	{
		{ W, O, O, S, S, N, B },
		{ W, S, O, O, S, N, B },
		{ W, S, S, O, O, N, B },
		{ W, O, S, O, S, N, B },
		{ W, S, O, S, O, N, B },
		{ W, O, S, S, O, N, B },

		{ B, N, O, S, S, O, W },
		{ B, N, O, S, O, S, W },
		{ B, N, O, O, S, S, W },
		{ B, N, S, O, S, O, W },
		{ B, N, S, O, O, S, W },
		{ B, N, S, S, O, O, W },
	};

	constexpr state block_state_5[][7]
	{
		{ B, N, O, O, O, O, W },
		{ W, O, O, O, O, N, B }
	};

}
