#include <iostream>
using namespace std;

int board[1000][2];
int n;

bool dfs(int money, int pos, bool stay)
{
    if(money < 0) return false;
    if(pos >= n-1)
    {
        if(board[n-1][0] == 0)
            money -= board[n-1][1];
        if(money < 0) return false;
        return true;
    }
    if(stay && board[pos][0])
    {
        return dfs(money, pos + board[pos][1], false);
    }
    if(!board[pos][0])
    {
        money -= board[pos][1];
        if(money < 0) return false;
    }
    if(dfs(money, pos+1, true)) return true;
    return dfs(money, pos+2, true);
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i = 0; i < 1000; ++i)
            board[n][1] = board[n][0] = 0;
        for(int i = 0; i < n; ++i)
        {
            char op;
            cin >> op >> board[i][1];
            board[i][0] = (op == 'A') ? 0 : 1;
        }
        cout << (dfs(8,0,true) ? "Yes" : "No") << endl;
    }
    return 0;
}