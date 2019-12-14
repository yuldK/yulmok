#include <vector>
#include <type_traits>

#pragma warning(push)
#pragma warning(disable:4100)
namespace coord
{
	template <typename Ty>
	class dimension_coord
	{
	public:
		using value_type = Ty;

		template <typename T>
		friend dimension_coord<T>&& operator,(dimension_coord<T>&& lhs, T rhs);

	public:
		template <typename... Args>
		dimension_coord(Args&&... args) { add(std::forward<Args>(args)...); }

		size_t max_dimension() const { return value.size(); }
		value_type get(size_t idx) { return value[idx]; }

	private:
		template <typename T>
		void add(T&& val) { if constexpr (std::is_convertible_v<T, value_type>) value.push_back(std::forward<T>(val)); }

		template <typename T, typename... Args>
		void add(T&& val, Args&&...args) { add(std::forward<T>(val)); add(std::forward<Args>(args)...); }

		void add() {}

	protected:
		std::vector<Ty> value;
	};

	template <typename Ty>
	class type
	{
	public:
		using value_type = Ty;
		using this_type = type<value_type>;

	public:
		type() : val{} {}

	#pragma region default operator
		type(const this_type& other) { *this = other; }
		type(const value_type& other) { *this = other; }
		this_type& operator=(const this_type& other) { val = other.val; return *this; }
		this_type& operator=(const value_type& other) { val = other; return *this; }

		type(this_type&& other) noexcept { *this = std::move(other); }
		type(value_type&& other) noexcept { *this = std::move(other); }
		this_type& operator=(this_type&& other) noexcept { val = std::move(other.val); return *this; }
		this_type& operator=(value_type&& other) noexcept { val = std::move(other); return *this; }

		bool operator==(const this_type& other) const { return val == other.val; }
		bool operator==(const value_type& other) const { return val == other; }

		this_type& operator+=(const value_type& other) { val += other; return *this; }
		this_type& operator+=(const this_type& other) { val += other.val; return *this; }
		this_type& operator++() { ++val; return *this; }
		this_type operator++(int) { auto ret = *this;  ++val; return ret; }

		this_type& operator-=(const value_type& other) { val -= other; return *this; }
		this_type& operator-=(const this_type& other) { val -= other.val; return *this; }
		this_type& operator--() { --val; return *this; }
		this_type operator--(int) { auto ret = *this;  --val; return ret; }
		
		operator value_type() const { return val; }
	#pragma endregion

		const value_type& get() const { return val; }

	private:
		Ty val;
	};
}

	template <typename Ty>
	coord::dimension_coord<Ty> operator,(coord::type<Ty> lhs, coord::type<Ty> rhs) { return coord::dimension_coord<Ty>(lhs.get(), rhs.get()); }

	template <typename Ty>
	coord::dimension_coord<Ty> operator,(coord::type<Ty>& lhs, Ty rhs) { return coord::dimension_coord<Ty>(lhs.get(), rhs); }

	template <typename Ty, typename weak_Ty>
	coord::dimension_coord<Ty> operator,(coord::type<Ty>& lhs, weak_Ty rhs)
	{ if constexpr (std::is_convertible_v<weak_Ty, Ty>) return (lhs, static_cast<Ty>(rhs)); }

	template <typename Ty>
	coord::dimension_coord<Ty>&& operator,(coord::dimension_coord<Ty>&& lhs, coord::type<Ty> rhs) { return (std::move(lhs), rhs.get()); }

	template <typename Ty>
	coord::dimension_coord<Ty>&& operator,(coord::dimension_coord<Ty>&& lhs, Ty rhs) { lhs.add(rhs); return std::move(lhs); }

	template <typename Ty, typename weak_Ty>
	coord::dimension_coord<Ty>&& operator,(coord::dimension_coord<Ty>&& lhs, weak_Ty rhs)
	{
		if constexpr (std::is_convertible_v<weak_Ty, Ty>) return (std::move(lhs), static_cast<Ty>(rhs));
		return std::move(lhs);
	}
#pragma warning(pop)
