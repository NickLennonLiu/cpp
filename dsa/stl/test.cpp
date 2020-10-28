#include <iostream>
#include "Queap.h"
using namespace std;


class TEST
{
public:
    void test(int i = 3);
};

void TEST::test(int i)
{
    cout << i << endl;
}

int main()
{
    TEST a;
    a.test();
    return 0;
}