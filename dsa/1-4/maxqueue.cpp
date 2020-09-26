struct maxQueap
{
    int size;
    int *maxque;
    int front, rear;
    myQueap(int size)
        : size(size), front(0), rear(0)
    {
        maxque = new int[size];
    }
    ~myQueap() { delete[] maxque; }

    void enqueue(int e)
    {
        maxque[rear] = e;
        rear = (rear + 1) % size;
        int x = (rear + size - 1) % size;
        while (maxque[x] <= e)
        {
            maxque[x] = e;
            if (x == front)
                break;
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