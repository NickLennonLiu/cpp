// next[j+1] = next[j] + 1 iff P[j] == P[next(j)]
int * buildNext(char * P, int m)
{
    int j = 0;
    int *N = new int[m];
    int t = N[0] = -1;
    while(j != m - 1)
    {
        if(t < 0 || P[j] == P[t])
            N[++j] = ++t;
        else 
            t = N[t];
    }
    return N;
}

int kmp(char *P, char* T, int m, int n)
{
    int * next = buildNext(P, m);
    int i = 0, j = 0;
    while(j < m && i < n)
    {
        if(0 > j || T[i] == P[j] ) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    delete [] next;
    return i-j;
}