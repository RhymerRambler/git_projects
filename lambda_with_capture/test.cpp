#include <iostream>
#include <vector>
#include <functional>

// demo of lazy evaluation using lambda's
class PrintLater
{
  std::vector<std::function<void()>> m_printers;
  public:
    void log(int x) {
      // capturing x by reference will not work because 'x' is on stack and
      // would be long gone when lambda would actually run
      // auto printer = [&x]() { std::cout << x << std::endl; };
      
      // hence, caputuring x by value
      auto printer = [x]() { std::cout << x << std::endl; };
      m_printers.push_back(printer);
    }

    void now() {
      for(auto& f : m_printers) {
        f();
      }
    }
};


int main()
{
  PrintLater pl;
  pl.log(1);
  pl.log(2);
  pl.log(3);
  pl.log(4);
  std::cout << "Done logging" << std::endl;
  pl.now();
}
