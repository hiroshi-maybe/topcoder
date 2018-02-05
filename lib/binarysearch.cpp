#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

bool lte(int n, int k) {
  return n<=k;
}

/*
 
 Binary search, O(lg N) time
 
 max: [ok,ng), min: (ng,ok]
 move ok as long as `c` holds
 
 References:
  - https://twitter.com/meguru_comp/status/697008509376835584
    - Meguru style
  - https://qiita.com/hamko/items/794a92c456164dcc04ad
 
 */
int meguru(vector<int> ns, int ok, int ng, int k) {
  while(abs(ok-ng)>1) {
    int mid = (ng+ok)/2;
    bool c = ok<ng ? ns[mid]<=k : ns[mid]>=k;
    if (c) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  bool c = ok<ng ? ns[ok]<=k : ns[ok]>=k;
  return c ? ok : -1;
}

/*
 
 Ternary search to find index of a peak of real numbers, O(lg N) time
 
  - Find an index of peak
  - Highest value must be UNIQUE to expect deterministic result (Unimodality)
  - If there are multiple peaks, any of them is returned
  - Numbers must be STRICTLY increasing or decreasing
  - Typically used for "real number" to guarantee strictly increasing/decreasing and unimodality
 
 References:
  - https://en.wikipedia.org/wiki/Ternary_search
  - https://en.wikipedia.org/wiki/Unimodality
  - https://www.hackerearth.com/practice/algorithms/searching/ternary-search/tutorial/
  - http://naoyat.hatenablog.jp/entry/2012/01/04/231801
  - http://d.hatena.ne.jp/ir5/20090630/1246349028
  - http://d.hatena.ne.jp/nodchip/20090303/1236058357
 
 Used problems:
  - https://github.com/k-ori/leetcode/blob/master/162-Find-Peak-Element/FindPeak.cpp
 
 */
int tsearch(vector<double> ns) {
  int N=ns.size(), l=0, r=N-1;
  if(N==1) return 0;
  if(N==2) return ns[0]>ns[1]?0:1;
  while(abs(r-l)>2) {
    int ll=l+(r-l)/3,rr=r-(r-l)/3;
    if(ns[ll]<ns[rr]) l=ll;
    else r=rr;
  }
  if(ns[l]>ns[l+1]&&ns[l]>ns[r]) return l;
  if(ns[l+1]>ns[r]) return l+1;
  return r;
}

/*
 
 Ternary search to find index of a peak of integers, O(lg N) time
 
  - Find an index of peak
  - Highest value must be UNIQUE to expect deterministic result (Unimodality)
  - If there are multiple peaks, any of them is returned
  - Numbers must be STRICTLY increasing or decreasing
  - Use binary search to find max value which in strictly increasing part

 Ternary search on integers
  - http://codeforces.com/blog/entry/43440
  - http://codeforces.com/blog/entry/11497
  - https://apps.topcoder.com/forums/?module=Thread&threadID=670169&start=0

 Used problems:
 - https://github.com/k-ori/leetcode/blob/master/162-Find-Peak-Element/FindPeak.cpp
 
 */
int tsearch_int(vector<int> ns) {
  int N=ns.size(), good=0, bad=N;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    (ns[mid-1]<ns[mid]?good:bad)=mid;
  }
  return good;
}

void test(vector<int> ns, int k) {
  int N = ns.size();

  cout << "###################" << endl;
  cout << "test:" << k << endl;
  cout << "["<<0<<","<<N<<"):"; // max index which satisfies ns[u]>=k
  int u = meguru(ns, 0, N, k);
  cout << u << endl;

  int l = meguru(ns, N-1, -1, k);
  cout << "("<<-1<<","<<N-1<<"]:"; // min index which satisfies ns[l]<=k
  cout << l << endl;

  cout << "upper_bound():" << distance(ns.begin(), upper_bound(ns.begin(), ns.end(), k)) << endl; // upper bound = 7
  cout << "lower_bound():" << distance(ns.begin(), lower_bound(ns.begin(), ns.end(), k)) << endl; // lower bound = 3
}

int main(int argc, char const *argv[]) {
  // ns[3..6] = 3
  vector<int> ns = {1,2,2,3,3,3,3,5,7,7};
  for(auto &n: ns) cout << n << ",";
  cout << endl;

  test(ns,3);
  test(ns,0);
  test(ns,7);
  test(ns,8);
  
  vector<double> unimodal1 = {0,2,3,5,4,3,2,1,0,-1,-2,-3};
  vector<int> unimodal1i = {0,2,3,5,4,3,2,1,0,-1,-2,-3};
  assert(tsearch(unimodal1)==3);
  assert(tsearch_int(unimodal1i)==3);
  vector<double> unimodal2 = {12,11,10,9,8,7,6,5,4,3,2,1};
  vector<int> unimodal2i = {12,11,10,9,8,7,6,5,4,3,2,1};
  assert(tsearch(unimodal2)==0);
  assert(tsearch_int(unimodal2i)==0);
  vector<double> unimodal3 = {1,2,3,4,5,6,7,8,9,10,11,12};
  vector<int> unimodal3i = {1,2,3,4,5,6,7,8,9,10,11,12};
  assert(tsearch(unimodal3)==11);
  assert(tsearch_int(unimodal3i)==11);
  vector<double> non_unimodal = {1,2,3,10,13,23,33,43,43,43,0,-10};
  vector<int> non_unimodali = {1,2,3,10,13,23,33,43,43,43,0,-10};

  assert(7<=tsearch(non_unimodal)&&tsearch(non_unimodal)<=9); // returns 8
  assert(7<=tsearch_int(non_unimodali)&&tsearch_int(non_unimodali)<=9); // returns 7
  
  // Ternary search does not work for this case
  // vector<double> non_strict = {1,1,1,1,1,1,1,2};
  // vector<int> non_stricti = {1,1,1,1,1,1,1,2};
  // assert(tsearch(non_strict)==7);
  // assert(tsearch_int(non_stricti)==7);
}
