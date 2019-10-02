#include <iostream>
#include <string>
#include "my_traits.hpp"

struct TestStruct
{
	char c;
	short s;
};
ADD_TYPE(int)
ADD_TYPE(TestStruct)

// using universal reference as argument to accept any kind of variable
template <typename T>
void foo(T&& var) {	
	std::cout << "foo: " << print_type_name<decltype(var)>() << std::endl;
}

// 
void bar(TestStruct && t) {
	std::cout << "bar && called\n";
}

void bar(TestStruct& t) {
	std::cout << "bar & called\n";
}

int main()
{
	int x = 24;
	int& lx = x;
	int&& rx = 48;

	TestStruct s = {'A', 4};
	TestStruct& ls = s;
	TestStruct&& rs = { 'B', 5 };

    // NOTE: rx & rs would still be seen as lvalue-ref's as they have a name
	foo(x); foo(lx); foo(rx); foo(72);
	foo(s); foo(ls); foo(rs); foo(TestStruct());
    bar(rs);

    // NOTE: now, rx & rs would be see as rvalue-ref's by foo as they are type-casted to a rvalue-ref using std::move
    foo(std::move(rx));
    foo(std::move(rs));
    bar(std::move(rs));

	return 0;
}
