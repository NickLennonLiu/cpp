#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

#define nmax 1000000
#define xmax 3500000

default_random_engine e;
uniform_int_distribution<int> u(0, xmax);
uniform_int_distribution<int> percentage(0,100);

int num[nmax];

char random_operation(int ins, int del, int que)
{
    del += ins;
    que += del;
    int op = percentage(e);
    if(op <= ins)
        return 'A';
    if(op <= del)
        return 'B';
    return 'C';
}

void sorted_sequence(int length, int d, int lo, int hi, int ins, int del, int que){
    uniform_int_distribution<int> interval(lo,hi);
    for(int i = 0; i < length; i++)
        num[i] = interval(e);
    sort(num, num+length);
    
    for(int i = 0; i < length; i++)
    {
        cout << random_operation(ins, del, que) << " " << num[i] << endl;
    }
}

void random_sequence(int length, int lo, int hi, int ins, int del, int que){
    uniform_int_distribution<int> interval(lo, hi);
    for (int i = 0; i < length; i++)
    {
        cout << random_operation(ins, del, que) << " " << interval(e) << endl;
    }
}

void neighbor_sequence(int length, int lo, int hi, int ins, int del, int que)
{
    uniform_int_distribution<int> interval(lo, hi);
    int start = interval(e);
    for(int i = 0; i < length; i++)
    {
        uniform_int_distribution<int> neighbor(start-10,start+10);
        start = neighbor(e);
        cout << random_operation(ins, del, que) << " " << start << endl;
    }
}

void total_random(int n)
{
    cout << n << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << random_operation(33, 33, 33) << " " << u(e) << endl;
    }
}

int random_length(int total, bool normal)
{
    if(normal)
    {
        normal_distribution<float> normald(total/2, 1);
        int length = (int)normald(e);
        return min(max(total/16,length),total);
    } else {
        uniform_int_distribution<int> l(total/16,total);
        return l(e);
    }
}

void testcase1()    // 测例1 ：无序插入
{
    cout << nmax << endl;
    random_sequence(nmax,0,xmax,100,0,0);
}

void testcase2() // 测例2 ：分段无序插入
{
    cout << (nmax/1000)*1000 << endl;
    for(int i = 0; i < 1000; ++i)
    {
        random_sequence(nmax/1000, (xmax/1000)*i, (xmax/1000)*(i+1), 100,0,0);
    }
}

void testcase3() // 测例3 ：分段有序插入
{
    cout << (nmax / 1000) * 1000 << endl;
    for (int i = 0; i < 1000; ++i)
    {
        sorted_sequence(nmax / 1000,0, (xmax / 1000) * i, (xmax / 1000) * (i + 1), 100, 0, 0);
    }
}

void testcase4() // 测例4 ：插入-删除 1
{
    cout << nmax/3 + (nmax/3)*2 << endl;
    random_sequence(nmax/3, 0, xmax, 100,0,0);
    random_sequence(2*(nmax/3), 0, xmax, 50,50,0);
}

void testcase5() // 测例5 ：插入-删除 2
{
    cout << nmax / 3 + (nmax / 3) * 2 << endl;
    random_sequence(nmax / 3, 0, xmax, 100, 0, 0);
    for (int i = 0; i < 1000; ++i)
    {
        random_sequence(2 * (nmax / 3) / 1000, (xmax / 1000) * i, (xmax / 1000) * (i + 1), 50, 50, 0);
    }
}

void testcase6() // 测例6 ：插入-删除 3
{
    cout << nmax / 3 + (nmax / 3) * 2 << endl;
    random_sequence(nmax / 3, 0, xmax, 100, 0, 0);
    for (int i = 0; i < 1000; ++i)
    {
        sorted_sequence(2 * (nmax / 3) / 1000,0, (xmax / 1000) * i, (xmax / 1000) * (i + 1), 50, 50, 0);
    }
}

void testcase7() // 测例7 ： 随机操作 1
{
    cout << nmax << endl;
    random_sequence(nmax, 0, xmax, 33,33,33);
}

void testcase8() // 测例8 ： 随机操作 2
{
    cout << (nmax / 1000) * 1000 << endl;
    for (int i = 0; i < 1000; ++i)
    {
        random_sequence(nmax / 1000, (xmax / 1000) * i, (xmax / 1000) * (i + 1), 33, 33, 33);
    }
}

void testcase9() // 测例9 ： 随机操作 3
{
    cout << (nmax / 1000) * 1000 << endl;
    for (int i = 0; i < 1000; ++i)
    {
        neighbor_sequence(nmax / 1000, (xmax / 1000) * i, (xmax / 1000) * (i + 1), 33, 33, 33);
    }
}

int main()
{
    int n = nmax;
    int case_num;
    cin >> case_num;
    switch(case_num){
        case 1: testcase1();break;
        case 2: testcase2();break;
        case 3: testcase3();break;
        case 4: testcase4();break;
        case 5: testcase5();break;
        case 6: testcase6();break;
        case 7: testcase7();break;
        case 8: testcase8();break;
        case 9: testcase9();break;
    }
    srand(case_num * 3);
    e.seed(rand());
    return 0;
}