#include <iostream>

struct fooType
{
  typedef int internalType;
  internalType a;
};

template<typename T>
typename T::internalType foo(T x) {
  return x.a;
}

int foo(int x)
{
  return x;
}

int main()
{
  fooType x{22};
  std::cout << foo(x) << std::endl;
  // here, template substitution would fail, but compilation will not, as there
  // is another candidate that will match. This is SFINAE i.e. substitution
  // failure is not an error
  // Note, the compiler first collects the candidates and then does the
  // matching. Hence, template substitution happens before matching
  std::cout << foo(100) << std::endl;
  return 0;
}
