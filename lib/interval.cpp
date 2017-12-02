#include <iostream>
#include <sstream>
#include <cassert>
#include <utility>

using namespace std;
#define dumpAR(ar) for(auto &x : (ar)) { cout << x << ','; } cout << endl;

/*
 
 Compute overlapped interval of given two intervals, O(1) time
 
 There are three cases:
 
 case 1:
  i1 ●--------◦
  i2  ●----◦
 -> [l2,r2)

 case 2:
  i1 ●---◦
  i2  ●----◦
 -> [l2,r1)
 
 case 3:
  i1 ●---◦
  i2       ●---◦
  -> [l2,r1) l2>r1
 
 https://discuss.leetcode.com/topic/111198/java-c-clean-code-with-explanation
 
 Usage:
 pair<int,int> x=overlap({0,1}, {2,3}); // x={2,1} (no overlap)
 
 */
pair<int,int> overlap(pair<int,int> i1, pair<int,int> i2) {
  int l1=i1.first,r1=i1.second,l2=i2.first,r2=i2.second;
  if(l1>r1) swap(l1,r1);
  if(l2>r2) swap(l2,r2);
  return make_pair(max(l1,l2), min(r1,r2));
}

int main(int argc, char const *argv[]) {
  // case 1
  auto a=overlap({0,10},{2,8});
  assert(a.first==2&&a.second==8);
  assert(a.first<a.second);

  // case 2
  auto b=overlap({0,8},{2,10});
  assert(b.first==2&&b.second==8);
  assert(b.first<b.second);
  
  // case 3
  auto c=overlap({0,2},{8,10});
  assert(c.first==8&&c.second==2);
  assert(c.first>c.second);

  auto d=overlap({0,1},{1,10});
  assert(d.first==1&&d.second==1);
  assert(d.first==d.second);
}
