#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Solution {
public:
    virtual int strStr(string haystack, string needle) = 0;
};

class RollHash : public Solution {
public:
    virtual int strStr(string haystack, string needle)
    {
        long long MOD = pow(2, 32);
        int L = haystack.size(), N = needle.size();
        if (!N)
            return 0;
        if (L < N)
            return -1;
        long long needle_hash = 0, haystack_hash = 0;
        for (int i = 0; i < needle.size(); i++)
        {
            needle_hash = (needle_hash * 26 + needle[i] - 'a') % MOD;
            haystack_hash = (haystack_hash * 26 + haystack[i] - 'a') % MOD;
        }
        long long al = 1;
        for (int i = 0; i < N - 1; i++)
            al = (al * 26) % MOD;
        for (int i = 0; i < L - N + 1; ++i)
        {
            if (haystack_hash == needle_hash)
                return i;
            if (i == L - N + 1)
                return -1;
            haystack_hash = (haystack_hash - (al * (haystack[i] - 'a')) % MOD + MOD) % MOD;
            haystack_hash = (haystack_hash * 26) % MOD;
            haystack_hash = (haystack_hash + haystack[i + N] - 'a') % MOD;
        }
        return -1;
    }

};

class KMP : public Solution { 
public:
    virtual int strStr(string haystack, string needle){
        int m = haystack.size(), n = needle.size();
        if(!n) return 0;
        int dp[100000][26] = {{0}};      // dp[j][c]代表在状态j下，对应字符为c时应当转向的下一状态
        kmp(needle,dp);
        for(int j = 0,i = 0;i<m;i++) {
            j = dp[j][haystack[i]-'a'];     // 状态跳转
            if(j == n) return i - n + 1;    // 如果达到最终状态，则返回结果
        }                                   // 如果尚未到达，i进行偏移
        return -1;
    }
    void kmp(string needle, int dp[][26]){
        int n = needle.size();
        dp[0][needle[0]-'a'] = 1;
        for(int j = 1,x = 0;j < n; j++) {
            for(int a = 0; a < 26 ; a++){
                if(a == (needle[j]-'a'))
                    dp[j][a] = j+1;
                else {
                    dp[j][a] = dp[x][a];
                }
            }
            x = dp[x][needle[j] - 'a'];
        }
    }
};



int main(){
    string haystack = "baabbaaaaaaabbaaaaabbabbababaabbabbbbbabbabbbbbbabababaabbbbbaaabbbbabaababababbbaabbbbaaabbaababbbaabaabbabbaaaabababaaabbabbababbabbaaabbbbabbbbabbabbaabbbaa",
        needle = "bbaaaababa";
    Solution* p[4];
    p[0] = new RollHash;
    p[1] = new KMP;
    for(int i = 0;i<2;i++) {
        cout << p[i]->strStr(haystack, needle) << endl;
    }
    return 0;
}