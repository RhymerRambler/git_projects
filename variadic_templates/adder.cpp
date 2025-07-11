#include <iostream>
using namespace std;

template<typename T>
T adder(T v) {
    cout << __PRETTY_FUNCTION__ << endl;
    return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args) {
    cout << __PRETTY_FUNCTION__ << endl;
    return first + adder(args...);
}

int main()
{
  int x, y;
  cin >> x;
  cin >> y;
  cout << "addition: " << adder(x, y) << endl;
  cout << "addition: " << adder(x*y, y) << endl;
  return 0;
}
