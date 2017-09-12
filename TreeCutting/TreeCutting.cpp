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
 
 9/11/2017
 
 9:24-10:24 time up
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2015/01/14/1000
    - keep dividing into sub-trees
  - http://mayokoex.hatenablog.com/entry/2015/04/02/130727
    - subset of sub-trees is deterministic
    - finding N possible edges to be cut. N should be number of positive number vertices (or conected subtrees) minus 1
 
 18:50-20:40 read editorials and add solution, still system test doesn't pass
 22:55-23:41 system test passed
 
 key:
  - number of vertices in sub graph can be validated by sum of vertice numbers
  - set of subtrees which satisfies problem statement is deterministic
    - if it's a graph (not tree), set of sub graphs is not deterministic due to cycle.
 
 summary:
  - I was trying to solve by iterating each node which has positive number though, in stuck
  - I noticed graph validation by vertice numbers though, I didn't have idea to leverage it and reduce subproblems
  - a lot of bugs
    - implementation bugs
      - overflow by 1<<v instead of 1LL<<v
      - __builtin_popcountll() (not __builtin_popcount())
    - algorithm bug
      - Algorithm should be DIVIDE & CONQUER (NOT DP)
        - no overlapping subproblem
        - once we find a nice cut (sum of positive numbers equal to graph size in subgraph), it should be always the final answer. no need to try other cuts.
        - no memoization needed, no branch pruning needed
  
  24:25-24:32 add a solution inspired by @mayoko's editorial. this is short and beautiful.
 
  I found that test cases in system test is missing below case.
 
  > par={ 0, 0, 1, 1 }
  > num={ -1, -1, 4, -1, -1 }
  > Returns: "IMPOSSIBLE"
 
 */

VI E[51];

class TreeCutting {
public:
  int V;
  VI ns;
  string ok="POSSIBLE",ng="IMPOSSIBLE";
  pair<LL,int> count(int u, int pre) {
    LL mask=1LL<<u;
    int sum=ns[u]==-1?0:ns[u];
    FORR(v, E[u]) if(v!=pre) {
      auto p=count(v,u);
      mask|=p.first,sum+=p.second;
    }
    
    return {mask,sum};
  }
  
  string can(vector<int> P, vector<int> ns) {
    this->V=SZ(ns); this->ns=ns;
    REP(i,V) E[i].clear();
    int T=0;
    REP(i,V) T+=(ns[i]!=-1);
    REP(i,SZ(P)) {
      int u=i+1,v=P[i];
      E[u].push_back(v),E[v].push_back(u);
    }
    
    // handle below case
    // par={ 0, 0, 1, 1 }
    // num={ -1, -1, 4, -1, -1 }
    // Returns: "IMPOSSIBLE"
    if (T==1) {
      auto p=count(0,-1);
      return __builtin_popcountll(p.first)==p.second ? ok : ng;
    }
    
    int x=0;
    REP(i,SZ(P)) {
      int u=i+1,v=P[i];
      auto p1=count(u,v),p2=count(v,u);
      if(__builtin_popcountll(p1.first)!=p1.second) continue;
      if(__builtin_popcountll(p2.first)!=p2.second) continue;
      ++x;
    }
    
    return x==T-1?ok:ng;
  }
};

class TreeCutting_divideAndConquer {
  public:
  int V;
  VI ns;
  string ok="POSSIBLE",ng="IMPOSSIBLE";
  LL pmask=0;
  
  bool f(LL scope) {
    REP(u,V) if((scope&(1LL<<u))) {
      auto p=count(u,-1,scope);
      if(__builtin_popcountll(p.first&pmask)!=1) continue;
      if(__builtin_popcountll(p.first)!=__builtin_popcountll(scope)) continue;
      if(__builtin_popcountll(p.first)!=p.second) continue;
      return true;
    }
    
    REP(u,V) FORR(v,E[u]) if(u<v&&(scope&(1LL<<u))&&(scope&(1LL<<v))) {
      auto p1=count(u,v,scope),p2=count(v,u,scope);
      if(p1.second==0||__builtin_popcountll(p1.first)!=p1.second) continue;
      if(p2.second==0||__builtin_popcountll(p2.first)!=p2.second) continue;
      
      // this is the biggest mistake in algorithm design
      // no need to compute other cases if size of subgraph equals to sum of vertex numbers (DP vs divide & conquer)
      //if(f(p1.first)&&f(p2.first)) { return true; }
      return f(p1.first)&&f(p2.first);
    }

    return false;
  }
  
  pair<LL,int> count(int u, int pre, LL scope) {
    if((scope&(1LL<<u))==0) return {0,0};
    LL mask=1LL<<u;
    int sum=ns[u]==-1?0:ns[u];
    FORR(v, E[u]) if(v!=pre) {
      auto p=count(v,u,scope);
      mask|=p.first,sum+=p.second;
    }
    
    return {mask,sum};
  }
  
  string can(vector<int> P, vector<int> ns) {
    this->V=SZ(ns); this->ns=ns;
    REP(i,V) E[i].clear();
    REP(i,V) if(ns[i]!=-1) pmask|=(1LL<<i);
    REP(i,SZ(P)) {
      int u=i+1,v=P[i];
      E[u].push_back(v),E[v].push_back(u);
    }
    
    return f((1LL<<V)-1LL)?ok:ng;
  }
};

// CUT begin
ifstream data("TreeCutting.sample");

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

bool do_test(vector<int> par, vector<int> num, string __expected) {
    time_t startClock = clock();
    TreeCutting *instance = new TreeCutting();
    string __result = instance->can(par, num);
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
        vector<int> par;
        from_stream(par);
        vector<int> num;
        from_stream(num);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(par, num, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505147078;
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
        cout << "TreeCutting (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
