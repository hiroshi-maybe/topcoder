#include <bits/stdc++.h>

using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
/*

 General segment tree, O(N) time to build, O(lg N) time to query or update

  - Range query, point update
  - Segment tree is applicable as long as result to be queried is associative
   - Range sum query
   - Range GCD query
  - Update `int operate(a,b)` method to reuse for diffirent query
  - Needs 2*N_-1 space, where N_ = min { 2^n : N<=2^n }
   - N_ leaves (i=N_-1..2*N_-2) + N_-1 parents (i=0..N_-2)
   - Data is populated in 0-indexed

  References:
   - Ant book 3-3 data structures
   - https://www.slideshare.net/hcpc_hokudai/rmq-47663507
   - https://www.slideshare.net/iwiwi/ss-3578491?next_slideshow=1
   - https://en.wikipedia.org/wiki/Segment_tree
   - https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/
   - https://cp-algorithms.com/data_structures/segment_tree.html
   - https://github.com/hiroshi-maybe/atcoder/blob/master/solutions/Sugoroku.cpp#L44

  Usage:

   SegmentTree<int> T(N,1e9,[](int a, int b) { return min(a,b); });
   T.build(A);
   cout<<T.query(3,8)<<endl;

  Used problems:
   - https://github.com/hiroshi-maybe/leetcode/blob/master/307-Range-Sum-Query/RangeSumQuery.cpp#L186 (RSQ)
   - https://github.com/k-ori/csacademy/blob/master/solutions/R78-StrangeMatrix.cpp#L88
   - https://github.com/k-ori/codeforces/blob/master/solutions/ArrayRestoration.cpp#L164 (RMQ)
   - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/Company.cpp#L90 (RMQ)
   - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/VasyaAndMaximumProfit.cpp#L78 (Max subsegment sum query)
   - https://github.com/hiroshi-maybe/GCJ/blob/master/kickstart/2019-RB/DiverseSubarray.cpp#L70 (Max subsegment sum query)
   - https://github.com/hiroshi-maybe/atcoder/blob/3855995ce83d1f60060f9ff472b75668cb16913e/solutions/RangeXorQuery.cpp#L44 (XOR range query)


 */
template <typename Val>
struct SegmentTree {
  int N_; // adjusted N
  vector<Val> tree;
  Val id;
  using Merge = function<Val(Val,Val)>;
  Merge merge;
public:
  SegmentTree(int N, Val id, Merge merge) { prep(N,id,merge); }
  SegmentTree(vector<Val> A, Val id, Merge merge) { prep(A.size(),id,merge), this->build(A); }
  SegmentTree& prep(int N, Val id, Merge merge) {
    this->id=id,this->merge=merge;
    int n=1; while(n<N) n<<=1; // Init by power of 2
    this->tree=vector<Val>(2*n-1,id), this->N_=n;
    return *this;
  }
  void build(const vector<Val> &ns) {
    for(int i=0; i<ns.size(); ++i) tree[i+N_-1]=ns[i];
    for(int i=N_-2; i>=0; --i) mergeAt(i);
  } // Initialize tree with `ns`
  void update(int i, const Val &x) { i+=N_-1,tree[i]=x; while(i>0) i=(i-1)/2,tree[i]=mergeAt(i); } // Update k-th (0-indexed) value
  Val query(int ql, int qr) { return queryTree(ql,qr,0,0,N_); } // query in range [ql,qr)
private:
  Val mergeAt(int i) { return tree[i]=merge(tree[2*i+1],tree[2*i+2]); }
  Val queryTree(const int ql, const int qr, int i, int tl, int tr) {
    if (tr<=ql||qr<=tl) return id; // out of range
    if (ql<=tl&&tr<=qr) return tree[i]; // all covered
    int mid=tl+(tr-tl)/2; // partially covered
    return merge(queryTree(ql,qr,2*i+1, tl,mid),
                 queryTree(ql,qr,2*i+2,mid, tr));
  }
};

