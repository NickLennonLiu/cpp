#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void test(int seconds, int num) {
    this_thread::sleep_for(chrono::seconds(seconds));
    cout << "The num is " << num << endl;
}

void example_1() {
    thread s1;  // create an empty thread obj
    
    thread t1(test, 2, 0);  // test是入口函数，2,0是该函数的参数Args
    thread t2(test, 3, 1);
    t1.join();
    t2.join();
}

void example_2(){
    thread t1(test, 3, 0);
    t1.join();  // t1.join()将阻塞主线程，直到t1指向的线程执行完3秒的延时
    this_thread::sleep_for(chrono::seconds(6));
}

void example_3()
{
    thread t1(test, 3, 0);
    this_thread::sleep_for(chrono::seconds(6));
    // t1指向的线程的延时与当前线程的延时将同时开始
    t1.join(); 
    // 由于t1指向的线程在3秒时已经完成运行，此处t1.join()无法阻塞当前线程
}

void example_4()
{
    thread t1(test, 3, 0);
    t1.detach(); 
    // 与t1.join()不同，t1.detach()让t1指向的线程与当前线程脱钩，两者独立
    // 当前线程的延时操作不会被阻塞
    this_thread::sleep_for(chrono::seconds(6));
}

void example_5()
{
    thread t1;
    thread t2(test, 3,0);
    t1 = move(t2);
    t1.join();
}

int main(){
    example_4();
    return 0;
}