// uninitialized.cpp CWE-457
#include <iostream> 

int main() {
    int x;
    int y = x + 1; // использование неинициализированной переменной

    std::cout << y << '\n';
}