class Bitmap
{
    char *M;
    int N;
public:
    Bitmap()
    : N(3)
    {
        M = new char[N];
        for(int i = 0; i < N; i++) M[i] = 0;
    }
    Bitmap(int n)
    {
        N = n/8 + 1;
        M = new char[N];
        for(int i = 0; i < N; i++) M[i] = 0;
    }
    ~Bitmap()
    {
        delete [] M;
    }
    bool test(int k)
    {
        int pos = k >> 3, 
            mask = 0x80 >> (k & 0x07);
        return M[pos] & mask;
    }
    void set(int k)
    {
        int pos = k >> 3,
            mask = 0x80 >> (k & 0x07);
        M[pos] |= mask;
    }
    void remove(int k)
    {
        if(!test(k)) return;
        int pos = k >> 3,
            mask = 0x80 >> (k & 0x07);
        M[pos] ^= mask;
    }
    void clear()
    {
        for(int i = 0; i < N; i++) M[i] = 0;
    }
};

class Bitmap_O1
{
    int *F, *T;
    int top, N;
public:
    Bitmap_O1()
    : top(0)
    {
        F = new int[1000];
        T = new int[1000];
    }
    Bitmap_O1(int n)
    : top(0)
    , N(n)
    {
        F = new int[n];
        T = new int[n];
    }
    ~Bitmap_O1()
    {
        delete [] F;
        delete [] T;
    }
    void set(int k)
    {
        if(!test(k))
        {
            T[top] = k;
            F[k] = top++;
        }
    }
    bool test(int k)
    {
        return (F[k] >= 0) && (F[k] < top) && (T[F[k]] == k);
    }
    void remove(int k)
    {
        if(test(k) && (--top))
        {
            F[T[top]] = F[k];
            T[F[k]] = T[top];
        }
    }
    void clear()
    {
        top = 0;
    }
};