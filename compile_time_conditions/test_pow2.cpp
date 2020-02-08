#include <type_traits>
#include <iostream>
/*
Roughly, std::enable_if is defined like this:

template<bool, typename T>
struct enable_if { };

template<typename T>
struct enable_if<true, T> {
  using type = T;
};
*/



template<int width, 
         typename std::enable_if<width >= 2 && !(width & (width-1)), int>::type _unused = 0>
class PowerOf2Array
{
   int arr[width];
   public:
        PowerOf2Array() {
            int w = width / 2;
            arr[w-1] = w;
        }
        int getMid() {
            int w = width / 2;
            return arr[w-1];
        }
};

constexpr bool isPowerOf2(int n) {
    return ((n >= 2) && !(n & (n-1)));
}

template<int width, 
         typename std::enable_if<isPowerOf2(width), int>::type _unused = 0>
class PowerOf2ArrayV2
{
   int arr[width];
   public:
        PowerOf2ArrayV2() {
            int w = width / 2;
            arr[w-1] = w;
        }
        int getMid() {
            int w = width / 2;
            return arr[w-1];
        }
};

template<int width> 
class PowerOf2ArrayV3
{
   static_assert(isPowerOf2(width), "Width should be power of 2 in PowerOfArrayV3");
   int arr[width];
   public:
        PowerOf2ArrayV3() {
            int w = width / 2;
            arr[w-1] = w;
        }
        int getMid() {
            int w = width / 2;
            return arr[w-1];
        }
};


int main()
{
    PowerOf2Array<64> x;
    std::cout << x.getMid() << std::endl;
    PowerOf2ArrayV2<32> y;
    std::cout << y.getMid() << std::endl;
    PowerOf2ArrayV3<16> z;
    std::cout << z.getMid() << std::endl;
    return 0;
}
