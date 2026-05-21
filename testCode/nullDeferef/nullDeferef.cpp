// null_deref.cpp CWE-476
#include <iostream>

int main() {
    int* ptr = nullptr;

    std::cout << *ptr << '\n';
}