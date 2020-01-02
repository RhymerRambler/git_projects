#include <type_traits>
#include <iostream>
class TestClass
{
  // non-moveable data member??
  int a[10];
  public:
    // adding 'const' makes the TestClass move constructible, because with this, now it can accept rvalue references
    // Note there is no move constructor for TestClass defined (neither implicit, nor explicit)
    TestClass(/*const*/ TestClass& t) {
      for (int i=0; i<10; i++) {
        a[i] =  (t.a)[i];
      }
    }
    // no move constructor
};

int main()
{
  std::cout << "Testclass: is move constructible: " << std::is_move_constructible<TestClass>::value << std::endl;
}

// is_move_constructible means if the object can be constructed using rvalues
