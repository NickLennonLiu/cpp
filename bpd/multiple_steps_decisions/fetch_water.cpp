//未完成，关于重复步骤的检测和去重需要重写。

#include <iostream>
#include <vector>
using namespace std;

const int A_SIZE = 9, B_SIZE = 4, TARGET = 6;
enum op {a_fill,b_fill,a_emp,b_emp,a_to_b,b_to_a};
int sol_cnt = 0;


struct state{
    int a,b;
};

bool succeed(state s){
    return (s.a==TARGET||s.b==TARGET);
}

state getNewState(state s,op a){
    switch (a)
    {
    case a_fill:
        s.a = A_SIZE;
        break;
    case b_fill:
        s.b = B_SIZE;
        break;
    case a_emp:
        s.a = 0;
        break;
    case b_emp:
        s.b = 0;
        break;
    case a_to_b:
        if(s.a >= (B_SIZE-s.b)){
            s.a -= B_SIZE - s.b;
            s.b = B_SIZE;
        }
        else{
            s.b += s.a;
            s.a = 0;
        }
        break;
    case b_to_a:
        if(s.b >= (A_SIZE-s.a)){
            s.b -= A_SIZE - s.a;
            s.a = A_SIZE;
        }
        else{
            s.a += s.b;
            s.b = 0;
        }
        break;
    default:
        break;
    }
    return s;
}

bool been(vector<state>& trait,state s){
    for(auto i:trait){
        if(i.a==s.a&&i.b==s.b) return true;
    }
    return false;
}

state InitialState(){
    state s;
    s.a = s.b = 0;
    return s;
}

void printMethod(vector<state>& trait,vector<op>& ops,state final);
void Try(vector<state>& trait,vector<op>& ops,state s){
    if(succeed(s)){
        //for(auto i:ops) cout << i << " ";
        printMethod(trait,ops,s);
        sol_cnt++;
        return;
    }
    for(int i = 0;i<6;++i){
        state next = getNewState(s,op(i));
        if(been(trait,next)) continue;
        trait.push_back(next);
        ops.push_back(op(i));
        Try(trait,ops,next);
        //trait.pop_back();
        ops.pop_back();
    }
    //cout << endl;
}

void printMethod(vector<state>& trait,vector<op>& ops,state final){
    auto size = trait.size();
    for(int i = 0;i<size;++i){
        cout << trait[i].a << " " << trait[i].b << endl;
        cout << "--";
        switch (ops[i])
        {
        case a_fill:
            cout << "Fill A";
            break;
        case b_fill:
            cout << "Fill B";
            break;
        case a_emp:
            cout << "Empty A";
            break;
        case b_emp:
            cout << "Empty B";
            break;
        case a_to_b:
            cout << "From A to B";
            break;
        case b_to_a:
            cout << "From B to A";
            break;
        default:
            break;
        }
        cout << "-->" << endl;
    }
    cout << final.a << " " << final.b << endl;
    cout << endl;
}

int main(){
    state ini = InitialState();
    vector<state> trait;
    vector<op> ops;
    trait.push_back(ini);
    Try(trait,ops,ini);
    cout << sol_cnt << endl;
    return 0;
}