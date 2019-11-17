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
   - X leaves (i=X-1..2*X-2) + X-1 parents (i=0..X-2)
   - Data is populated in 0-indexed
 
  References:
   - Ant book 3-3 data structures
   - https://www.slideshare.net/hcpc_hokudai/rmq-47663507
   - https://www.slideshare.net/iwiwi/ss-3578491?next_slideshow=1
   - https://en.wikipedia.org/wiki/Segment_tree
   - https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/
   - https://cp-algorithms.com/data_structures/segment_tree.html
 
  Usage:
 
   SegmentTree T(X.size());
   T.build(X);
   cout << T.query(3,17) << endl;
   T.update(12,5);
   cout << T.query(3,17) << endl;

  Used problems:
   - https://github.com/k-ori/leetcode/blob/master/307-Range-Sum-Query/RangeSumQuery.cpp (RSQ)
   - https://github.com/k-ori/csacademy/blob/master/solutions/R78-StrangeMatrix.cpp#L88
   - https://github.com/k-ori/codeforces/blob/master/solutions/ArrayRestoration.cpp#L164 (RMQ)
   - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/Company.cpp#L90 (RMQ)
   - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/VasyaAndMaximumProfit.cpp#L78 (Max subsegment sum query)
   - https://github.com/hiroshi-maybe/GCJ/blob/master/kickstart/2019-RB/DiverseSubarray.cpp#L70 (Max subsegment sum query)
 
 */
// 🛠 Customize node of segment tree
struct Node {
  static const int Id=1e9;
  int val;
  Node(int val=Id): val(val) {}
  static Node IDE; // Identity element in monoid
};
// Merge operation should be associative A`op`(B`op`C) == (A`op`B)`op`C
Node Node::IDE=Node();
Node merge(const Node &a, const Node &b) {
  return Node(min(a.val,b.val));
}
// 🛠 Customize node of segment tree

