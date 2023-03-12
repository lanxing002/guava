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

	// �������������var�����е��������ܳ���ǰ�������ʱ����Ȼ�����ã���Ȼ���Ǵ����
	var& operator=(const var&) = delete;
	var& operator=(var&&) = delete;
		
	~var() = default;

	template<typename T>
	var(T&& data) noexcept;

	template<typename T>
	T* cast();

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

template<typename T>
T* var::cast()
{
	type target_type = type::get<T>();
	if (target_type.get_type_data()->type_id == var_type.get_type_data()->type_id)
		return static_cast<T*>(raw_data_pointer);
	else
		return nullptr;
}
}


