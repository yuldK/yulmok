#pragma once
#include <cstdint>
#include "common/dimension_coord.h"

namespace omok
{
	using coord_type = ::coord::type<int8_t>;

	struct coord : ::coord::dimension_coord<coord_type::value_type, 2>
	{
		using value_type = coord_type::value_type;
		using super_type = ::coord::dimension_coord<value_type, 2>;

	public:
		coord(value_type x = 0, value_type y = 0)
			: super_type{ x, y }
			, x{ value[0] }
			, y{ value[1] }
		{
		}

		coord(const super_type& super)
			: super_type{ super }
			, x{ value[0] }
			, y{ value[1] }
		{
		}

		coord(const coord& other)
			: super_type{ other.x, other.y }
			, x{ value[0] }
			, y{ value[1] }
		{
		}

	public:
		value_type& x;
		value_type& y;

	public:
		coord& operator=(const coord& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		bool operator==(const coord& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		bool operator!=(const coord& rhs) const
		{
			return !(*this == rhs);
		}
	};
}
