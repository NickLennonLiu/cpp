#pragma once

int binSearch(int s[], int lo, int hi, int e)
{
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (e < s[mid])
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo - 1;
}