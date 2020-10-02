#pragma once

void mergeSort(int *s, int *t)
{
    if (s == t || s == t - 1)
        return;
    auto len = (t - s) / 2;
    mergeSort(s, s + len);
    mergeSort(s + len, t);
    int *tmp = new int[t - s];
    auto i = s, j = s + len, k = tmp;
    while ((i != s + len) || (j != t))
    {
        while ((*i < *j || j == t) && i != s + len)
            *(k++) = *(i++);
        while ((*j <= *i || i == s + len) && j != t)
            *(k++) = *(j++);
    }
    while (k != tmp)
        *(--t) = *(--k);
    delete[] tmp;
}