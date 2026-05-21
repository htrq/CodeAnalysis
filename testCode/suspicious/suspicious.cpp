// suspicious.cpp CWE-570
#include <iostream>

int main() {
    unsigned int x = 0;

    if (x < 0) { // всегда false
        std::cout << "Impossible\n";
    }
}