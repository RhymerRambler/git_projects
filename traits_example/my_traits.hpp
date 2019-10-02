#pragma once

#include <type_traits>

// Trait 1: to get the name of the type
template <typename T>
struct TypeName;

#define ADD_TYPE(t) \
		template<> \
		struct TypeName<t> { static const char* name; }; \
		const char* TypeName<t>::name = #t;

// Trait 2: to check if the type is a Rvalue reference (similar to std::is_rvalue_reference in type_traits)
template <typename T>
struct IsRvalueRef {
	const static bool value = false;
};

template <typename T>
struct IsRvalueRef<T&> {
	const static bool value = false;
};

template <typename T>
struct IsRvalueRef<T&&> {
	const static bool value = true;
};

// simplifying the std::remove_reference trait using alias templates
template <typename T>
using std_remove_reference_t = typename std::remove_reference<T>::type;

// function to print the type name using traits
template <typename T>
std::string print_type_name()
{
	std::string name = TypeName<std_remove_reference_t<T>>::name;
	if (std::is_const<T>::value == true) name += " const";
	if (IsRvalueRef<T>::value) name += "&&";
	else if (std::is_lvalue_reference<T>::value) name += "&";
	return name;
}

