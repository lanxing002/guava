#pragma once
#include <string_view>

namespace zrefl
{
	class PBaseType
	{

	};

	namespace details
	{
		template<std::size_t size>
		struct fnv1a_traits;

		template<>
		struct fnv1a_traits<4> 
		{
			using type = std::uint32_t;
			static constexpr std::uint32_t offset = 2166136261;
			static constexpr std::uint32_t prime = 16777619;
		};

		template<>
		struct fnv1a_traits<8> 
		{
			using type = std::uint64_t;
			static constexpr std::uint64_t offset = 14695981039346656037ull;
			static constexpr std::uint64_t prime = 1099511628211ull;
		};

		constexpr std::size_t string_hash_seed(std::size_t seed, const char* str, std::size_t N) noexcept 
		{
			using traits = details::fnv1a_traits<sizeof(std::size_t)>;
			std::size_t value = seed;

			for (std::size_t i = 0; i < N; i++)
				value = (value ^ static_cast<traits::type>(str[i])) * traits::prime;

			return value;
		}

		constexpr std::size_t string_hash_seed(std::size_t seed, const char* curr) noexcept 
		{
			using traits = fnv1a_traits<sizeof(std::size_t)>;
			std::size_t value = seed;

			while (*curr) 
			{
				value = (value ^ static_cast<traits::type>(*(curr++))) * traits::prime;
			}

			return value;
		}

		constexpr std::size_t string_hash(const char* str, std::size_t N) noexcept 
		{
			using traits = fnv1a_traits<sizeof(std::size_t)>;
			return string_hash_seed(traits::offset, str, N);
		}

		constexpr std::size_t string_hash(const char* str) noexcept
		{
			using traits = fnv1a_traits<sizeof(std::size_t)>;
			return string_hash_seed(traits::offset, str);
		}

		constexpr std::size_t string_hash(std::string_view name)
		{
			using traits = fnv1a_traits<sizeof(std::size_t)>;
			return string_hash_seed(traits::offset, name.data(), name.size());
		}

		template<typename T>
		constexpr auto pure_type_name_impl() noexcept
		{
#		if defined(_MSC_VER)
			return std::string_view(__FUNCSIG__);
#		endif
		}

		template<typename T>
		constexpr auto pure_type_name() noexcept
		{
#		if defined(_MSC_VER)
			auto sig_name = pure_type_name_impl<T>();
			sig_name.remove_prefix(sig_name.find('<', 0) + 1);
			sig_name.remove_suffix(sig_name.size() - sig_name.rfind('>'));
			return sig_name;
#		endif
		}
	}


	/*class NameID
	{
	public:
		constexpr NameID(std::string_view str) noexcept :value(details::string_hash(str)) {}


	private:
		std::size_t value;
	};

	class TypeID
	{
	public:
		constexpr TypeID(std::string_view str) noexcept :name_id(str) {}

	private:
		NameID name_id;
	};

	class Name
	{

	private:
		std::string_view name;
		NameID name_id;
	};*/

	class Type
	{
	public:
		const Type() noexcept = default;
		constexpr Type(std::string_view str) noexcept :type_name(str) {}

		std::string_view get_name()
		{
			return type_name;
		}

		void set_name(std::string_view str)
		{
			type_name = str;
		}

	private:
		std::string_view type_name;
	};

}