/*

 RMQ (segment tree), O(lg N) query, O(lg N) update

 - normal: range query, point update
 - lazy propagation: point query, range update

 References:
  - https://www.npca.jp/works/magazine/2015_5/

 Usage:
   auto rmq=makeRmQ(A,(int)1e9);
   assert(rmq.query(2,8)==1);

 Used problem:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/Company.cpp#L174
  - https://github.com/hiroshi-maybe/atcoder/blob/e81dcc4cd4d181d4a38e70ee4cdfb0c3692cfd2f/solutions/Roadwork.cpp#L72
   - lazy propagation (range update)
  - https://github.com/hiroshi-maybe/leetcode/blob/master/1124-longest-well-performing-interval/longest-well-performing-interval.cpp#L50
   - range min query
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/YetAnotherMonsterKillingProblem.cpp#L44
   - range min query
  - https://github.com/hiroshi-maybe/atcoder/blob/2b8c0e08422d98f6c08a13f32969d75e002eb299/solutions/OperationTakahashiDating.cpp#L76
   - range min query
  - https://github.com/hiroshi-maybe/atcoder/blob/ffc44349faf3f9e8e377089cc5ff11d0e7b10139/solutions/FlatSubsequence.cpp#L44
   - range max query for dp

 */
template<typename Val> auto makeRmMQ(vector<pair<Val,Val>> A, pair<Val,Val> id) {
  using P=pair<Val,Val>;
  return SegmentTree<P>(A,id,[](P a, P b) {
    return P(min(a.first,b.first), max(a.second,b.second));
  });
}
template<typename Val> auto makeRmQ(vector<Val> A, Val id) {
  return SegmentTree<Val>(A,id,[](Val a, Val b) { return min(a,b); });
}
template<typename Val> auto makeRMQ(vector<Val> A, Val id) {
  return SegmentTree<Val>(A,id,[](Val a, Val b) { return max(a,b); });
}

/*
 General lazy segment tree, O(N) time to build, O(lg N) time to query or update

  - Range query, *range* update

 Reference:
  - https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-9
  - https://atcoder.github.io/ac-library/master/document_ja/lazysegtree.html

 Used problems:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/Editor.cpp#L44
   - lazy RmMQ
  - https://github.com/hiroshi-maybe/atcoder/blob/a669b3419df50aaf5388da15b3ff5ae0d87abd24/solutions/Roadwork.cpp#L75
   - lazy RmQ
  - https://github.com/hiroshi-maybe/atcoder/blob/40d27e83c735be93ac9d0537224052383cf2dc7a/solutions/ReplaceDigits.cpp#L45
   - Range update query for decimal string in AtCoder Library Contest

 */
template <typename Val, // x∈S (Monoid) for f(x)
  Val (*id)(),  // Identity element for S
  Val (*merge)(Val, Val), // Merge x and y
  typename Delay, // Parameters for f_i∈F
  Delay (*delayId)(), // Identity element for F
  Val (*apply)(Val, Delay), // f_i(x)
  /* mergeDelay(g, f), f(g(x)) */
  Delay (*mergeDelay)(Delay, Delay)> // f_i∘f_j∈F
struct LazySegmentTree {
  int N_/* adjusted N*/,head/* head of leaf */;
  vector<Val> tree;
  vector<Delay> delay;
public:
  LazySegmentTree(int N) { prep(N); }
  LazySegmentTree(vector<Val> A) { prep(A.size()),this->build(A); }
  LazySegmentTree& prep(int N) {
    int n=1; while(n<N) n<<=1; // Init by power of 2
    this->tree=vector<Val>(2*n-1,id()),this->delay=vector<Delay>(2*n-1,delayId());
    this->N_=n,this->head=N_-1;
    return *this;
  }
  void build(const vector<Val> &ns) {
    for(int i=0; i<ns.size(); ++i) tree[i+N_-1]=ns[i];
    for(int i=N_-2; i>=0; --i) mergeAt(i);
  } // Initialize tree with `ns`
  void update(int ql, int qr, const Delay &delay) { updateTree(ql,qr,delay,0,0,N_); }
  Val query(int ql, int qr) { return queryTree(ql,qr,0,0,N_); } // query in range [ql,qr)
private:
  Val mergeAt(int i) { return tree[i]=merge(tree[2*i+1],tree[2*i+2]); }
  Val queryTree(const int ql, const int qr, int i, int tl, int tr) {
    if(tr<=ql||qr<=tl) return id(); // out of range
    applyDelay(i);
    if(ql<=tl&&tr<=qr) return tree[i]; // all covered
    int mid=tl+(tr-tl)/2; // partially covered
    return merge(queryTree(ql,qr,2*i+1, tl,mid),
                 queryTree(ql,qr,2*i+2,mid, tr));
  }
  void updateTree(const int ql, const int qr, Delay d, int i, int tl, int tr) {
    if(ql<=tl&&tr<=qr) mergeDelayAt(i,d),applyDelay(i); // all covered
    else if(ql<tr&&tl<qr) { // partially coverd
      int mid=tl+(tr-tl)/2;
      applyDelay(i),updateTree(ql,qr,d,2*i+1,tl,mid),updateTree(ql,qr,d,2*i+2,mid,tr),mergeAt(i);
    } else applyDelay(i);
  }
  void applyDelay(int i) {
    if(i<head) pushdownAt(i);
    tree[i]=apply(tree[i],delay[i]),delay[i]=delayId();
  }
  void pushdownAt(int i) { mergeDelayAt(2*i+1,delay[i]),mergeDelayAt(2*i+2,delay[i]); }
  void mergeDelayAt(int i, Delay d) { delay[i]=mergeDelay(delay[i],d); }
};

