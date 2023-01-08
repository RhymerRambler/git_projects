// Example demonstrating lazy evaluation using a user-defined view!

#include "transform_view.h"

#include <vector>
#include <iostream>

int main()
{
  auto sqr = [](int i)->int { return i*i; };
  auto dbl = [](int i)->int { return i+i; };
  auto v   = std::vector<int>{1, 2, 4, 5};
  auto tv  = TransformView<std::vector<int>>(v, sqr); // applying sqr over all elements of the vector - just creates a view
  auto tv2 = TransformView<TransformView<std::vector<int>>>(tv, dbl); // applying dbl on the transformed vector from prev step - just creates a view

  int i = 2;
  std::cout << v[i] << ": " << tv[i] << ": " << tv2[i] << std::endl;

  // new simplified syntax when instantiating class templates - works since C++17!
  auto tv3 = TransformView(v, sqr);
  auto tv4 = TransformView(tv, dbl);
  return 0;
}
