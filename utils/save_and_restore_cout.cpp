#include <iostream>

// solution 1: using RAII to save and restore formatting flags
class OstreamSaveAndRestore
{
public:
  OstreamSaveAndRestore(std::ostream& out) : os(out), flags(out.flags()) { }
  ~OstreamSaveAndRestore() { os.flags(flags); }
private:
  std::ostream& os;
  std::ios::fmtflags flags;
};


void foo(int val)
{
  OstreamSaveAndRestore OSAR(std::cout);
  std::cout << "0x" << std::hex << val << std::endl;
}

void bar(int val)
{
  std::cout << val << std::endl;
}

// solution 2: make and use a different stream object over cout's rdbuf
//

void foo2(int val)
{
  std::ostream myout(std::cout.rdbuf());
  myout << "0x" << std::hex << val << std::endl;
}

int main()
{
  int x = 100;
  // solution 1
  foo(x); // will print in hex, but hex will not stick to cout
  bar(x); // will print in decimal
  // solution 2
  foo2(x); // will print in hex, but hex will not stick to cout
  bar(x); // will print in decimal
  return 0;
}
