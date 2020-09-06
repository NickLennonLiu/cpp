#include <iostream>
using namespace std;

class This{
    public:
        This() {
            m_int = 1;
        }
        int* foo() {
            return &(this->m_int);
        }
        This* bar() {
            return this;
        }
    private:
        int m_int;
};

int main(){
    This *th = new This();
    cout << *(th->foo());
    // cout << th->bar()->m_int;
    return 0;
}