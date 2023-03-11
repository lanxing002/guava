#include "type.h"

#include <iostream>
namespace guava
{
	//type::type()
	//{
	//	std::cout << "what happend" << std::endl;
	//}

	type_register_manager& type_register_manager::get_instance() noexcept
	{
		static type_register_manager manager;
		return manager;
	}

	const std::string& type::get_name()
	{
		assert(m_type_data);
		//auto iter = type_register_manager::get_instance()
		return m_type_data->type_name;
	}

	const std::string& type_register_manager::get_id_by_name(const std::string& name)
	{
		auto is_target = [&](const auto& iter) {
			return iter.first == name;
		};
		auto target = std::find_if(name_to_id.cbegin(), name_to_id.cend(), is_target);
		return target == name_to_id.end() ? invalid_id : target->second;
	}

	// 获取已经注册的类型
	type type::get_by_name(const std::string& name)
	{
		//return type{ nullptr };
		auto& manager = type_register_manager::get_instance();
		const auto& type_id = manager.get_id_by_name(name);
		if (type_id == type_register_manager::invalid_id)
			return type{ nullptr };
		else
		{
			//assert(manager.id_to_type.count(type_id) == 1);
			return manager.id_to_type.find(type_id)->second;
		}
	}

	const std::string type_register_manager::invalid_id{ "#" };
}