#include <iostream>
template <typename T>
class TD;
int main()
{
    auto && rx = 27;
    int x = 27;
    auto && lx = x;
    TD<decltype(lx)> y;
    TD<decltype(rx)> ry;
    return 0;
}
