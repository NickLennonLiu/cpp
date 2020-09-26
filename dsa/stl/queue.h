struct queue
{
    int elems[1000002];
    int rear, front;

    queue()
        : rear(0), front(0)
    {
    }

    void dequeue(int n)
    {
        front = front + n;
    }
    void enqueue(int e)
    {
        elems[rear] = e;
        rear = rear + 1;
    }
};

struct queap
{
    queue p, q; // p:维护最大值的队列 q:正常队列

    void enqueue(int e)
    {
        p.enqueue(e);
        q.enqueue(e);
        int x = p.rear - 1;
        while (x >= 0 && p.elems[x] <= e)
        {
            p.elems[x] = e;
            if (x == p.front)
                break;
            x = x - 1;
        }
    }

    void dequeue(int n)
    {
        p.dequeue(n);
        q.dequeue(n);
    }

    int getMax()
    {
        return p.elems[p.front];
    }
};
