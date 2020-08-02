#include <iostream>
using namespace std;

class Instrument{
public:
    void play(){ cout << "Instrument::play" << endl;}
};
class Wind:public Instrument{
public:
    void play(){ cout << "Wind::play" << endl;}
};
void tune(Instrument* i){
    (*i).play();
}
int main(){
    Wind flute;
    tune(&flute);                // Instrument::play
    Instrument &inst = flute;
    inst.play();                // Instrument::play
    return 0;
}