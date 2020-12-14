int partition(int *a, int l, int r)
{
    int x = a[l];
    for(int i = l; i < r; ++i){
        if()
    }
}

// [l, r)
int quickSelect(int *a, int l, int r, int index)
{
    int q = partition(a, l, r);
    if(q == index)
        return a[q];
    else
        return q < index ? quickSelect(a, q+1, r, index) : quickSelect(a, l, q, index);
}

