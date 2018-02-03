#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

/*
 
 Binary Indexed Tree, build: O(N*lg N) time, query: O(lg N) time, N=Upper bound of the range
 
 - Data structure to query sum in a range
 - Typically used to count frequencies of values
 - Root of the tree covers the largest range
 - T[i] has sum in [i-2^r+1,i], r=position of least significant 1 bit
 
 References:
  - Ant book 3-3 data structures
  - https://en.wikipedia.org/wiki/Fenwick_tree
  - https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
  - https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)
 
 Usage:
  int N=ns.size();
  BIT f(N);
  for(int i=0; i<N; ++i) f.add(i,ns[i]);
  cout << f.query(4) << endl;
  f.add(4,10);
  cout << f.query(4) << endl;

 Used problems:
  - https://leetcode.com/problems/global-and-local-inversions/
 
 */
struct BIT {
public:
  int N;
  vector<int> T; // T[1..N] has values (1-based index)
  BIT(int N): N(N) {
    T.resize(N+1,0);
  }
  
  // query ∑ { sum[i] : i=0..p }
  int query(int r) {
    ++r; // 0-based index to 1-based index
    int res=0;
    while(r>0) {
      res+=T[r];
      r-=lsone(r);
    }
    return res;
  }
  
  // query ∑ { sum[i] : i=l..r }
  int query2(int l, int r) {
    assert(l<=r&&0<=l&&r<N);
    return query(r)-query(l-1);
  }
  
  // sum[i]+=x
  void add(int i, int x) {
    assert(0<=i&&i<=N);
    ++i; // 0-based index to 1-based index
    while(i<=N) {
      T[i]+=x;
      i+=lsone(i);
    }
  }
  
  // compute total inversions
  int inversions(vector<int> ns) {
    int N=ns.size(),res=0;
    for(int i=N-1; i>=0; --i) {
      res+=query(ns[i]-1);
      add(ns[i],1);
    }
    return res;
  }
private:
  int lsone(int i) { return i&-i; }
};

int main(int argc, char const *argv[]) {
  vector<int> ns={2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  
  // Range sum query
  int N=ns.size();
  BIT f(N);
  for(int i=0; i<N; ++i) f.add(i,ns[i]);
  assert(f.query(2)==4);
  assert(f.query(3)==7);
  f.add(3,6);
  assert(f.query(2)==4);
  assert(f.query(3)==13);
  
  // Inversion
  int V=*max_element(ns.begin(),ns.end());
  f=BIT(V);
  assert(f.inversions(ns)==3);
}
