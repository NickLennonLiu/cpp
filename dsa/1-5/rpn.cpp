#include <iostream>
#include "Stack.h"
#include "polynomial.h"
using namespace std;

#define M 1000000007

/*
polynomial 0
x 1
+ 2
- 3
* 4 
^ 5
( 6
) 7

*/

int get_num(char s[], int& pos)
{
    int read = 0;
    while(s[pos] <= '9' && s[pos] >= '0')
    {
        read = (read * 10 + s[pos] - '0') % M;
        ++pos;
    }
    --pos;
    //cout << "Read a number: " << read << endl;
    return read;
}

// 返回运算符的优先级
int priority(int type)
{
    switch(type)
    {
        case 2: return 1;
        case 3: return 1;
        case 4: return 2;
        case 5: return 3;
        default: return 0;
    }
    return 0;
}

inline void calculate(Stack<Polynomial> &stack, const Polynomial& op)
{
    Polynomial a,b;
    b = stack.pop();
    a = stack.pop();
    switch (op.type())
    {
    case 2:stack.push(a+b);break;
    case 3:stack.push(a-b);break;
    case 4:stack.push(a*b);break;
    case 5:stack.push(a^b.coeffecient(0));break;
    default:
        break;
    }
}

void rpn(Stack<Polynomial> &stack, char s[])
{
    Stack<Polynomial> op;
    int idx = 0;
    Polynomial a;
    while(s[idx] != 0)
    {
        //cout << "Debug: s[idx]: " << s[idx] << " ----------\n";
        switch(s[idx])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': 
            {
                a = Polynomial(get_num(s, idx));
                stack.push(a);
                break;
            }
            case 'x': 
            {
                if (idx > 0 && s[idx - 1] != 'x' && s[idx-1]!='(' && s[idx - 1] != '*' && s[idx - 1] != '-' && s[idx - 1] != '+')
                {
                    // 可能要考虑插入乘号之前处理先前的优先级更高的^
                    if(!op.empty() && op.top().type() == 5)
                    {
                        //stack.push(op.pop());
                        //cout << "Pushed a ^ into stack" << endl;
                        calculate(stack,op.pop());
                    }
                    //
                    op.push(a = Polynomial(0,4));   // 推入被省略的乘号
                    //cout << "Pushed a * into op" << endl;
                }
                stack.push(a = Polynomial(0,1));   // 推入x
                //cout << "Pushed a x into stack" << endl;
                break;
            }
            case '+': 
            {
                while (!op.empty() && priority(op.top().type()) > 1)
                {
                    cout << op.top().type() << endl;
                    //stack.push(op.pop());
                    calculate(stack, op.pop());
                    //cout << "Pushed a */^ into stack" << endl;
                }
                    
                op.push(a = Polynomial(0,2));
                //cout << "Pushed a + into op" << endl;
                break;
            }
            case '-': 
            {
                while (!op.empty() && (priority(op.top().type()) > 1 || op.top().type() == 3))
                {
                    //stack.push(op.pop());
                    calculate(stack, op.pop());
                    //cout << "Pushed a */^/- into stack" << endl;
                }
                op.push(a = Polynomial(0,3));
                //cout << "Pushed a - into op" << endl;
                break;
            }
            case '*': 
            {
                while (!op.empty() && priority(op.top().type()) > 2)
                {
                    //stack.push(op.pop());
                    calculate(stack, op.pop());
                    //cout << "Pushed a ^ into stack" << endl;
                }          
                op.push(a = Polynomial(0,4));
                //cout << "Pushed a * into op" << endl;
                break;
            }
            case '^': 
            {
                while (!op.empty() && (op.top().type() == 5))
                {
                    //stack.push(op.pop());
                    calculate(stack,op.pop());
                    //cout << "Pushed a ^ into stack" << endl;
                }
                //cout << "Pushed a ^ into op" << endl;
                op.push(a = Polynomial(0,5));
                break;
            }
            case '(':
            {
                if(idx && s[idx-1] != '(' && s[idx-1] != '+' && s[idx-1] != '-' && s[idx-1] != '*')
                {
                    // 可能要考虑插入乘号之前处理先前的优先级更高的^
                    if(!op.empty() && op.top().type() == 5)
                    {
                        //stack.push(op.pop());
                        //cout << "Pushed a ^ into stack" << endl;
                        calculate(stack,op.pop());
                    }
                    //
                    op.push(a = Polynomial(0,4));   // 推入被省略的乘号
                    //cout << "Pushed a * into op" << endl;
                }
                op.push(a = Polynomial(0,6));
                //cout << "Pushed a ( into op" << endl;
                break;
            }
            case ')':
            {
                while(!op.empty() && op.top().type() != 6)
                {
                    //stack.push(op.pop());
                    calculate(stack, op.pop());
                    //cout << "Pushed something into stack:" << stack.top().type() << endl;
                }
                op.pop();
                //cout << "Poped a left( " << op.pop().type() << endl;
                break;
            }
            default: break;
        }
        ++idx;
    }
    //cout << op.size() << " " << stack.size() << endl;
    while(!op.empty())
    {
        calculate(stack, op.pop());
    }
}


int main()
{
    char exp[1000000];
    scanf("%s", exp);
    Stack<Polynomial> stack;
    //Queue<Polynomial> RPN;
    rpn(stack, exp);
    Polynomial result = stack.pop();
    //cout << result.rank() << endl;
    
    for(int i = result.rank();i >= 0; --i)
    {
        cout << result.coeffecient(i) << " ";
    }
    
    /*
    while(!RPN.empty())
    {
        Polynomial cur = RPN.pop_front();
        cout << cur.type() << " ";
    }
    */
    return 0;
}