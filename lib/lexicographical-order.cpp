#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

/*
 
 Generate n numbers in lexicographical order, O(n) time
 
 https://leetcode.com/problems/lexicographical-numbers/
 
 */
vector<int> lexicalOrder(int n) {
  vector<int> res;
  int x = 1;
  for(int _=0; _<n; ++_) {
    res.push_back(x);
    if ((long long)x*10<=n) {
      x*=10; //1,10,100,..
    } else {
      //101,102,.. or  499
      while (x==n||x%10== 9) x/=10; // Remove the last digit
      x++;
    }
  }
  return res;
}

int main(int argc, char const *argv[]) {
  vector<int> a13 = lexicalOrder(13);
  vector<int> e13 = {1,10,11,12,13,2,3,4,5,6,7,8,9};
  assert(a13 == e13);
}
