#include <type_traits>
#include <iostream>
class TestClass
{
  int *a;
  public:
    TestClass(int len) { a = (int*)malloc(10*sizeof(int)); }
    ~TestClass() {
       if (a == nullptr) { // will happen in case of moved object
         std::cout << "a is already null: " << a << std::endl;
       }
       free(a); // call of free or delete on nullptr is safe
       std::cout << "Dtor called\n";
    }
    TestClass(TestClass&& t) {
        a = t.a;
        t.a = nullptr;
        std::cout << "Move Ctor called\n";
    }
};

int main()
{
    TestClass t(20);
    TestClass t2(std::move(t));
    // 't' would only be destructed at the end of its scope. A 'move' doesn't destroys it
}
