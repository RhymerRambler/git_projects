#include <string>
#include <iostream>
using namespace std;

class A {
  public:
  std::string getStr() {
    return "hello";
  }

  int getInt() {
    return 361;
  }

  private:
  std::string mStr;
};

int main()
{
  // declval creates a pseudo object at compile time, which can be used to get
  // to the return type of the function
  decltype(declval<A>().getInt()) w = 1;
  decltype(declval<A>().getStr()) x = "uuu";
  std::cout  << x << w << std::endl;
  return 0;
}
