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
 
 9/2/2017
 
 9:38-10:09 system test passed (278.99 pt)
 
 brute-force by permutation and validation by in-degree 0
  - precompute parents and in-degree of each node by dfs
  - visit nodes following order of permutation
   - if in-degree of the node is not 0, the order is NG
   - reduce in-degree of parent of visited node by one
 
 editorials:
  - http://roiti46.hatenablog.com/entry/2015/04/30/TopCoder_SRM_654_Div2_Med%3A_OneEntrance
  - http://kmjp.hatenablog.jp/entry/2015/03/28/0900
   - bruteforce by permutation and validation by floyd-warshall
   - visiting node y. if ∃x s.t. (x is visited before y) AND d(s,y) == d(s,x) + d(x,y), node x is in path. NG.
  - https://apps.topcoder.com/wiki/display/tc/SRM+654
 
 15:40-15:58 add solution by floyd-warshall
 
 summary:
  - original solution using in-degree was a bit complex though, implemented withotu issues 👍
  - technique in @kmjp's solution to test if vertex u is on path v↝s is neat 👍
 
 other solutions:
  - permutation
    - https://community.topcoder.com/stat?c=problem_solution&rm=325660&rd=16318&pm=13698&cr=23179170
    - https://community.topcoder.com/stat?c=problem_solution&rm=325662&rd=16318&pm=13698&cr=23189191
  - binomial coefficient
    - https://community.topcoder.com/stat?c=problem_solution&rm=325659&rd=16318&pm=13698&cr=23068712
  - trace path to root
    - https://community.topcoder.com/stat?c=problem_solution&rm=325663&rd=16318&pm=13698&cr=40020493

 */
VI E[10];
int P[10];
class OneEntrance_indegree {
  public:
  VI IND;
  void dfs(int u, int pre) {
    FORR(v,E[u]) if(v!=pre) {
      ++IND[u];
      P[v]=u;
      dfs(v,u);
    }
  }
  int count(vector<int> A, vector<int> B, int s) {
    int V=SZ(A)+1;
    MINUS(P);
    REP(v,V) E[v].clear();
    REP(i,SZ(A)) E[A[i]].push_back(B[i]),E[B[i]].push_back(A[i]);
    IND = VI(V,0);
    dfs(s,-1);
    
    int res=0;
    VI vs; REP(i,V) vs.push_back(i);
    do {
      VI ind = IND;
      bool ok=true;
      FORR(i,vs) {
        if(ind[i]>0) { ok=false; break; }
        if(P[i]>=0) --ind[P[i]];
      }
      if(ok) ++res;
    } while(next_permutation(vs.begin(),vs.end()));
    
    return res;
  }
};

const int Inf = 100;
int mx[10][10];
class OneEntrance {
public:
  int count(vector<int> A, vector<int> B, int s) {
    int V=SZ(A)+1;
    int res=0;
    
    REP(i,V)REP(j,V) mx[i][j]=mx[j][i]=(i==j?0:Inf);
    REP(i,SZ(A)) mx[A[i]][B[i]]=mx[B[i]][A[i]]=1;
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]=min(mx[i][j],mx[i][k]+mx[k][j]);
    
    VI vs; REP(i,V) vs.push_back(i);
    do {
      bool ok=true;
      REP(i,V) REP(j,i) {
        int u=vs[i],v=vs[j];
        if(mx[u][s]==mx[u][v]+mx[v][s]) ok=false;
      }
      res+=ok;
    } while(next_permutation(vs.begin(),vs.end()));
    
    return res;
  }
};

// CUT begin
ifstream data("OneEntrance.sample");

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

bool do_test(vector<int> a, vector<int> b, int s, int __expected) {
    time_t startClock = clock();
    OneEntrance *instance = new OneEntrance();
    int __result = instance->count(a, b, s);
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        int s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504370310;
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
        cout << "OneEntrance (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
