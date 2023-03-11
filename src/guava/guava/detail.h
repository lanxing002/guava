#pragma once

#include <unordered_map>
#include <memory>
#include <string>

namespace guava
{
namespace detail
{
	template<typename T>
	using wrapper_mapper_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
}
}

// impl
namespace guava
{

namespace detail
{
}

}


