class FooBar {
private:
    int n;
    std::mutex m1, m2;
    std::condition_variable c1, c2;
    bool foo_done = false, bar_done = false;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            // signal bar
            {
            std::unique_lock<std::mutex> lck(m1);
            foo_done = true;
            c1.notify_one();
            }
            // wait for bar
            {
            std::unique_lock<std::mutex> lck(m2);
            while(!bar_done) c2.wait(lck);
            bar_done = false;
            }
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            // wait for foo
            {
            std::unique_lock<std::mutex> lck(m1);
            while(!foo_done) c1.wait(lck);
            foo_done = false;
            }
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            // signal foo
            {
            std::unique_lock<std::mutex> lck(m2);
            bar_done = true;
            c2.notify_one();
            }
        }
    }
};
