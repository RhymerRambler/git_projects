#include <type_traits>
#include <iostream>
class TestClass
{
  int *a;
  int l;
  public:
    TestClass(int len) : l(len), a(len ? new int[len] : nullptr) { }
    void set(int idx, int val) {
        a[idx] = val;
    }
    void display() {
        std::cout << "value of a: " << std::hex << a << std::endl;
        for(int i=0; i < l; i++) {
            std::cout << std::dec << a[i] << ", ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    TestClass t(5);
    t.set(0, 1);
    t.set(1, 2);
    t.set(2, 3);
    t.set(3, 4);
    t.set(4, 5);

    TestClass t2(5);
    t2.set(0, 11);
    t2.set(1, 22);
    t2.set(2, 33);
    t2.set(3, 44);
    t2.set(4, 55);
    t.display();
    t2.display();

    t = std::move(t2);
    t.display(); 
    t2.display(); // t2 is alive and still set with values - but this is compiler specific! C++ itself says that 't2' can be in undefined state
    return 0;
}
