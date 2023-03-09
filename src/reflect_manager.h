#pragma once

#include "reflect_type.h"
#include "refl_basic.h"

#include <unordered_map>
#include <string_view>

namespace zrefl
{
	class ReflManager
	{
	public:
		static ReflManager& Instance() noexcept;

		template<typename T>
		void register_type();

		Type register_type(Type type, size_t size);

		//TODO: 这里的field_data是一个值，类似与&MyStruct::x，不是一个类型，且其类型是一个变化的，所以使用auto自动推导
		// 这里跟 template<auto c> 一样 template<char c>
		template<auto field_data>
		void register_field(std::string_view field_name);

		template<typename T>
		void register_field(std::string_view field_name, T&& data);

	private:
		//std::unordered_map<Type, TypeInfo> type_infos;
		std::unordered_map<std::string, TypeInfo> type_infos;
	};

	inline static ReflManager& zrefl_manager = ReflManager::Instance();
}

// implenmation
namespace zrefl
{
	template<typename T>
	void ReflManager::register_type()
	{
		if constexpr (std::is_void_v<T>)
			return;
		else
		{
			if constexpr (std::is_const_v<T>)
				register_type<std::remove_const_t<T>>();
			if constexpr (std::is_reference_v<T>)
				register_type<std::remove_cvref_t<T>>();
			else
			{
				auto type_name = static_cast<std::string>(details::pure_type_name<T>());
				if (type_infos.contains(type_name))
					return;

				register_type(Type{ details::pure_type_name<T>() }, std::is_empty_v<T> ? 0 : sizeof(T));
			}
		}
	}

	template<auto field_data>
	void ReflManager::register_field(std::string_view field_name)
	{

	}

	template<typename T>
	void ReflManager::register_field(std::string_view field_name, T&& data)
	{
		using RawT = std::remove_cv_t<std::remove_reference_t<T>>;
		if constexpr (std::is_member_pointer_v<RawT>)
		{

		}
		//static_assert(std::false_type::value, "Failed");
	}
}