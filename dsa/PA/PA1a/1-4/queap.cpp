#include <iostream>
using namespace std;

struct myQueap
{
    int size;
    int* maxque;
    int front, rear;
    myQueap(int size)
    : size(size)
    , front(0)
    , rear(0)
    {
        maxque = new int[size];
    }
    ~myQueap() {delete[] maxque;}

    void enqueue(int e)
    {
        maxque[rear] = e;
        rear = (rear + 1) % size;
        int x = (rear + size - 1) % size;
        while(maxque[x] <= e)
        {
            maxque[x] = e;
            if(x==front) break;
            x = (x + size - 1) % size;
        }
    }
    void dequeue(int n)
    {
        front = (front + n) % size;
    }
    int getMax()
    {
        return maxque[front];
    }
};

int main()
{
    int n;
    myQueap queap(n);
    cin >> n;
    for(int i = 0;i < n; i++)
    {
        int a;
        cin >> a;
        queap.enqueue(a);
    }
    for(int i = 0;i < n;i++)
    {
        cout << queap.getMax() << " ";
        queap.dequeue(1);
    }
    cout << endl;
    return 0;
}