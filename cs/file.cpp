#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(){
    string filename;
    ifstream fin;
    string name;
    char sex;
    long int id;
    int score;

    cout << "Please input the file name:" << endl;
    cin >> filename;

    fin.open(filename);
    if(fin){
        cout << "Successfully opened the file!" << endl;
    }
    else cout << "File not found!" << endl;
    while(!fin.eof()){
        fin >> name >> id >> score;
    }
    cout << name << id << score;
    fin.close();
    return 0;
}

