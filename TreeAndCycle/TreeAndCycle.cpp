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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/21/2017
 
 9:42-10:16 time up
 
 21:15-22:05 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/07/04/1000
 
 22:16-23:00 add solution (practice room is not available)
 
 Key
 - we want path => split to fragment of paths!
 - vertex order in path doesn't matter to reconnect!
  - because cost depends on vertex
 - e(i+1,pre[i]) and 0<=pre[i]<i+1, then pre[i] is parent and i+1 is child in tree
 - analyze and clasify to three separated cases
  i)   take no children (parent may or may not be dropped)
  ii)  take two children (parent dropped)
  iii) take one children (parent may or may not be dropped)
 
 Summary
 - this is hard to find out though, key is splitting to paths
 - don't be worried about tree DP. It's usually just a memoized DFS
 
 */

int memo[101][2];

class TreeAndCycle {
  public:
  MAPII E[101]; // [parent][child]->cost (has edge)
  VI costV;
  int V;
  int f(int u, int pre, bool conn) {
    if(memo[u][conn]>=0) return memo[u][conn];
    
    int costp = conn ? 0 : (costV[u] + (pre==-1?0:E[pre][u]));
    
    int res=0;
    
    // i) take no children (parent may or may not be dropped)
    // cost = ∑{f(v[x],0), v[x] is any child}+costV[u]+(0 or costV[u]+costE[parent,u])
    res += costV[u] + costp;
    FORR(kvp,E[u]) {
      int v=kvp.first;
      res += f(v,u,0);
    }
    
    // ii) take two chilren (parent dropped)
    // cost ∈ { f(v[x],1)+f(v[y],1)+costE[u,p]+∑{f(v[i],i!=x,y}, x and y are any distinct children }
    if (!conn) {
      FORR(kvp1,E[u]) FORR(kvp2,E[u]) if (kvp1.first!=kvp2.first) {
        int v=kvp1.first,w=kvp2.first;
        int x=f(v,u,1)+f(w,u,1)+E[pre][u];
        FORR(kvp3,E[u]) if(kvp3.first!=v&&kvp3.first!=w) x+=f(kvp3.first,u,0);
        res = min(res, x);
      }
    }
    
    // iii) take one children (parent may or may not be dropped)
    // cost ∈ { f(v[x],1)+∑{f(v[i],0),i!=x}+(0 or costV[u]+costE[parent,u])
    FORR(kvp,E[u]) {
      int v=kvp.first;
      int x=f(v,u,1);
      FORR(kvp2,E[u]) if(kvp2.first!=v) x+=f(kvp2.first,u,0);
      x+=costp;
      
      res=min(res,x);
    }
    
    return memo[u][conn]=res;
  }
  
  int minimize(vector<int> _costV, vector<int> pre, vector<int> _costE) {
    V=SZ(pre)+1;
    REP(i,V) E[i].clear();
    costV=_costV;
    REP(i,SZ(_costE)) {
      E[pre[i]][i+1]=_costE[i];
    }
    memset(memo,-1,sizeof memo);
    
    //return min(f(0,-1,0), f(0,-1,1)+costV[0]);
    return f(0,-1,0);
  }
};

// CUT begin
ifstream data("TreeAndCycle.sample");

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

bool do_test(vector<int> costV, vector<int> pre, vector<int> costE, int __expected) {
    time_t startClock = clock();
    TreeAndCycle *instance = new TreeAndCycle();
    int __result = instance->minimize(costV, pre, costE);
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
        vector<int> costV;
        from_stream(costV);
        vector<int> pre;
        from_stream(pre);
        vector<int> costE;
        from_stream(costE);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(costV, pre, costE, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500655333;
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
        cout << "TreeAndCycle (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