int id() { return (int)1e9; };
int lazyId() { return (int)1e9; };
int mina(int a, int b) { return min(a,b); };
int seta(int a, int b) { return b==lazyId()?a:b; };

void test_segmenttree() {
  vector<int> ns={2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};

  {
    // Range minimum query
    SegmentTree<int> T(ns,1e9,[](int a, int b) { return min(a,b); });

    assert(T.query(2,8)==1);
    assert(T.query(3,8)==2);
    T.update(5,-1);
    assert(T.query(2,8)==-1);
  }

  {
    // Range minimum query, range update
    LazySegmentTree<int,id,mina,int,lazyId, seta, seta> T(ns);

    assert(T.query(2,8)==1);
    assert(T.query(3,8)==2);
    T.update(3,6,0);
    assert(T.query(0,3)==1);
    assert(T.query(0,4)==0);
    assert(T.query(5,7)==0);
    T.update(0,4,-1);
    assert(T.query(0,3)==-1);
    assert(T.query(4,10)==0);
  }

  {
    int N=100;
    vector<int> A(N);
    iota(A.begin(),A.end(),1);
    SegmentTree<int> T1(A,1e9,[](int a, int b) { return min(a,b); });
    LazySegmentTree<int,id,mina,int,lazyId,seta,seta> T2(A);
    int T=100;
    while(T--) {
      int l=genRandNum(0,N-1),r=genRandNum(l,N+1),val=genRandNum(0,100);
      for(int i=l; i<r; ++i) A[i]=val,T1.update(i,val);
      T2.update(l,r,val);
      int ql=genRandNum(0,N-1),qr=genRandNum(ql,N+1);
      int res=1e9;
      for(int i=ql; i<qr; ++i) res=min(res,A[i]);

      int act1=T1.query(ql,qr),act2=T2.query(ql,qr);
      assert(res==act1);
      assert(res==act2);
    }
  }
}

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
  auto rmq=makeRmQ(ns,(int)1e9);
  assert(rmq.query(2,8)==1);
  assert(rmq.query(3,8)==2);
  rmq.update(5,-1);
  assert(rmq.query(2,8)==-1);

  vector<pair<int,int>> ps;
  for(int i=0; i<ns.size(); ++i) ps.emplace_back(ns[i],i);
  auto rmq2=makeRmQ(ps,{1e9,-1});
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
  - https://github.com/hiroshi-maybe/codeforces/blob/82bef974ead7bd9d1e27a4e58b5b3066a0450335/solutions/OptimalSubsequences.cpp#L44
  - https://github.com/hiroshi-maybe/topcoder/blob/470b5d80a15f3d97f4a2405b6ef274d6f320ffaa/solutions/SwapTheString/SwapTheString.cpp#L42
   - inversion number
  - https://github.com/hiroshi-maybe/leetcode/blob/master/1505-minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits.cpp#L34
  - https://github.com/hiroshi-maybe/atcoder/blob/d1ebaf97523ed0e7e3bad3c645e4294c5e2e900a/solutions/Difficulty.cpp#L80
   - range sum query with ModInt
  - https://github.com/hiroshi-maybe/atcoder/blob/c8601b666f1a2f62c2456e9077c7cae42ec4885f/solutions/DataStructure.cpp#L44
   - range sum query and binary search

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
  - https://github.com/hiroshi-maybe/codeforces/blob/924a2f0afa608ef58ea26dd14c2e38eb4e282d50/solutions/ArsonInBerlandForest.cpp#L44

 */
template <typename Val>
struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum(vector<vector<Val>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<Val>>(R+1,vector<Val>(C+1,0));

    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  Val query(int i1, int j1, int i2, int j2) {
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<Val>> cum;
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
  TwoDimCumSum<int> cum(mx);
  assert(cum.query(2,1,5,4)==8);
  assert(cum.query(1,1,3,3)==11);
  assert(cum.query(1,2,3,5)==12);
  assert(cum.query(1,2,1,2)==0);
  assert(cum.query(1,2,0,1)==0);
}

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address range-query.cpp && ./a.out
