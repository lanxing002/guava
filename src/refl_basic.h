#pragma once

#include "reflect_type.h"

#include <unordered_map>
#include <set>

namespace zrefl
{
	//using AttrSet = std::set<Attr, AttrLess>;

	struct FieldPtr
	{
	private:
		Type type;

	};

	struct FieldInfo
	{
		FieldPtr field_ptr;
	};

	//struct MethodInfo
	//{
	//	size_t size;
	//};

	struct TypeInfo
	{
		size_t size;
		//size_t alignment;
		//bool is_polymorphic;
		//bool is_trivial;
		std::unordered_map<std::string, FieldInfo> fieldinfos;
		//std::unordered_multimap<std::string, MethodInfo> methodinfos;
		//std::unordered_map<Type, BaseInfo> baseinfos;
		//AttrSet attrs;
	};
}
