// ruleOfThree.cpp CWE-415
class Bad {
public:
    Bad() {
        data = new int[10];
    }

    ~Bad() {
        delete[] data;
    }

private:
    int* data;
};

int main() {
    Bad a;
    Bad b = a; // shallow copy -> double free
}