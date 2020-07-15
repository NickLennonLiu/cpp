#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

struct MenuItem {
    int code;
    char name[10];
    float price;
};

int main(){
    cout << setiosflags(ios::showpoint | ios::fixed | ios::right) << setprecision(2);
    MenuItem items[10];
    ifstream fin("menu.txt");
    int index = 0;
    try{
        if(fin) cout << "Successfully opened the menu!" << endl;
        else throw(runtime_error("File doesn't exsits!"));
    }
    catch(runtime_error err){
        cout << err.what() << endl;
    }
    while(!fin.eof()){
        fin >> items[index].code >> items[index].name >> items[index].price;
        index ++;
    }
    for(int i = 0;i<index;++i){
        cout << items[i].code << " " << items[i].name << " " << items[i].price << endl;
    }
    int order[10];
    float total = 0;
    for (int i = 0; i < index; ++i)
    {
        cout << "想要多少" << items[i].name << "？：";
        cin >> order[i];
        cout << endl;
    }

    cout << "订单：\n菜名    个数\n";

    for (int i = 0; i < index; ++i)
    {
        if(!order[i]) continue;
        cout << items[i].name << " " <<setw(4)<< order[i] << endl;
        total += order[i] * items[i].price;
    }
    cout << "总价： "<< total << endl;

    return 0;
}