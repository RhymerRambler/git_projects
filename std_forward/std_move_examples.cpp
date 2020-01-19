// std::move should be used where you want the corresponding name to behave
// as rvalue reference. The name should not be used in the
// program after it has been applied a std::move, except for some cases, when the
// move doesn't actually happen (like const objects, objects whose classes
// do not have move constructor/assignemnts)

#include <iostream>
#include <vector>

class Test
{
    std::vector<int> mVec;
    public:
        // 1. std::move needed because 'in' is a lvalue (as it has a name, though it is of rvalue-ref type)
        Test(std::vector<int>&& in) : mVec(std::move(in)) {
        }
        
        Test(Test&& t) {
            mVec = t.mVec;
            std::cout << "Move constructor called" << std::endl;            
        }

        Test(const Test& t) {
            mVec = t.mVec;
            std::cout << "Copy constructor called" << std::endl;            
        }

        int get (int i) const {
            return mVec[i];
        }

        int size() const { return mVec.size(); }

        void display()  const {
            for (const auto& e : mVec) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }

        Test& add (const Test& t) {
            std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;            
            for (auto i = 0, c = t.size(); i < c; i++) {
                mVec[i] += t.get(i);
            }
            return *this;
        }

        Test& add (Test&& t) {
            std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;            
            for (auto i = 0, c = t.size(); i < c; i++) {
                mVec[i] += t.get(i);
            }
            return *this;
        }
};

// Return by value - use std::move on non-local variables, because local vars
// are anyway optimized by RVO
Test foo(Test&& x) {
  x.add(std::vector<int>({1, 22, 13, 56}));
  return std::move(x); // 2. std::move required because x is a l-value, otherwise it will trigger a copy constructor
}

int main()
{
    Test t (std::vector<int>({1, 22, 13, 56}));
    Test t1 = t;
    Test t2 = std::move(t);     // 3. use std::move to invoke the move constructor or move assignment
    Test&& rt2 = std::move(t2); // 4. OR, use std::move to create a rvalue reference
    t1.add(std::move(rt2));     // 5. OR, use std::move to convert a lvalue to a rvalue reference
                                // to invoke rvalue ref overload of a function
    t1.display();
    Test t3 = foo(std::move(t1));
    //t1.display(); => t1 cannot be accessed now, as it has actually got moved to 't3'
    t3.display();
    return 0;
}
