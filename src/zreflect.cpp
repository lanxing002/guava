#include <vector>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include <cassert>
#include "reflect_id.hpp"
#include "reflect_manager.h"

template<typename T>
struct MyStruct
{
    float x; 
    float y;
    T t;
};

std::string random_str()
{
    size_t size = ((double)rand() / (RAND_MAX) * 100) + 1 ;
    std::string res(size, 'i');
    for (int i = 0; i < size; i++)
    {
        auto rand_char = static_cast<char>((double)rand() / (RAND_MAX) * 127);
        if (std::isalnum(rand_char))
        {
            res[i] = rand_char;
        }
    }
    return res;
}

class ReflMngr;
class SharedObject;
int test()
{
    using namespace std::literals;
    //constexpr auto sv1{ "tt"sv };
    //std::basic_string_view t{ "tt"sv  };
    //t.remove_prefix();
    //sv1.remove_
    //ReflMngr::Inatance().RegisterTypeAuto<MyStruct>();
    //ReflMngr::Instance().AddField(&Vec::x)("x");
    //ReflMnger::Instance().AddField(&Vec::y)("y");
    //SharedObject v = ReflMngr::Instance.MakeShared(TyepID::of<Vec>);
    //std::string_view sv1{ "auto __cdecl zreflect::tools::func_signature_impl<struct MyStruct<int>&&>(void) noexcept"sv };
    //std::cout << sv1 << std::endl;
    //sv1.remove_prefix(sv1.find('<', 0) + 1);
    //std::cout << sv1 << std::endl;
    //sv1.remove_suffix(sv1.size() - sv1.rfind('>'));
    //sv1.remove_prefix(100);

    constexpr auto print_str{ zrefl::details::pure_type_name<float MyStruct<void*>::*> () };
    constexpr auto print_str2{ zrefl::details::pure_type_name<void (*)(int, bool)>() };
    constexpr auto print_str3 {zrefl::details::pure_type_name<const MyStruct<int>>()};
    std::cout << print_str2 << std::endl;
    std::cout << print_str2.data() << std::endl;
    std::cout << print_str3 << std::endl;
    
    using namespace zrefl;
    std::unordered_map<std::size_t, std::string> hash_set;
    int test_count = 2000;
    while (test_count-- > 0)
    {
        auto str = random_str();
        auto code = details::string_hash(str);
        if (hash_set.count(code) > 0)
        {
            std::cout << "hash   code:   " << code << std::endl;
            std::cout << "with   string: " << str << std::endl;
            auto& hitted_str = (hash_set.find(code))->second;
            std::cout << "hitted string: " << hitted_str << std::endl;
            assert(str == hitted_str);
        }
        hash_set.emplace(code, str);
    }

    //std::cout << zreflect::tools::pure_type_name_impl<MyStruct<int>&&>() << std::endl;
    return 0;
}

int test1()
{
    using namespace zrefl;
    zrefl_manager.register_type<MyStruct<int>>();

    zrefl_manager.register_field<&MyStruct<int>::x>("x");     
    return 0;
    //zrefl_manager.register_type<MyStruct>();
}

int main()
{
    test1();
    //test();
    //std::cout << "Hello World!\n";
}
