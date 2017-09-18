/* Comparing copies, moves and emplaces when creating a vector of 'n' sequences */
/**/
#include <iostream>
#include <chrono>
#include <vector>
#include <cstddef>
#include <time.h>

#define SEQ_SIZE 1000
#define dout if (0) std::cout
class MoveableBuf
{
protected:
    int *buf;
    int size;
public:
    MoveableBuf() { size = -1; }
    MoveableBuf(int sz, int start, int incr) : size(sz) {
        dout << "constructor of Moveable called\n";
        buf = new int[sz];
        int val = start;
        for (int i = 0; i < sz; i++) {
            buf[i] = val;
            val += incr;
        }
    }

    ~MoveableBuf() {
        dout << "destructor of Moveable called\n";
        delete buf;
        size = 0;
    }

    MoveableBuf(const MoveableBuf& b) {
        dout << "Copy constructor of Moveable called\n";
        buf = new int[b.size];
        for (int i = 0; i < b.size; i++) {
            buf[i] = b.get(i);
        }
        size = b.size;
    }

    char get(int i) const {
        return buf[i];
    }

    MoveableBuf(MoveableBuf&& b) {
        dout << "Move constructor of MoveableBuf called\n";
        buf = b.buf;
        size = b.size;
        b.buf = nullptr;
        b.size = 0;
    }
};


class NotMoveableBuf : public MoveableBuf
{
public:
    NotMoveableBuf(int sz, int start, int incr) : MoveableBuf(sz, start, incr) { }
    /* A user defined copy constructor => no implicit move constructor */
    NotMoveableBuf(const NotMoveableBuf& b) : MoveableBuf(b) { }
};


void fillCfgBufNoMove(std::vector<NotMoveableBuf>& vec, int len)
{
    for (int i = 1; i <= len; i++) {
        vec.push_back(NotMoveableBuf(SEQ_SIZE, i, i));
    }
}

void fillCfgBufWithMove(std::vector<MoveableBuf>& vec, int len)
{
    for (int i = 1; i <= len; i++) {
        vec.push_back(MoveableBuf(SEQ_SIZE, i, i));
    }
}

void fillCfgBufWithEmplace(std::vector<MoveableBuf>& vec, int len)
{
    for (int i = 1; i <= len; i++) {
        vec.emplace_back(SEQ_SIZE, i, i);
    }
}

int main()
{
    int element_count;
    std::cin >> element_count;

    std::vector<NotMoveableBuf> vec1;
    vec1.reserve(element_count*2);

    std::vector<MoveableBuf> vec2;
    vec2.reserve(element_count*2);

    std::vector<MoveableBuf> vec3;
    vec3.reserve(element_count*2);
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        fillCfgBufNoMove(vec1, element_count);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "f() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
            << " milliseconds\n";
    }
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        fillCfgBufWithMove(vec2, element_count);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "f() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
            << " milliseconds\n";
    }
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        fillCfgBufWithEmplace(vec3, element_count);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "f() took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
            << " milliseconds\n";
    }

    return 0;
}
