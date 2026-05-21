// useAfterFree.cpp CWE-416
#include <iostream>

int main() {
    int* p = new int(42);
    delete p;

    std::cout << *p << '\n'; // use-after-free
    return 0;
}