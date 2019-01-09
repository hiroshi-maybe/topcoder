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
 
 4/14/2018 SRM733
 
 9:15-10:15 give up
 
 4/18/2018
 
 18:50-19:20, 22:00-24:30 Read editorials and understand Cayley's formula
 
 4/19/2018
 
 8:30-11:30, 14:30-15:24 add solution
 
 Editorials:
  - https://www.topcoder.com/blog/srm-733-results/
  - https://togetter.com/li/1218180
  - https://www.topcoder.com/blog/single-round-match-733-editorials/
   - Generalized Cayley's formula
   - http://codeforces.com/blog/entry/4005?locale=en (Russian)
  - https://kimiyuki.net/blog/2018/04/15/srm-733-medium/
   - Kirchhoff's matrix tree theorem
  - http://kmjp.hatenablog.jp/entry/2018/04/15/1000
   - Generalized Cayley's formula
  - https://twitter.com/n_vip/status/985214121103654912
   - leveraging proof by double counting or Prüfer sequences?
  - https://twitter.com/osrehun/status/985232011311771648
   - leveraging proof by Prüfer sequences
  - https://twitter.com/satanic0258/status/985236672412446720
   - leveraging proof by Prüfer sequences
  - https://twitter.com/kinaba/status/985210371039358976
   - Kirchhoff's matrix tree theorem
 
 Keywords: Cayley's formula, matrix-tree theorem and tree distance
 
 # Cayley's formula
 For every positive integer `n`, the number of trees on `n` labeled vertices is
 n^(n-2), which equivalently counts the number of spanning trees of a complete graph with labeled vertices (sequence A000272 in the OEIS)
 
 ## Proof 1: Kirchhoff's matrix tree theorem

 Articles:
  - http://www.i.kyushu-u.ac.jp/~eiji/GraphCombinatorics/graph-combinatorics5.pdf
   - section 2
  - http://joisino.hatenablog.com/entry/2017/08/20/200000
   - proof 4 in this article
  - https://en.wikipedia.org/wiki/Kirchhoff%27s_theorem#Cayley's_formula
 
 The number of spanning trees is equal to any cofactor of the Laplacian matrix of G.
 This shows generalized Cayley's formula.
 Theorem is applicable to this problem directly.
 However it takes O(N^3) for Gaussian elimination to compute determinant of a minor.
 
 ## Proof 2: Double counting
 
 Articles:
  - http://www.i.kyushu-u.ac.jp/~eiji/GraphCombinatorics/graph-combinatorics5.pdf
   - section 1
  - https://en.wikipedia.org/wiki/Double_counting_(proof_technique)#Counting_trees
  - http://joisino.hatenablog.com/entry/2017/08/20/200000
   - proof 3 in this article
 
  // count 1
  U(n) = n * (n-1)! * T(n)
       = n! * T(n)
 
  - Labeling root of the tree and edges on top of existing T(n) trees
 
  // count 2
  U(n) = ∏ { n*k : k=n-1..1 }
       = n^(n-2)*n!
 
  - `n` options for start of edges
  - `k` options to select end of edges which satisfies below conditions
   - it's not the start of the edge
   - it should be root of forests which decreases by one in each edge selection
 
 From count 1 and count 2...
 
     n! * T(n) = n^(n-2)*n!
 <=> T(n) = n^(n-2)
 
 ## Proof 3: Prüfer sequences (expected solution)
 
 Articles:
  - https://en.wikipedia.org/wiki/Pr%C3%BCfer_sequence
  - http://joisino.hatenablog.com/entry/2017/08/20/200000
   - Proof 1 in this article
 
 Prüfer sequences yield a bijective proof of Cayley's formula
 
 There exists bijective function which maps Prüfer sequence to spanning tree of labeled vertices.
 Prüfer sequence is composed of n-2 elements of arbitrary vertex labels of 1...n.
 Thus Cayley's formula is obtained from number of possible Prüfer sequence which is n^(n-2).
 
  T(n) = n^(n-2)
 
 In our case we can associate connected component with single node in Prüfer sequences.
 See https://math.stackexchange.com/questions/2550064/proof-of-generalized-cayleys-formula
 There exists n^(K-2) sequences where K = number of connected components.

  res = n^(K-2)*∏ { S[i] : i=0..K-1 }
 
 # References:
  - https://en.wikipedia.org/wiki/Cayley%27s_formula
  - http://www.i.kyushu-u.ac.jp/~eiji/GraphCombinatorics/graph-combinatorics5.pdf
   - Proof of Cayley’s formula (double counting), Matrix-Tree Theorem
  - http://hamayanhamayan.hatenablog.jp/entry/2017/05/07/183930
   - Summary of special counting problems in undirected graph
  - https://mathtrain.jp/graphmatrix
  - http://joisino.hatenablog.com/entry/2017/08/20/200000
   - 6 proofs of Cayley's formula
 
 Summary:
  - I had no idea about those theorems
  - Problem is simple. Should I have googled some of keywords? 🤔
 
 */
const LL MOD=987654323;
class BuildingSpanningTreesDiv1 {
  public:
  int uf[1001];
  int find(int x) { return x==uf[x]?x:(uf[x]=find(uf[x])); }
  void unite(int a, int b) {
    int pa=find(a),pb=find(b);
    if(pa!=pb) uf[pa]=pb;
  }
  bool same(int a, int b) { return find(a)==find(b); }
  int getNumberOfSpanningTrees(int N, vector<int> X, vector<int> Y) {
    REP(i,N) uf[i]=i;
    REP(i,SZ(X)) {
      int u=X[i]-1,v=Y[i]-1;
      if(same(u,v)) return 0;
      unite(u,v);
    }
    MAPII M;
    REP(i,N) M[find(i)]++;
    VI P;
    FORR(kvp,M) P.push_back(kvp.second);
    int K=SZ(P);
    
    // alreay spanning tree
    if(K==1) return 1;
    
    LL res=1;
    REP(_,K-2) res*=N,res%=MOD;
    FORR(p,P) res*=p,res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("BuildingSpanningTreesDiv1.sample");

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

bool do_test(int n, vector<int> x, vector<int> y, int __expected) {
    time_t startClock = clock();
    BuildingSpanningTreesDiv1 *instance = new BuildingSpanningTreesDiv1();
    int __result = instance->getNumberOfSpanningTrees(n, x, y);
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
        int n;
        from_stream(n);
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1523722515;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BuildingSpanningTreesDiv1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
