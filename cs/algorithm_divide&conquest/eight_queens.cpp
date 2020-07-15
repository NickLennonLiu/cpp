#include <iostream>
using namespace std;


struct state;
const int SIZE = 8;
int sol_num;
void Print(state s);
bool isValid(state,int,int);
state GetNewState(state,int,int);

struct state{
    int Q[SIZE];
    bool row[SIZE],rdiag[2*SIZE-1],ldiag[2*SIZE-1];
};

void Try(int step,state s){
    if(step==8){
        ++sol_num;
        Print(s);
        return;
    }
    for(int i = 0; i < SIZE; ++i){
        if(isValid(s,step,i)){
            state next = GetNewState(s,step,i);
            Try(step+1,next);
        }
    }
    return;
}

state GetNewState(state old,int step,int i){
    old.Q[step] = i;
    old.row[i] = 0;
    old.ldiag[step+i] = 0;
    old.rdiag[step-i+SIZE-1] = 0;
    return old;
}

bool isValid(state s,int step,int i){
    return s.row[i] && s.ldiag[step+i] && s.rdiag[(step-i)+SIZE-1];
}

state InitialState(){
    state s;
    for(int i = 0;i<SIZE;++i){
        s.Q[i] = -1;
        s.row[i] = true;
    }
    for(int i = 0;i<SIZE*2-1;++i){
        s.ldiag[i] = s.rdiag[i] = true;
    }
    return s;
}

void Print(state s){
    for(auto i: s.Q){
        cout << i+1 << " ";
    }
    cout << endl;
}


int main(){
    state s = InitialState();
    Try(0,s);
    cout <<"Number of solutions: "<< sol_num<< endl;
    return 0;
}