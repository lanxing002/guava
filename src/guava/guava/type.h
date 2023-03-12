#pragma once

#include <string>
#include <string_view>
#include <memory>
#include <unordered_map>
#include <cassert>

namespace guava
{
	class type_data
	{

	public:
		std::string type_name;   // custom_name for client
		std::string type_id;    // 编译器获取的name
	};


	class type_wrapper_base
	{
	public:
		virtual void* apply_offset() = delete;
	};

	class type
	{
	public:
		type() = delete;
		type(type_data* data) :m_type_data(data) {};
		type(const type&) = default;
		type(type&&) = default;

		type& operator=(const type&) = default;
		type& operator=(type&&) = default;

		const std::string&  get_name();
		inline type_data const* get_type_data() { return m_type_data; }


		// -------- static method -----------
		template<typename T>
		constexpr static std::string name_id();

		template<typename T>  // 注册一个类型
		static type get();

		// 获取已经注册的类型
		static type get_by_name(const std::string& name);
		// -------- end static method -----------


	private:
		type_data const* m_type_data {nullptr};
		//type_wrapper_base* type_wrapper;
	};

	// -----------------------------------------------------
	namespace type_private
	{
		template<typename T>
		type create_or_get_type();

		//template<typename T>
		//std::unique_ptr<type_data> make_type_data();

		template<typename T>
		constexpr auto pure_type_name() noexcept;
	}

	class type_register_manager
	{
	private:
		type_register_manager() = default;
		type_register_manager(const type_register_manager& ) = delete;
		type_register_manager(type_register_manager&&) = delete;
		
		type_register_manager& operator=(const type_register_manager&) = delete;
		type_register_manager& operator=(type_register_manager&&) = delete;
		
	public:
		static type_register_manager& get_instance() noexcept;

		// 最主要的是使用一个自定义的名字，这样可以从一个name中生成一个type
		template<typename T>
		type register_type(const std::string& type_name) noexcept;

		const std::string& get_id_by_name(const std::string& name);

	private:
		template<typename T>
		type register_impl() noexcept;

	private:
		std::unordered_map<std::string, std::string> name_to_id;
		std::unordered_map<std::string, type> id_to_type;

	public:
		static const std::string invalid_id;


	template<typename T>
	friend type type_private::create_or_get_type();
	friend class type;
	};

}

// impl
namespace guava
{
	template<typename T>
	type type_register_manager::register_type(const std::string& type_name) noexcept
	{
		auto iter = name_to_id.find(type_name);
		assert(iter == name_to_id.end());

		auto _name_id = type::name_id<T>();
		iter = name_to_id.emplace_hint(iter, type_name, _name_id);
		return type_private::create_or_get_type<T>();;
	}

	template<typename T>
	type type_register_manager::register_impl() noexcept
	{
		auto name_id = type::name_id<T>();
		auto iter = id_to_type.find(name_id);

		if (id_to_type.end() == iter)
		{
			auto p_type_data = new type_data{ "__", name_id };
			iter = id_to_type.emplace_hint(iter, name_id, p_type_data);
		}

		return iter->second;
		//return type{ nullptr };
	};

	template<typename T>
	constexpr std::string type::name_id()
	{
		return static_cast<std::string>(type_private::pure_type_name<T>());
	}

	template<typename T>  // 注册一个类型
	type type::get()
	{
		return type_private::create_or_get_type<T>();
	}

namespace type_private
{
	template<typename T>
	type create_or_get_type()
	{
		static_assert(sizeof(T), "type must be complete !!");
		// static 语法保证create一次，其他都是get
		static const type val = type_register_manager::get_instance().register_impl<T>();
		return val;
	}

	template<typename T>
	constexpr auto pure_type_name() noexcept
	{
#		if defined(_MSC_VER)
		std::string_view sig_name{ __FUNCSIG__ };
		sig_name.remove_prefix(sig_name.find('<', 0) + 1);
		sig_name.remove_suffix(sig_name.size() - sig_name.rfind('>'));
		return sig_name;
#		endif
	}
}
}
