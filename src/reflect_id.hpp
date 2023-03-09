#pragma once

#include "reflect_type.h"

#include <string_view>
#include <unordered_map>

namespace zreflect
{
	template<typename T>
	class ReflectIDInfo
	{
	//protected:
	//	void register_id(T ID, std::string_view name);
	//	U register_name(std::string_view name);

	public:
		std::string_view register_id(std::size_t ID, std::string_view name);
		T register_name(std::string_view name);

		void ReflectID();

		std::string_view name_of(std::size_t ID) const noexcept;
		void clear();

	private:
		std::unordered_map<T, std::string_view> id_to_name;
	};

	//class ReflectTypeInfo : public ReflectIDInfo<Type>
	//{

	//};
}

//implemention of template
namespace zreflect
{
	template<typename T>
	std::string_view ReflectIDInfo<T>::register_id(std::size_t ID, std::string_view name)
	{

	}

	template<typename T>
	T ReflectIDInfo<T>::register_name(std::string_view name)
	{
		T ID(name);
		auto new_name = register_id(ID, name);
	}

}



