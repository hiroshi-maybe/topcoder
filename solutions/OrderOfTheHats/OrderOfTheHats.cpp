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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/14/2018
 
 16:54-17:47 give up
 
 1/15/2018
 
 20:00-20:37 read editorials
 20:38-20:50 add solution
 
 Minimum feedback arc set is NP-complete. No polynomial algorithm is not found.
 However V is small (V<=20). We can remember 2^V states.
 
 Suppose we have vertice set `S` with no cycle. Also we are adding a vertex `v` to S.
 If there exists a cycle in S' = S ∪ {v}, there should exist at least one edge from v to `u` ∈ S.
 If we remove all those edges, S' has acyclic as well.
 We can keep solving next subproblem P(S'). This forms optimal substructure.
 
 Feedback arc set:
  - https://en.wikipedia.org/wiki/Feedback_arc_set#Minimum_feedback_arc_set
  - https://mathoverflow.net/questions/233985/removing-cycles-in-a-directed-graph-by-swapping-edges-orientation
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+549
  - http://kmjp.hatenablog.jp/entry/2013/12/28/1100
  - http://kenkoooo.hatenablog.com/entry/2016/04/20/021527
  - http://area.hateblo.jp/entry/2013/11/26/043901
 
 Key:
  - Keep adding vertex. Use bit DP to remember what vertices are chosen
  - DAG ∪ {v} forms DAG if edges v↝u s.t. u ∈ DAG are removed
 
 Summary:
  - I figured out that this is a problem called as "Minimum feedback arc set" of unweighted directed graph
  - Minimum feedback arc set is NP-complete
  - V is small (<=20). I thought to remember state 2^V though, I coudn't move forward any more.
  - We need to keep adding vertices one by one. Pay attention how we can build subproblem.
 
 */

// O(V*2^V) time
int memo[1<<20];
class OrderOfTheHats {
public:
  int V;
  vector<int> G;
  int f(int mask) {
    int &res = memo[mask];
    if(res>=0) return res;
    if(mask==(1<<V)-1) return 0;
    
    res=V*V;
    REP(v,V) if((mask&(1<<v))==0) {
      int mask2=mask|(1<<v);
      int cnt=__builtin_popcount(mask2&G[v]);
      res=min(res,cnt+f(mask2));
    }
    return res;
  }
  
  int minChanged(vector<string> GG) {
    this->V=SZ(GG);
    G.resize(V,0);
    REP(u,V) REP(v,V) if(GG[u][v]=='Y') G[u]|=(1<<v);
    MINUS(memo);
    return f(0);
  }
};

// O(V^2*2^V) time
class OrderOfTheHats_org {
  public:
  int V;
  vector<string> G;
  int f(int mask) {
    int &res = memo[mask];
    if(res>=0) return res;
    if(mask==(1<<V)-1) return 0;
    
    res=V*V;
    REP(v,V) if((mask&(1<<v))==0) {
      int cnt=G[v][v]=='Y';
      REP(u,V) if(mask&(1<<u)) {
        cnt+=G[v][u]=='Y';
      }
      res=min(res,cnt+f(mask|(1<<v)));
      
    }
    return res;
  }
  
  int minChanged(vector<string> G_) {
    this->G=G_;
    this->V=SZ(G);
    MINUS(memo);
    return f(0);
  }
};

// CUT begin
ifstream data("OrderOfTheHats.sample");

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

bool do_test(vector<string> spellChart, int __expected) {
    time_t startClock = clock();
    OrderOfTheHats *instance = new OrderOfTheHats();
    int __result = instance->minChanged(spellChart);
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
        vector<string> spellChart;
        from_stream(spellChart);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(spellChart, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515977643;
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
        cout << "OrderOfTheHats (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
