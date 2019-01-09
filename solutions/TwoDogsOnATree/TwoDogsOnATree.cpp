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
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/*
 
 8/14/2017
 
 SRM719 contest
 
 18:15-19:15 could not solve
 
 9/4/2017
 
 21:30-22:15 give up
 22:15-23:10 read editorial
  - http://kmjp.hatenablog.jp/entry/2017/08/15/1000
  - http://tookunn.hatenablog.com/entry/2017/08/15/161416
 
 x^x=0, XOR operator discards duplicated number.
 Key analysis is that this property discards duplicated path traversal too.
 
 Define f(u,v) = XOR { w[e] : e ∈ u↝v }, g(u) = f(0,u)
 
 Suppose LCA(u,v) = w, then...
 f(u,v) = f(u,w)^f(w,v) = f(u,w)^f(w,v)^0 = f(u,w)^f(w,v)^f(w,0)^f(w,0)
        = f(0,u)^f(0,v) = g(u)^g(v)
 Thus we can compute f(u,v) from g(u) and g(v) in O(1) time.
 
 Suppose a↝b and c↝d have no common edges.
 In such a case, f(a,b)^f(b,c) = g(a)^g(b)^g(c)^g(d) by above analysis.
 
 If a↝b and c↝d have common edges p↝q, we can actually convert this path to (a↝c),(b↝d) or (a↝d),(c↝b).
 In this case f(a,c)^f(b,d)=g(a)^g(c)^g(b)^g(d) because f(p,q)^f(p,q) = 0. It can be ignored.
 
 By above analysis, we can just pick up every four vertices (a,b,c,d) and compute g(a)^g(c)^g(b)^g(d).
 
 res = max { g(a)^g(c)^g(b)^g(d) : a,b,c,d ∈ V }
 a,b,c,d can be duplicated because we can convert even them into valid non-overlap paths.
 
 key:
  - heavily analysis focused problem
  - leverage property of A^A=0
    - it enables us to convert any combination of paths to valid path
    - it enables us to compute value of the result only from g(x) = XOR { e : e ∈ root↝x }
 
 summary:
  - tough to reach this analysis with my current analysis performance
  - xor has some interesting properties though, it's tough to leverage it to solve problems.
 
 submit solutions:
  most of people are using dfs to compute g(u)
  - https://community.topcoder.com/stat?c=problem_solution&rm=330440&rd=16956&pm=14673&cr=40458743
  - https://community.topcoder.com/stat?c=problem_solution&rm=330444&rd=16956&pm=14673&cr=40619236
  - https://community.topcoder.com/stat?c=problem_solution&rm=330437&rd=16956&pm=14673&cr=40234236
  - https://community.topcoder.com/stat?c=problem_solution&rm=330439&rd=16956&pm=14673&cr=23136455
 
 */

vector<II> E[1001];
class TwoDogsOnATree {
public:
  int V;
  SETI A;
  void dfs(int u, int mask) {
    A.emplace(mask);
    FORR(p,E[u]) dfs(p.first,mask^p.second);
  }
  int maximalXorSum(vector<int> parent, vector<int> W) {
    V=SZ(parent)+1;
    REP(i,V) E[i].clear();
    REP(i,SZ(parent)) {
      int v=i+1,u=parent[i];
      E[u].emplace_back(v,W[i]);
    }

    dfs(0,0);
    SETI B;
    FORR(n1,A) FORR(n2,A) {
      B.emplace(n1^n2);
    }
    int res=0;
    FORR(n1,B) FORR(n2,B) {
      res=max(res,n1^n2);
    }
    return res;
  }
};

/*
VI E[1001];
SETI memo[1001][2];
class TwoDogsOnATree {
  public:
  int V;
  void dfs(int u, int pre) {
    FORR(v,E[u]) if(v!=pre) {
      dfs(v,u);
      FORR(n,memo[v][1]) {
        memo[u][0].insert(n^E[u]);
        memo[u][1].insert(n^E[u]);
      }
      FORR(n,memo[v][0]) {
        memo[u][0].insert(n);
      }
    }
    REP(x,V)REP(y,V) if(x!=pre&&y!=pre&&x!=y) {
      FORR(n,memo[x][1]) FORR(m,memo[y][1]) memo[u][0].insert(n^m);
    }
    memo[u][0].insert(0);
    memo[u][1].insert(0);
  }
  int maximalXorSum(vector<int> parent, vector<int> W) {
    V=SZ(parent);
    REP(i,V) E[i].clear();
    REP(i,SZ(parent)) {
      int u=i+1,v=parent[i];
      E[u].push_back(v);
      E[v].push_back(u);
    }
    
    int res=0;
    REP(u,V) {
      ZERO(memo);
      FORR(v,E[u]) {
        dfs(v,u);
        
      }
      
    }
    
    return 0;
  }
};*/

// CUT begin
ifstream data("TwoDogsOnATree.sample");

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

bool do_test(vector<int> parent, vector<int> w, int __expected) {
    time_t startClock = clock();
    TwoDogsOnATree *instance = new TwoDogsOnATree();
    int __result = instance->maximalXorSum(parent, w);
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
        vector<int> parent;
        from_stream(parent);
        vector<int> w;
        from_stream(w);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(parent, w, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502759544;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TwoDogsOnATree (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
