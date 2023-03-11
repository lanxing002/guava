#include "type.h"
#include "var.h"
#include <iostream>

using namespace guava;

class Base
{
public:
	int data;
};

//Base make_b()
//{
//	return {};
//};

int main()
{
	//const Base& b = make_b();

	using um = std::unordered_map<std::string, std::string>;
	auto c = um{};
	auto iter = c.find("12");
	auto end = c.end();
	assert(iter == c.end());

	c.emplace_hint(iter, "12", "shier");
	iter = c.find("12");

	auto& manager = type_register_manager::get_instance();
	//std::cout << "hello guava!" << std::endl;
	type t2 = manager.register_type<Base>("base");
	manager.register_type<Base*>("base2");
	type t = type::get<Base>();
	type t4 = type::get_by_name("base");
	std::cout << t2.get_name() << std::endl;

	Base base;
	var obj = base;

	// register base
	// register derived
	// cast base to derived
	return 0;
}
