#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

/*
 
 Range minimum query by segment tree, O(N) time to build, O(lg N) time to query or update
 
  - Data structure to query in range
  - Segment tree is applicable as long as result to be queried is associative
   - Range sum query
   - Range GCD query
  - Update `int operate(a,b)` method to reuse for diffirent query
  - Needs 2*X-1 space, where X = min { n : N<=2^n }
   - X leaves + X-1 parents
   - Data is populated in 0-indexed
 
  References:
   - Ant book 3-3 data structures
   - https://www.slideshare.net/hcpc_hokudai/rmq-47663507
   - https://www.slideshare.net/iwiwi/ss-3578491?next_slideshow=1
   - https://en.wikipedia.org/wiki/Segment_tree
   - https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/
 
  Usage:
 
   SegmentTree T(X.size());
   T.build(X);
   cout << T.query(3,17) << endl;
   T.update(12,5);
   cout << T.query(3,17) << endl;

  Used problems:
   - https://github.com/k-ori/leetcode/blob/master/307-Range-Sum-Query/RangeSumQuery.cpp (RSQ)
 
 */
struct SegmentTree {
public:
  int N;
  SegmentTree(int N): N(N) {
    int n=1;
    // Make vector size power of 2
    while(n<N) n<<=1;
    T.resize(2*n-1,iV);
  }
  
  // Initialize tree with `ns`
  void build(vector<int> &ns) {
    assert(ns.size()<=T.size());
    buildTree(ns,0,0,N);
  }
  
  void update(int i, int x) {
    updateTree(i,x,0,0,N);
  }
  
  // query in range [L,R)
  int query(int L, int R) {
    return queryTree(L,R,0,0,N);
  }
  
  // ⚠️ Override point
  // Note that operation should be associative A`op`(B`op`C) == (A`op`B)`op`C
  const int iV=1e9;
  int operate(int a, int b) {
    return min(a,b); // RMQ
  }
private:
  vector<int> T; // T[1..N] has values (1-based index)
  // T[i] manages query result in index range [l,r)
  void buildTree(vector<int> &ns, int i, int l, int r) {
    if (l==r-1) { T[i]=ns[l]; return; }
    
    int mid=l+(r-l)/2;
    buildTree(ns,2*i+1,l,mid); // left child
    buildTree(ns,2*i+2,mid,r); // right child
    
    T[i]=operate(T[2*i+1],T[2*i+2]);
  }
  
  void updateTree(int p, int x, int i, int l, int r) {
    if (l==r-1) { T[i]=x; return; }
    
    int mid=l+(r-l)/2;
    if(p<mid) updateTree(p,x,2*i+1,l,mid);
    else       updateTree(p,x,2*i+2,mid,r);
    
    T[i]=operate(T[2*i+1],T[2*i+2]);
  }
  
  int queryTree(int L, int R, int i, int l, int r) {
    // out of range
    if (r<=L||R<=l) return iV;
    
    // match
    if (L<=l&&r<=R) return T[i];
    
    int mid=l+(r-l)/2;
    int res=iV;
    int a=queryTree(L,R,2*i+1,l,mid);
    int b=queryTree(L,R,2*i+2,mid,r);
    res = operate(res,a);
    res = operate(res,b);
    return res;
  }
};

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
  - https://github.com/k-ori/leetcode/blob/master/307-Range-Sum-Query/RangeSumQuery.cpp
 
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
  int query(int l, int r) {
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
  
  // sum[i]=x
  void update(int i, int x) {
    int v1=query(i)-query(i-1);
    add(i,x-v1);
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
  
  // Range minimum query
  SegmentTree T(N);
  T.build(ns);
  assert(T.query(2,8)==1);
  assert(T.query(3,8)==2);
  T.update(5,-1);
  assert(T.query(2,8)==-1);
}
