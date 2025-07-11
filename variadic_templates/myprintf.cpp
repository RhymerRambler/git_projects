#include <iostream>

template<typename T>
int myprintf(T arg1)
{
  std::cout << __PRETTY_FUNCTION__ << ": " << arg1 << std::endl;
  return 1;
}

template<typename T, typename... Args>
int myprintf(T arg1, Args... args)
{
  std::cout << __PRETTY_FUNCTION__ << ": " << arg1 << std::endl;
  return 1 + myprintf(args...);
}


int main()
{
  int x = 2;
  float y = 4.5;
  auto i = myprintf(x, " ", y);
  std::cout << "items printed: " << i << std::endl;
  return 0;
}
