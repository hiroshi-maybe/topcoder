#include <iostream>
#include <chrono>
using namespace std;

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG measure.cpp && ./a.out -s

long long fib(int x) { return x<=1?x:(fib(x-1)+fib(x-2)); }

void test_measure() {
  auto start = chrono::high_resolution_clock::now();
  auto measure=[&]() -> int {
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    start = stop;
    return duration.count();
  };

  for(int i=30; i<=45; ++i) {
    long long a=fib(i);
    cout<<a<<endl;
    cout<<"fib("<<i<<")="<<a<<", "<<measure()<<" (msec)"<<endl;
  }
}

int main(int argc, char const *argv[]) {
  test_measure();
  return 0;
}
