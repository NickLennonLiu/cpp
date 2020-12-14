/*
分析：
A的长度为n
子串长度为k的可能性 2^k
A中长度为k的子串n-k+1个
2^k > n-k+1 
2^k + k - 1 >= 2^k
k最多不会超过log n = 24
*/
#include <cstdio>
#include <stdlib.h>
