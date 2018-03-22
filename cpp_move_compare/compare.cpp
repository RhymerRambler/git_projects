/* Comparing copies, moves and emplaces when creating a vector of 'n' sequences */
/**/
#include <iostream>
#include <chrono>
#include <vector>
#include <cstddef>
#include <time.h>

#define SEQ_SIZE 1000
#define dout if (0) std::cout
class MoveableSeq
{
protected:
    int *buf;
    int size;
public:
    MoveableSeq() { size = -1; }
    MoveableSeq(int sz, int start, int incr) : size(sz) {
        dout << "constructor of MoveableSeq called\n";
        buf = new int[sz];
        int val = start;
        for (int i = 0; i < sz; i++) {
            buf[i] = val;
            val += incr;
        }
    }

    ~MoveableSeq() {
        dout << "destructor of MoveableSeq called\n";
        delete buf;
        size = 0;
    }

    MoveableSeq(const MoveableSeq& b) {
        dout << "Copy constructor of MoveableSeq called\n";
        buf = new int[b.size];
        for (int i = 0; i < b.size; i++) {
            buf[i] = b.get(i);
        }
        size = b.size;
    }

    char get(int i) const {
        return buf[i];
    }

    MoveableSeq(MoveableSeq&& b) {
        dout << "Move constructor of MoveableSeq called\n";
        buf = b.buf;
        size = b.size;
        b.buf = nullptr;
        b.size = 0;
    }
};


class NotMoveableSeq : public MoveableSeq
{
public:
    NotMoveableSeq(int sz, int start, int incr) : MoveableSeq(sz, start, incr) { }
    /* A user defined copy constructor => no implicit move constructor */
    NotMoveableSeq(const NotMoveableSeq& b) : MoveableSeq(b) { }
};


void fillCfgSeqNoMove(std::vector<NotMoveableSeq>& vec, int len)
{
    for (int i = 1; i <= len; i++) {
        vec.push_back(NotMoveableSeq(SEQ_SIZE, i, i));
    }
}

void fillCfgSeqWithMove(std::vector<MoveableSeq>& vec, int len)
{
    for (int i = 1; i <= len; i++) {
        vec.push_back(MoveableSeq(SEQ_SIZE, i, i));
    }
}

void fillCfgSeqWithEmplace(std::vector<MoveableSeq>& vec, int len)
{
    for (int i = 1; i <= len; i++) {
        vec.emplace_back(SEQ_SIZE, i, i);
    }
}

int main()
{
    int element_count;
    std::cin >> element_count;
    {
        std::vector<NotMoveableSeq> vec1;
        vec1.reserve(element_count*2);
        auto t1 = std::chrono::high_resolution_clock::now();
        fillCfgSeqNoMove(vec1, element_count);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
    }
    {
        std::vector<MoveableSeq> vec2;
        vec2.reserve(element_count*2);
        auto t1 = std::chrono::high_resolution_clock::now();
        fillCfgSeqWithMove(vec2, element_count);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
    }
    {
        std::vector<MoveableSeq> vec3;
        vec3.reserve(element_count*2);
        auto t1 = std::chrono::high_resolution_clock::now();
        fillCfgSeqWithEmplace(vec3, element_count);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
    }
    return 0;
}
