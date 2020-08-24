#include <string>
#include <queue>
using namespace std;

class Solution
{
public:
    string countAndSay(int n)
    {
        queue<char> app;
        app.push('1');
        while (--n)
        {
            int s = app.size(), i = 0;
            while(i<s){
                char c = app.front();
                int cnt = 0;
                while(app.front()==c && i < s){
                    app.pop();
                    cnt++;
                    i++;
                }

                for(char x: to_string(cnt)) app.push(x);

                app.push(c);
            }
        }
        string ans;
        while(!app.empty()){
            ans += app.front();
            app.pop();
        }
        return ans;
    }
};