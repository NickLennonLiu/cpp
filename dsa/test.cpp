#include <stdio.h>
#include <cstring>
using namespace std;

int main()
{
    char a[100], b[100];
    scanf("%s %s", a, b);
    printf("%s\n%s\n", a, b);
    printf("%d,%d", strlen(a), strlen(b));
    return 0;
}