#include "type_print_via_error.h"

#include <string>
#include <iostream>

#define SHOWTYPE 1

/* auto */
// pass By Value
template <typename T>
void pBV(T x)
{
  std::cout << x << std::endl;
#if SHOWTYPE
  TypePrinter<decltype(x)> tmp;
#endif
}


/* auto& */
// pass By Reference
template <typename T>
void pBR(T& x)
{
  std::cout << x << std::endl;
#if SHOWTYPE
  TypePrinter<decltype(x)> tmp;
#endif
}

/* auto&& */
// pass By Universal Reference
template <typename T>
void pBUR(T&& x)
{
  std::cout << x << std::endl;
#if SHOWTYPE
  TypePrinter<decltype(x)> tmp;
#endif
}

int main()
{
  std::string s = "hello";
  std::string& rs = s;

  // reference-ness of the argument is ignored in template type deduction, so 'T' is deduced as std::string in both cases
  pBV(rs); // auto  a = rs; ==> type of 'a' would be std::string
  pBR(rs); // auto& a = rs; ==> type of 'a' would be std::string&

  const std::string& crs = s;

  // Here, const-ness and reference-ness of the argument, both are ignored while type deduction, so 'T' is deduced as std::string
  pBV(crs);  // auto a = crs; ==> type of 'a' would be std::string

  // Here, only reference-ness of the argument ignored while type deduction, so 'T' is deduced as 'const std::string'
  pBR(crs);  // auto& a = crs; ==> type of 'a' would be const std::string&

  // Here, reference-ness is also not ignored, so 'T' is deduced as 'const std::string&'
  pBUR(crs); // auto&& a = crs; ==> type of 'a' would be 'const std::string&' after applying reference collapsing rule:
             // const std::string& && => const std::string&

  auto f = [](){ std::string s = "I am R value"; return s; };
  // Here, reference-ness is ignored, so 'T' is deduced as std::string
  pBUR(f()); // auto&& a = f(); ==> type of 'a' would be std::string&&

  return 0;
}
