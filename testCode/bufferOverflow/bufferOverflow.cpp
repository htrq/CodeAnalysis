// bufferOverflow.cpp CWE-125

#include <iostream>

int main() {
    int arr[5] = {1,2,3,4,5};

    std::cout << arr[10] << '\n'; // выход за границы
}