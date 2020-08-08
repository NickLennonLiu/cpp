#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <future>
using namespace std;

//为目标线程传入promise的指针来设置返回结果
void check_num(int num, promise<bool>* res_promise) {
  if (num == 1) {
	res_promise->set_value(false);
	return; } 
  for (int i = sqrt(num); i > 1; i--)
	if (num % i == 0) {
	  res_promise->set_value(false);
	  return; }
	res_promise->set_value(true);
}



int main() {
 int num = 194232491;
 //设置promise，通过promise的get_future()接口获取配对的future
 //bool是目标线程返回内容的类型
 promise<bool> res_promise;
 future<bool> res_future = res_promise.get_future();
 //向目标线程中传入promise的指针，promise和future保证了线程间结果传递，
 //因此可以detach目标线程，让目标线程完全独立于当前线程
 thread worker(check_num, num, &res_promise);
 worker.detach();
 //通过future的get()获取结果，之前已经介绍过了
 if (res_future.get())
   cout << num << " is a prime number" << endl;
 else
   cout << num << " is not a prime number" << endl;
 return 0;
}
