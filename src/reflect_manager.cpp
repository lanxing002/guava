#include "reflect_manager.h"
#include "reflect_type.h"

#include <map>

namespace zrefl
{
	ReflManager& ReflManager::Instance() noexcept
	{
		static ReflManager refl_mngr;
		return refl_mngr;
	}


	Type ReflManager::register_type(Type type, size_t size)
	{
		auto name_str = static_cast<std::string>(type.get_name());
		auto target = type_infos.find(name_str);

		if (target != type_infos.end())
			return {};
		
		Type new_type;
		target = type_infos.emplace_hint(target, name_str, TypeInfo{size});
		new_type.set_name(name_str);

		return new_type;
	}
}