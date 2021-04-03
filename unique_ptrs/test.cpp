#include <memory>
#include <iostream>

class TestBuf
{
  int* buf;
  int N;
  public: 
    TestBuf(int n) : N(n) {
      std::cout << "Creating buffer!" << std::endl;
      buf = new int[n];
    }

    ~TestBuf() {
      std::cout << "Deleting buffer!" << std::endl;
      delete[] buf;
      buf = nullptr;
    }

    void set(int i, int val) {
      if (i >= N) return;
      buf[i] = val;
    }

    friend std::ostream& operator << (std::ostream& os, TestBuf& tb) {
      for (int i=0; i < tb.N; i++) os << tb.buf[i] << ", ";
      os << std::endl;
      return os;
    }
};

std::unique_ptr<TestBuf>& process(std::unique_ptr<TestBuf>& pob)
{
  return pob;
}

std::unique_ptr<TestBuf>& process2(TestBuf* pob)
{
  std::unique_ptr<TestBuf>* pob2 = new std::unique_ptr<TestBuf>(pob);
  return *pob2;
}

int main()
{
  std::unique_ptr<TestBuf> pob1(new TestBuf(4));
  pob1->set(0, 100);
  pob1->set(1, 200);
  pob1->set(2, 300);
  pob1->set(3, 400);
  std::cout << *pob1;

  // creating a lvalue-ref doesn't change anything, as expected i.e.
  // both pob1 and pob1_ref are referring to same unique_ptr object
  std::unique_ptr<TestBuf>& pob1_ref = pob1;
  std::cout << *pob1_ref;
  std::cout << *pob1;

  // copying - not allowed as copy-construtor and assignment are deleted
  // std::unique_ptr<TestBuf> pob1_copy = pob1;

  // moving is however allowed
  std::unique_ptr<TestBuf> pob1_new = std::move(pob1);
  std::cout << *pob1_new;
  // will lead to segfault, as pob1 doesn't own  anything now
  // std::cout << *pob1; 

  // passing and retuning unique_ptr's - only by reference is possible
  auto& pobr = process(pob1_new); // by l-value reference
  std::cout << *pob1_new;
  std::cout << *pobr;
  
  ////////////////////////////////////////////////////////////////
  //
  // You need to ensure that the ownership of an object is not shared
  // Here, both pob1_new and pob2 are two different unique_ptr objects owning
  // the same underlying object - which is risky
  auto& pob2 = process2(pob1_new.get());
  std::cout << *pob1_new;
  std::cout << *pob2;
  // now if we say delete the owned object from pob2
  pob2.reset();
  // std::cout << *pob1_new; => will lead to segfault
  return 0;
}
