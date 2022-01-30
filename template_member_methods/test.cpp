#include<string>
#include<map>
#include <iostream>

class Foo
{
public:
  template<typename T>
  std::map<int, T>& mymap();

  template<typename T>
  void update(T val, int key) {
    mymap<T>()[key] = val;
  }

  template<typename T>
  void print() {
    for (auto kv : mymap<T>()) {
      std::cout << kv.first << " : " << kv.second << std::endl;
    }
  } 
private:
    std::map<int, std::string> m_int_str;
    std::map<int, double> m_int_double;
};

template<>
std::map<int, std::string>& Foo::mymap() {
  return m_int_str;
}

template<>
std::map<int, double>& Foo::mymap() {
  return m_int_double;
}

int main()
{
  Foo f;
  f.update(std::string("hello"), 1);
  f.update(std::string("hello, world!"), 2);
  f.update(1.1, 1);
  f.update(2.2, 2);
  f.print<double>();
  f.print<std::string>();
  return 0;
}
