#include <fstream> // for greed plugin
#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/20/2018
 
 18:15-18:47 Analysis
 18:48-19:08 Implement and submit. However 1WA
 19:09-19:56 Investigate analysis mistake... However no luck
 
 21:45-23:35 read editorial, follow input data and understand the root cause
 23:35-26:00 added analysis description and solution
 
 Editorials:
  - http://hamayanhamayan.hatenablog.jp/entry/2018/02/21/110908
  - https://togetter.com/li/1201519
 
 I thought that I could solve just by looking at neighbored 2 levels in subtree.
 However that's a stupid idea. This wrong analysis cannot catch up below case:
 
     a
  *b   c
       d
       e
      *f
    *g  *h
 
 If we want to put a stone at `c`, we need to put at `d` as well. Weight at each state is maximum among below:
 {W[b]+W[c]+W[d], W[b]+W[d]+W[e], W[b]+W[e]+W[f], W[b]+W[f]+W[g]+W[h]}
 Thus `b` along with weights in deep level in the tree forms maximum cost.
 Yes focusing on the last state and go backward in state transition is good start.
 However, analyze connection with subproblem. If we can ignore deep level, there MUST be some proof.
 Follow necessary and sufficient conditions carefully. Don't skip intermediate logic.
 
 ***
 
 From here, I describe analysis of correct approach.
 Look at below tree. We want to put stones at `b` and `c` to put a stone at `a`.
 
    a
  b   c
 d e f g
 
 There are two cases:
  - put a stone at left child first
  - put a stone at right child first
 
 i) Left first case
 
 1. put stones at `d` and `e`
 2. put stone at `b` and remove from `d` and `e`
 3. put stone at `f` and remove stones under `f`
 4. put stone at `g` (and we want to put at `c` after all)
 
       a
   *b      c
  d  e  *f  *g
 
 Wait. Why can we put a stone at `g`?
 If we want to put a stone at `g`, children of `g` must have stones as well.
 Due to the recursive structure, children of `g` and grand children of `g` must have stones before hand.
 
 Now we can define step 3' which leverages substructure in subtree rooted by `c`.
 
 3' solve maximum cost in c's subtree keeping weight of node `b`
 
      a
  *b      *c
 d   e  *f  *g
 
 4' Remove stones at `f` and `g`. Now we can put a stone at `a`.

      *a
  *b      *c
 d   e   f   g

 We can define recurrence relation from this observation.
 
   f1(a)
 = max(
    f(b),          // step 2
    W[b]+f(c),     // step 3'
    W[a]+W[b]+W[c] // step 4'
  )
 
 Note that f1(x) shows left first case. f(x) considers both left first and right first cases.
 
 ii) Right first case
 
 f2(a) for right first case has symmetric property. We can just swap `b` and `c` from f1(a) analysis.
 f(a) = min(f1(a),f2(a))
 
 iii) Single child case
 
 Single child case is simpler. f(a) = max(f(b), W[a]+W[b])
 
 ***
 
 Why weight needs to be monotonically decreasing?
  - https://twitter.com/_olphe/status/965946962263515136
  - https://twitter.com/shisashi/status/966346931181043713

 Suppose we want to solve the problem for subtree rooted by `a`.
 There are two subtrees T1 and T2.
 
      a
     / \
   T1   T2
 
 If weight is not monotonically decreasing towards root,
 we cannot leverage optimality by putting a stone at root of either tree first.
 We may want to put a stone in the middle of T1 and "lift up" stone in T2.
 
 Summary:
  - I'm stupid. Don't skip intermediate states before making a conclusion 👎
   - In this specific problem, what state is necessary to fill children 👎👎
   - Samples didn't have a case with remote chilren affect the result 👎👎👎👎
   - My poor analysis was completely in the pit fall 👎👎👎👎👎👎👎👎
   - Follow necessary and sufficient conditions carefully. Don't skip intermediate logic. 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
  - Focusing on recursive relation was nice start. However analysis in deeper level is too loose 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 
 */

vector<int> E[1001];
int memo[1001];
class StonesOnATree {
public:
  const int Inf=1e8+100;
  VI W;
  int minStones(vector<int> P, vector<int> W) {
    this->W=W;
    REP(i,1001) E[i].clear();
    REP(i,SZ(P)) E[P[i]].push_back(i+1);
    MINUS(memo);
    return f(0);
  }
  
  int f(int a) {
    int &res=memo[a];
    if(res>=0) return res;
    res=W[a];
    
    if(SZ(E[a])==1) {
      int b=E[a][0];
      res=max(f(b), W[a]+W[b]);
    }
    if(SZ(E[a])==2) {
      int b=E[a][0],c=E[a][1];
      int f1=max({f(b), W[b]+f(c), W[a]+W[b]+W[c]});
      int f2=max({f(c), W[c]+f(b), W[a]+W[b]+W[c]});
      res=min(f1,f2);
    }
    
    return res;
  }
};

class StonesOnATree_wrong {
  public:
  const int Inf=1e8+100;
  VI W;
  int minStones(vector<int> P, vector<int> W) {
    this->W=W;
    REP(i,1001) E[i].clear();
    REP(i,SZ(P)) E[P[i]].push_back(i+1);
    MINUS(memo);
    return f(0);
  }
  
  int ff(int u) {
    int &res=memo[u];
    if(res>=0) return res;
    res=0;
    int sum=0;
    VI X;
    REP(i,SZ(E[u])) {
      int v=E[u][i];
      dump2(u,v);

      sum+=W[v];
      res=max(res,ff(v));
    }
    if(SZ(E[u])==2) {
      int a=E[u][1],b=E[u][0];
      int c=Inf;
      SMIN(c,max(f(a),f(b)+W[a]));
      SMIN(c,max(f(b),f(a)+W[b]));
      dump4(f(a),f(b),W[a],f(b)+W[a]);
      dump4(f(b),f(a),W[b],f(a)+W[b]);
      dump3(u,a,b);
      assert(c<353617);
      res=max({res,c});
    } else if(SZ(E[u])==1) {
      int a=E[u][0];
      res=max({res,ff(a)});
    }
    res=max(res,sum+W[u]);
    assert(res<353617);
    
    dump2(u,res);
    
    return res;
  }
  
  int f(int u) {
    int &res=memo[u];
    if(res>=0) return res;
    res=0;
    int sum=0;
    VI X;
    REP(i,SZ(E[u])) {
      int v=E[u][i];
      sum+=W[v];
      res=max(res,f(v));
    }
    assert(SZ(E[u])<=2);
    if(SZ(E[u])==2) {
      int rsum=0;
      FORR(x,E[E[u][1]]) rsum+=W[x];
      int lsum=0;
      FORR(x,E[E[u][0]]) lsum+=W[x];

      int a=sum+rsum,b=sum+lsum;
      dump3(u,a,b);
      assert(a<353617&&b<353617);
      res=max(res,min(a,b));
    }
    res=max(res,sum+W[u]);
    assert(res<353617);
    
    dump2(u,res);
    
    return res;
  }
};

// CUT begin
ifstream data("StonesOnATree.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<int> p, vector<int> w, int __expected) {
    time_t startClock = clock();
    StonesOnATree *instance = new StonesOnATree();
    int __result = instance->minStones(p, w);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> p;
        from_stream(p);
        vector<int> w;
        from_stream(w);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(p, w, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519179324;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "StonesOnATree (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
