#include <iostream>
using namespace std;

int p[100];
int n;
int m[100][100], s[100][100];

void init() {
    cin >> n;
    for(int i = 0;i < n+1;i++) cin >> p[i];
}

void matrix_chain() {
    for(int i = 1;i<=n;i++) m[i][i] = 0;

    for(int len = 2;len<=n;len++) 
    {
        for(int i = 1;i<=n-len+1;i++) 
        {
            int j = i+len-1;
            m[i][j] = 10000000;
            for(int k = i;k<=j;k++)
            {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j]) 
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void print_split(int i,int j) {
    if(i==j) 
        cout << "A" << i;
    else if(i==1&&j==n){
        print_split(i, s[i][j]);
        print_split(s[i][j]+1, j);
    }
    else {
        cout << "(";
        print_split(i,s[i][j]);
        print_split(s[i][j]+1,j);
        cout << ")";
    }
}

int main(){
    init();
    matrix_chain();
    print_split(1,n);
    cout << endl;
    return 0;
}