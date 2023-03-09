#pragma once

class type_wrapper_base
{
public:
	virtual void* apply_offset() = delete;
};

class type_data
{
public:

};


class type
{

public:
	template<typename T>
	T* cast();

private:
	type_wrapper_base* type_wrapper;
};

