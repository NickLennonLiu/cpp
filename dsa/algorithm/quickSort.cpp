// cmp(a,b) true if a > b, false if a <= b
// TODO: 快排的稳定性怎么保证？
template <typename T, typename CMP>
void quickSort(T *s, T *t, CMP &cmp)
{
    if (s == t - 1 || s == t)
        return;
    T key = *s;
    T *l = s, *r = t - 1;
    while (l != r)
    {
        while (r != l && cmp(*r, key))
            --r;
        if (r != l)
            *(l++) = *r;
        while (l != r && cmp(key, *l))
            ++l;
        if (l != r)
            *(r--) = *(l);
    }
    *(l) = key;
    quickSort(l + 1, t, cmp);
    quickSort(s, l, cmp);
}