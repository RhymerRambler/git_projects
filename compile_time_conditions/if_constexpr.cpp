#include <iostream>
#include <type_traits>

class Mango
{
public:
  void taste() { std::cout << "Very Sweet" << std::endl; }
  // Mango Clothes brand
  void clothes() { std::cout << "Shirts, tops, Jeans" << std::endl; }
};

class Apple
{
public:
  void taste() { std::cout << "Sweet and Sour" << std::endl; }
  void models() { std::cout << "IPhone 7, 8, 9, 10" << std::endl; }
};

template <typename T>
class Fruit
{
public:
  void taste(T f) {
    f.taste();
  }

  void brand_items(T f) {
    /* 
    if (std::is_same<T, Apple>::value) {
      // Will give compile time errors if f is of type Mango
      f.models();
    }
    else if (std::is_same_v<T, Mango>) {
      // Will give compile time errors if f is of type Apple
      f.clothes();
    }*/

    if constexpr (std::is_same<T, Apple>::value) {
      f.models();
    }
    else if constexpr (std::is_same_v<T, Mango>) {
      f.clothes();
    }
    else {
      std::cout << "Unknown type" << std::endl;
    }
  }
};


int main()
{
  Mango m;
  Fruit<Mango> f;
  f.taste(m);
  f.brand_items(m);
  Apple a;
  Fruit<Apple> f2;
  f2.taste(a);
  f2.brand_items(a);
  return 0;
}
