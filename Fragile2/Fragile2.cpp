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
 
 9/7/2017
 
 9:21-10:03 sytem test passed (234.68 pt)
 
 editorial:
  - https://twitter.com/evima0/status/562245868703588352
    - writer's comment
  - http://kmjp.hatenablog.jp/entry/2015/02/06/0930
  - http://roiti46.hatenablog.com/entry/2015/02/02/TopCoder_SRM_648_Div2
 
 key:
  - brute force pair of vertices to be removed
  - count number of connected component
   - mark all the vertices which can be visited from i=0..V-1
    - whenever you can start a new iteration, it's new component which is not visited in previous iterations
    - this step is same for both floyd-warshall and dfs
   - another approach is union-find tree
  - if removed vertices are marked as visited, no need to rebuild graph every time
 
 summary:
  - I misunderstood that I should remove edges
  - I tried floyd-warshall first though, judge of connected component was wrong
  - eventually solved by dfs though, I spent some time to fix trivial bug
  - I should solve this problem more quickly 👎
 
 23:25-23:54 add floyd-warshall solution
 23:57-24:08 add union-find solution
 
 submit solutions:
  - dfs
    - https://community.topcoder.com/stat?c=problem_solution&rm=325029&rd=16312&pm=13648&cr=22867887
    - https://community.topcoder.com/stat?c=problem_solution&rm=325004&rd=16312&pm=13648&cr=23320202
    - https://community.topcoder.com/stat?c=problem_solution&rm=325005&rd=16312&pm=13648&cr=23305191
    - https://community.topcoder.com/stat?c=problem_solution&rm=325003&rd=16312&pm=13648&cr=23197675
 
 */
int E[21][21];
class Fragile2 {
  public:
  int V;
  int viz[21];
  void dfs(int u) {
    if(viz[u]>0) return;
    viz[u]=1;
    REP(v,V) if(E[u][v]) dfs(v);
  }
  
  int cnt(int x, int y) {
    int res=0;
    REP(i,V) if(!viz[i]) {
      ++res;
      dfs(i);
    }
    return res;
  }
  
  int countPairs(vector<string> G) {
    vector<II> es;
    V=SZ(G);
    ZERO(E);
    REP(j,V)REP(i,j) if(G[i][j]=='Y') E[i][j]=E[j][i]=1;
    
    int cn=cnt(-1,-1);
    
    int res=0;
    REP(y,V) REP(x,y) {
      ZERO(viz);
      viz[x]=viz[y]=1;
      int cn2=cnt(x,y);
      res+=cn2>cn;
    }
    
    return res;
  }
};

int mx[21][21];
class Fragile2_floydwarshall {
public:
  int V;
  int viz[21];
  
  int cnt() {
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]|=mx[i][k]&mx[k][j];
    int res=0;
    REP(i,V) if(!viz[i]) {
      ++res;
      REP(j,V) viz[j]|=mx[i][j];
    }
    return res;
  }
  
  int countPairs(vector<string> G) {
    vector<II> es;
    V=SZ(G);
    ZERO(mx);
    REP(j,V)REP(i,j) if(G[i][j]=='Y') mx[i][j]=mx[j][i]=1;
    
    ZERO(viz);
    int cnt1=cnt();
    
    int res=0;
    REP(y,V) REP(x,y) {
      ZERO(mx);
      REP(j,V)REP(i,j) if(G[i][j]=='Y') mx[i][j]=mx[j][i]=1;
      REP(i,V) mx[i][x]=mx[x][i]=mx[i][y]=mx[y][i]=0;
      
      ZERO(viz); viz[x]=viz[y]=1;
      int cnt2=cnt();
      
      res+=cnt2>cnt1;
    }
    
    return res;
  }
};

class Fragile2_unionfind {
public:
  int V;
  int uf[21];
  int find(int u) { return uf[u]==u?u:uf[u]=find(uf[u]); }
  void unite(int u, int v) {
    int up=find(u),vp=find(v);
    if(up!=vp) uf[vp]=up;
  }
  int groups() {
    SETI S;
    REP(i,V) S.emplace(find(i));
    return SZ(S);
  }
  
  int countPairs(vector<string> G) {
    this->V=SZ(G);
    ZERO(uf);
    REP(i,V) uf[i]=i;
    REP(j,V)REP(i,j) if(G[i][j]=='Y') unite(i,j);
    int cnt1=groups();
    
    int res=0;
    REP(y,V) REP(x,y) {
      ZERO(uf);
      REP(i,V) uf[i]=i;
      REP(j,V)REP(i,j) if(i!=x&&i!=y&&j!=x&&j!=y&&G[i][j]=='Y') unite(i,j);
      
      res+=groups()-2>cnt1;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("Fragile2.sample");

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

bool do_test(vector<string> graph, int __expected) {
    time_t startClock = clock();
    Fragile2 *instance = new Fragile2();
    int __result = instance->countPairs(graph);
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
        vector<string> graph;
        from_stream(graph);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(graph, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504801295;
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
        cout << "Fragile2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
