#pragma once
#include "type.h"
#include "detail.h"

namespace guava
{

class var
{
public:
	var() = delete;
	var(const var&) = default;
	var(var&&) = default;

	// 复制运算符会让var所持有的数据再跑出当前作用域的时候依然起作用，显然这是错误的
	var& operator=(const var&) = delete;
	var& operator=(var&&) = delete;
		
	~var() = default;

	template<typename T>
	var(T&& data) noexcept;

private:
	type var_type;
	void* raw_data_pointer{ nullptr };
};
}

// impl 
namespace guava
{

template<typename T>
var::var(T&& data) noexcept :
	var_type(type::get<detail::wrapper_mapper_t<T>>()),
	raw_data_pointer(std::addressof(data)) 
	{  }
}