struct SegmentTree {
public:
  int N__;
  vector<Node> Tree;
  SegmentTree(int N) {
    int n=1;
    // Init by power of 2
    while(n<N) n<<=1;
    this->Tree=vector<Node>(2*n,Node::IDE);
    this->N__=n;
  }
  // Initialize tree with `ns`
  void build(const vector<Node> &ns) {
    buildTree(ns,0,0,N__);
  }
  // Update k-th (0-indexed) value
  void update(int i, const Node &x) {
    updateTree(i,x,0,0,N__);
  }
  // query in range [L,R)
  Node query(int L, int R) {
    return queryTree(L,R,0,0,N__);
  }
private:
  void buildTree(const vector<Node> &ns, int i, int l, int r) {
    if (l==r-1) {
      if(l<ns.size()) Tree[i]=ns[l];
      return;
    }
    int mid=l+(r-l)/2;
    buildTree(ns,2*i+1,  l,mid); // left child
    buildTree(ns,2*i+2,mid,  r); // right child
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  void updateTree(int p, const Node &x, int i, int l, int r) {
    if (l==r-1) { Tree[i]=x; return; }
    int mid=l+(r-l)/2;
    if(p<mid) updateTree(p,x,2*i+1,  l,mid);
    else      updateTree(p,x,2*i+2,mid,  r);
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  Node queryTree(int L, int R, int i, int l, int r) {
    // out of range
    if (r<=L||R<=l) return Node::IDE;
    // all covered
    if (L<=l&&r<=R) return Tree[i];
    // partially covered
    int mid=l+(r-l)/2;
    Node a=queryTree(L,R,2*i+1,  l,mid);
    Node b=queryTree(L,R,2*i+2,mid,  r);
    Node res=merge(a,b);
    return res;
  }
};
void test_segmenttree() {
  vector<int> ns={2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  int N=ns.size();
  
  // Range minimum query
  SegmentTree T(N);
  vector<Node> X;
  for(int i=0; i<N; ++i) X.push_back(ns[i]);
  T.build(X);
  
  assert(T.query(2,8).val==1);
  assert(T.query(3,8).val==2);
  T.update(5,-1);
  assert(T.query(2,8).val==-1);
}

/*
 
 RMQ (segment tree), O(lg N) query, O(lg N) update
 
 - normal: range query, point update
 - lazy propagation: point query, range update
 
 References:
  - https://www.npca.jp/works/magazine/2015_5/
 
 Used problem:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/Company.cpp#L174
  - https://github.com/hiroshi-maybe/atcoder/blob/master/solutions/Roadwork.cpp#L72
   - lazy propagation (range update)
  - https://github.com/hiroshi-maybe/leetcode/blob/master/1124-longest-well-performing-interval/longest-well-performing-interval.cpp#L50
   - range min query
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/YetAnotherMonsterKillingProblem.cpp#L44
   - range min query
 
 */
template <class T> struct RMQ {
public:
  T Inf;
  vector<T> A;
  int SIZE; // normalized size of original array
  T merge(T a, T b) { return min(a,b); }
  RMQ(int N, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(N);
    this->A=vector<T>(2*SIZE,Inf);
  }
  // O(N) initialization
  RMQ(vector<T> &X, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(X.size());
    this->A=vector<T>(2*SIZE,Inf);
    for(int i=0; i<X.size(); ++i) A[i+SIZE-1]=X[i];
    for(int i=SIZE-2; i>=0; --i) {
      A[i]=merge(A[2*i+1],A[2*i+2]);
    }
  }
  void update(int i, T v) {
    i+=SIZE-1;
    A[i]=v;
    while(i>0) {
      i=(i-1)/2;
      A[i]=merge(A[2*i+1],A[2*i+2]);
    }
  }
  // half-open range [ql,qr)
  T query(int ql, int qr) {
    return qu(ql,qr,0,0,SIZE);
  }
private:
  // i: node index (<SIZE if not leaf)
  T qu(int ql, int qr, int i, int l, int r) {
    if(qr<=l||r<=ql) return Inf;
    if(ql<=l&&r<=qr) return A[i];
    int m=(l+r)/2;
    
    return merge(qu(ql,qr,2*i+1,l,m),qu(ql,qr,2*i+2,m,r));
  }
  int calcsize(int N) {
    int n=1; while(n<N) n<<=1;
    return n;
  }
};
template <class T> struct RMQ_lazy {
public:
  T Inf;
  vector<T> A;
  int SIZE; // normalized size of original array
  RMQ_lazy(int N, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(N);
    this->A=vector<T>(2*SIZE,Inf);
  }
  // O(N) initialization
  RMQ_lazy(vector<T> &X, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(X.size());
    this->A=vector<T>(2*SIZE,Inf);
    for(int i=0; i<X.size(); ++i) A[i+SIZE-1]=X[i];
    for(int i=SIZE-2; i>=0; --i) {
      A[i]=min(A[2*i+1],A[2*i+2]);
    }
  }
  T query(int i) {
    i+=SIZE-1;
    T res=A[i];
    while(i>0) i=(i-1)/2,res=min(res,A[i]);
    return res;
  }
  // range update [ql,qr)
  void update(int ql, int qr, T v, int i=0, int l=-1, int r=-1) {
    if(l==-1) l=0,r=SIZE;
    if(qr<=l||r<=ql) return;
    if(ql<=l&&r<=qr) { A[i]=min(A[i],v); return; }
    int m=(l+r)/2;
    update(ql,qr,v,2*i+1,l,m),update(ql,qr,v,2*i+2,m,r);
  }
  int calcsize(int N) {
    int n=1; while(n<N) n<<=1;
    return n;
  }
};
void test_rmq() {
  vector<int> ns={2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  
  // Range minimum query
  RMQ<int> rmq(ns,1e9);

  assert(rmq.query(2,8)==1);
  assert(rmq.query(3,8)==2);
  rmq.update(5,-1);
  assert(rmq.query(2,8)==-1);
  
  RMQ<pair<int,int>> rmq2(ns.size(),{1e9,-1});
  for(int i=0; i<ns.size(); ++i) rmq2.update(i,{ns[i],i});
  
  assert(rmq2.query(2,8)==make_pair(1,2));
  assert(rmq2.query(3,8)==make_pair(2,4));
  rmq2.update(5,{-1,5});
  assert(rmq2.query(2,8)==make_pair(-1,5));
}

/*
 
 Binary Indexed Tree, build: O(N*lg N) time, query: O(lg N) time, N=Upper bound of the range (exclusive)
 
 - Data structure to query sum in a range
 - Typically used to count frequencies of values
 - Queries sum in range [0..N)
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
  - https://github.com/k-ori/codeforces/blob/master/solutions/PetrAndPermutations.cpp#L90
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/PetyaAndArray.cpp#L89
   - sparse frequency query by coordinate compression
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/Tree.cpp#L222
   - prefix sum in Eler tour tree
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/LunarNewYearAndFoodOrdering.cpp#L48
  - https://github.com/hiroshi-maybe/atcoder/blob/master/solutions/EnclosedPoints.cpp#L81
  - https://github.com/hiroshi-maybe/GCJ/blob/master/kickstart/2019H/Hindex.cpp#L44
 
 */
template <typename T> struct BIT {
public:
  int N;
  vector<T> A;
  BIT() {}
  BIT(int N) { init(N); }
  void init(int N) {
    this->N=N;
    A=vector<T>(N+1,0);
  }
  // query ∑ { sum[i] : i=l..<r }
  T query(int l, int r) {
    assert(l<=r&&0<=l&&r<=N);
    return query(r)-query(l);
  }
  // min index s.t. dat[0..i]>x
  int upperbound(T x) {
    int good=N+1,bad=0;
    while(abs(good-bad)>1) {
      int m=(good+bad)/2;
      (query(m)>x?good:bad)=m;
    }
    return good-1;
  }
  // sum[i]+=x
  void add(int i, T x) {
    assert(0<=i&&i<N);
    ++i;
    while(i<=N) A[i]+=x,i+=lsone(i);
  }
  // sum[i]=x
  void update(int i, T v) {
    T pre=query(i+1)-query(i);
    add(i,v-pre);
  }
private:
  int lsone(int i) { return i&-i; }
  // query in [0,r) : ∑ { sum[i] : i=0..r-1 }
  T query(int r) {
    assert(0<=r&&r<=N);
    T res=0;
    while(r>0) res+=A[r],r-=lsone(r);
    return res;
  }
};

// compute inversions
vector<int> inversions(vector<int> ns) {
  int maxv=*max_element(ns.begin(),ns.end());
  BIT<int> bit(maxv+1);
  int N=ns.size();
  vector<int> res(N);
  for(int i=N-1; i>=0; --i) {
    // Count elements which stays in right side and smaller
    res[i]=bit.query(0,ns[i]);
    bit.add(ns[i],1);
  }
  return res;
}

void test_bit() {
  vector<int> ns={2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  
  // Range sum query
  {
    int N=ns.size();
    BIT<int> f(N);
    for(int i=0; i<N; ++i) f.add(i,ns[i]);
    assert(f.query(0,3)==4); // ∑{ns[0..2]}
    assert(f.query(0,4)==7); // ∑{ns[0..3]}
    
    assert(f.upperbound(0)==0);
    assert(f.upperbound(2)==1);
    assert(f.upperbound(51)==12);
    assert(f.upperbound(50)==11);

    f.add(3,6);
    assert(f.query(2,3)==1);
    assert(f.query(0,4)==13);
  }
  
  // Inversion
  {
    vector<int> exp={2,0,0,1,0,0,0,0,0,0,0,0};
    assert(inversions(ns)==exp);
  }
}

/*
 
 Two dimension cumulative sum, O(R*C) time to build, O(1) time to query
 
  - Build cumulative sum 2d array from `X`
  - It queries sum in rectangle r in [i1,i2), c in [j1,j2) in O(1) time
 
 Usage:
  TwoDimCumSum cum(X);
  cout << X.query(0,1,2,3) << endl; // Query sum in (0,1)-(1,2) rectangle
 
 Used problems:
  - https://github.com/k-ori/leetcode/blob/master/304-Range-Sum-Query-2D/RangeSumQuery2D.cpp
  - https://github.com/k-ori/topcoder/blob/master/DropCoins/DropCoins.cpp#L157
 
 */
struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum(vector<vector<int>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<int>>(R+1,vector<int>(C+1,0));
    
    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  int query(int i1, int j1, int i2, int j2) {
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<int>> cum;
};

int main(int argc, char const *argv[]) {
  test_segmenttree();
  test_rmq();
  test_bit();
  
  // 2D cumulative sum query
  vector<vector<int>> mx={
    {3, 0, 1, 4, 2},
    {5, 6, 3, 2, 1},
    {1, 2, 0, 1, 5},
    {4, 1, 0, 1, 7},
    {1, 0, 3, 0, 5}
  };
  TwoDimCumSum cum(mx);
  assert(cum.query(2,1,5,4)==8);
  assert(cum.query(1,1,3,3)==11);
  assert(cum.query(1,2,3,5)==12);
  assert(cum.query(1,2,1,2)==0);
  assert(cum.query(1,2,0,1)==0);
}

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address range-query.cpp && ./a.out
