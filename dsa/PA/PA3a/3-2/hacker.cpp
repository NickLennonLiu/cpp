#include "crc32.h"
#include <stdio.h>
// crc32(0, buf, len)

/*
若使用 5 层的嵌套for循环处理初始的字符串集合，
将被扣除10分的白盒分数。
散列
[ CRC32 是流式函数：将 buf1 的 CRC32 值作为初始值，
计算 buf2 的 CRC32 值，将得到 buf1 + buf2 的 CRC32 值，
你可以利用这一性质避免较为繁琐的字符串拼接操作。 ]
*/

char c[18] = {'0','1','2','3','4','5','6','7','8','9',
              't','s','i','n','g','h','u','a'};

int n;
unsigned char salt[5];
int saltcrc32;
long long int encrypted[1000000];
unsigned char salted[15];
unsigned char successed[9][9];


struct Hash
{
    void put(int e, unsigned char* M, int len);
};

unsigned char gen[6];
void init(Hash &hash, unsigned char *gen, int p)
{
    if(p == 5)
    {
        //hash.put(crc32(saltcrc32, gen, 5), gen, 5);
        return;
    }
    for(int i = 0; i < 18; ++i)
    {
        gen[p] = c[i];
        init(hash, gen, p+1);
    }
    if(p)
        //hash.put(crc32())
    return;
}

Hash hash;

int main()
{
    scanf("%d", &n);

    scanf("%s", salt);
    int saltlen = 0;
    while(salt[saltlen]) saltlen++;

    init(hash, gen, 0);

    for(int i = 0; i < n; ++i)
    {
        scanf("%x", encrypted[i]);
    }
    return 0;
}