//Unfinished, I think I will just pass it.

#include <iostream>
using namespace std;

struct state{
    int P,G;
};

bool Safe(state s){
    if(s.P!=3&&s.P!=0&&s.P!=s.G) return false;
    else return true;
}

state s[20];
int choice[20] = {0};
int k;

state d[6] =  {{2,0},{1,0},{1,1},{0,1},{0,2}};

void display();
void transfer_state();

void transfer_state(){
    k = 1;
    s[1].P = 3;
    s[1].G = 3;
    do{
        int fx = 1;
        if(k%2) fx = -1;
        int i;
        //
        //
        if(i>5){choice[k+1]=0;k--;}
    }while(!(s[k].P==0&&s[k].G==0));
}

int main(){
    transfer_state();
    display();
    return 0;
}