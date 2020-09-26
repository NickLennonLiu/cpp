#include <iostream>
#include "quickSort.cpp"
using namespace std;

int main()
{
    int n[10] = {2,1,3,3,5,0,8,-2,3,4};
    while(true)
    {
        for(int i = 0; i < 10; i++) n[i] = rand() % 100;
        quickSort(n,0,10);
        for(int i = 0; i < 10; i++)
        {
            cout << n[i] << " ";
        }
    }
    
    return 0;
}