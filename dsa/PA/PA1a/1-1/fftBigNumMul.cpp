#include <iostream>
#include <cstring>
#include "fft.cpp"
using namespace std;

int main()
{
    char a[5000], b[5000];
    Complex an[10001], bn[10001];
    cin.getline(a, 5000);
    cin.getline(b, 5000);
    int alen = strlen(a), blen = strlen(b);
    //cout << alen << " " << blen << endl;
    int totallen = 1;
    while(totallen < (alen + blen + 1)) totallen <<=1 ;
    //cout << "totallen" << totallen << endl;
    for(int i = alen;i>0;i--) an[alen-i] = Complex(a[i-1] - '0', 0);
    for(int i = blen;i>0;i--) bn[blen-i] = Complex(b[i-1] - '0', 0);

    DFT(an, totallen, 1), DFT(bn, totallen, 1);

    for(int i = 0;i<totallen;i++) an[i] = an[i] * bn[i];

    DFT(an, totallen, -1);

    for (int i = 0; i < totallen; i++) cout << int(an[i].re + 0.5) << " ";
    cout << endl;
    return 0;
}