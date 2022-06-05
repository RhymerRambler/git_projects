// Code to check if a method exists in the incoming template type
// This makes use of SFINAE
//
#include <string>
#include <iostream>

// Class with toString and GetInt methods
class Val1
{
public:
  std::string toString() {
    return std::to_string(x);
  }
  int GetInt() { return x; }
  Val1(int _x) : x(_x) { }
private:
  int x;
};

// Class without toString and GetInt methods
class Val2
{
public:
  std::string getString() {
    return std::to_string(x);
  }
  Val2(int _x) : x(_x) { }

private:
    int x;
};

template<typename T>
struct hasGetInt
{
  template<typename C>
  static char check(decltype(&C::GetInt)); // Compiler will select this for Val1
  template<typename C>
  static int  check(...); // Compiler will select this for Val2, but will not give an error for substitution failure for above 'check' method - this is SFINAE
  enum { value = sizeof(check<T>(0)) == sizeof(char) ;
};

template<typename T>
struct hasToString
{

  template<typename C>
  // static char check(decltype(&C::toString)); // TODO: check this works for a function returning int like GetInt, but not with toString?
  static char check(decltype(std::declval<C>().toString())); // Compiler will select this for Val1
  template<typename C>
  static int  check(...); // Compiler will select this for Val2, but will not give an error for substitution failure for above 'check' method - this is SFINAE
  enum { value = sizeof(check<T>(std::string())) == sizeof(char)};
};

// NOTE: for SFINAE to work there has to be template subsitution involved,
// hence we need function templates and that's the reason 'typename C' is
// needed in the above defintions. You could have written it without involving
// typename C, but SFINAE will not have come into action then

// Bringing in a template function, instead of using main() directly, so that
// we can use the 'if constexpr' magic
template <typename T>
std::string CallToString(T& ob)
{
  if constexpr (hasToString<T>::value) {
    return ob.toString();
  }
  return "null";
}

int main()
{
  Val1 ob(22);
  if (hasGetInt<Val1>::value) {
    std::cout << "Int: " << ob.GetInt() << std::endl;
  }
  if (hasToString<Val1>::value) {
    std::cout << "String: " << ob.toString() << std::endl;
  }
  Val2 ob2(22);
  if (hasToString<Val2>::value) {
    // This will result in a compile error, as ob2 does not have toString. See CallToString to see how to get this to work
    // std::cout << ob2.toString() << std::endl;
  }

  std::cout << CallToString<Val1>(ob) << std::endl;
  std::cout << CallToString<Val2>(ob2) << std::endl;
  
  return 0;
}
