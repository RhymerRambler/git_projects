#include <string>
#include <iostream>
#include <type_traits>

/*
 In case of lvalue -> T is explicitly passed as X&
 In case of rvalue -> T is explicitly passed as X
 Note that, type deduction is prohibited in std::forward. The code snippet below doesn't do that though.
 Approx. implementation of std::forward
 template<typename T>
 T&& forward(T&& param) {
   return static_cast<T&&>(param);
 }

 */

void bar(std::string& x)
{
  std::cout << __PRETTY_FUNCTION__ << " called with x = " << x << std::endl;
}

void bar(std::string&& x)
{
  std::cout << __PRETTY_FUNCTION__ << " called with x = " << x << std::endl;
}

template <typename T>
void foo(T&& x)
{
  std::cout << "x is rvalue reference: " << std::is_rvalue_reference<decltype(x)>::value << std::endl;
  // 'x' is an lvalue now, as explained in the comment in the main() function below
  // To ensure that its reference-ness is preserved when passing further, we do an std::forward cast with 
  // an explicit type - so no type-deduction
  bar(std::forward<T>(x)); 
}

class Test
{
std::string ob;
public:
    // INCORRECT: moving a univeral reference is wrong as it may be bound to a l-value
    template <typename T>
    Test(T&& t) : ob(std::move(t)) { }
};

int main()
{
  std::string s = "hello";
  std::string& rs = s; // a lvalue reference
  auto f = [](){ std::string s = "I am R value"; return s; }; // a rvalue reference creator
  std::string&& rrs = f(); // a rvalue reference
  // references (whether lvalue or rvalue) when used in the program, they are essentially lvalue's
  // because you can assign them (not reseating), you can take their address etc. You are directly
  // operating on the object they are referring to. For e.g. we can play with rrs
  rrs[0] = 'N'; rrs[1] = 'o'; rrs[2] = 't'; rrs[3] = ' ';
  std::cout << rrs << ", address of rrs: 0x" << &rrs << std::endl; 
  foo(rrs); // will call the lvalue version
  foo(f()); // will call the rvalue version

  std::string str = "abcdef";
  std::string str2 = "12345";
  Test t(str);  // Unexpectedly, str contents are moved!
  Test t2(f());
  str += str2;

  std::cout << str << std::endl; // expect an incorrect result here!
  return 0;
}
