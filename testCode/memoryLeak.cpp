// memoryLeak.cpp CWE-401
int main() {
    int* p = new int[100];
    p[0] = 1;

    // delete[] p; забыли
    return 0;
}