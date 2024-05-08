#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>

class Foo {
    std::mutex mtx1, mtx2;
    std::condition_variable cv1, cv2;
    bool ready1 = false, ready2 = false;
public:
    Foo() {
    }

    void first(std::function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        std::unique_lock<std::mutex> lck(mtx1);
        ready1 = true;
        cv1.notify_one();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lck(mtx1);
        while (!ready1) cv1.wait(lck);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        std::unique_lock<std::mutex> lck2(mtx2);
        ready2 = true;
        cv2.notify_one();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lck(mtx2);
        while (!ready2) cv2.wait(lck); 
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

void printFirst() {
  std::cout << "First\n";
}

void printSecond() {
  std::cout << "Second\n";
}

void printThird() {
  std::cout << "Third\n";
}


int main()
{
  Foo* f = new Foo();
  std::thread t2{&Foo::second, f, printSecond};
  std::thread t3{&Foo::third, f, printThird};
  std::thread t1{&Foo::first, f, printFirst};
  t1.join(); t2.join(); t3.join();
  return 0;
}
