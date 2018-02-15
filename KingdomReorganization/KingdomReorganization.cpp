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
 
 2/13/2018
 
 9:19-9:43 analysis
 9:44-10:17 submit and ACC (379.47 pt)
 
 2/14/2018 read editorials and add solutions with library
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+531
   - Kruskal's algorithm
  - http://kmjp.hatenablog.jp/entry/2014/01/08/0930
   - Kruskal's algorithm
  - http://d.hatena.ne.jp/kusano_prog/20120203/1328294671
   - Prim's algorithm
  - http://area.hateblo.jp/entry/2014/04/15/172634
   - Prim's algorithm
  - https://topcoder.g.hatena.ne.jp/firewood/20120221/1329847766
   - Kruskal's algorithm
 
 Submit solutions:
  - Clean implementation with Kruskal's algorithm
   - https://community.topcoder.com/stat?c=problem_solution&rm=311372&rd=14724&pm=11282&cr=22930141
   - https://community.topcoder.com/stat?c=problem_solution&rm=311370&rd=14724&pm=11282&cr=22692058
 
 References:
  - MST: https://en.wikipedia.org/wiki/Minimum_spanning_tree
  - Prim's algorithm: https://en.wikipedia.org/wiki/Prim%27s_algorithm
  - Kruskal's algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
 
 Key:
  - Single path between vertices -> no cycle -> tree
  - If existing edges are reset, problem is reduced to minimum spanning tree
 
 Summary:
  - My first time to implement minimum spanning tree
  - It took a while to implement Prim's algorithm following Wikipedia's pseudo code
 
 */

struct MST {
public:
  int V;
  vector<tuple<int,int,int>> E;
  MST(int V): V(V) {
    uf = vector<int>(V);
    for(int i=0; i<V; ++i) uf[i]=i;
  }
  void edge(int u, int v, int w) {
    assert(u<V&&v<V);
    E.emplace_back(w,u,v);
  }
  int solve() {
    sort(E.begin(),E.end());
    
    int res=0;
    for(int i=0; i<E.size(); ++i) {
      int u,v,w;
      tie(w,u,v)=E[i];
      if(!same(u,v)) res+=w,unite(u,v);
    }
    return res;
  }
private:
  vector<int> uf;
  int find(int x) { return uf[x]==x?x:uf[x]=find(uf[x]); }
  void unite(int x, int y) {
    int px=find(x),py=find(y);
    if(px!=py) uf[px]=py;
  }
  int same(int x, int y) {
    return find(x)==find(y);
  }
};

// Kruskal's algorithm, O(E*lg V) time
class KingdomReorganization {
public:
  int cost(char c) {
    if(islower(c)) return c-'a'+26;
    else return c-'A';
  }
  int getCost(vector<string> A, vector<string> B, vector<string> C) {
    int V=SZ(A);
    MST mst(V);
    int tot=0;
    REP(j,V) REP(i,j) {
      if(A[i][j]=='1') {
        mst.edge(i,j,-cost(C[i][j]));
        tot+=cost(C[i][j]);
      } else {
        mst.edge(i,j,cost(B[i][j]));
      }
    }
    return tot+mst.solve();
  }
};

struct Prim {
public:
  int V;
  vector<vector<pair<int,int>>> E;
  Prim(int V): V(V) {
    E = vector<vector<pair<int,int>>>(V);
    viz = vector<int>(V,0);
  }
  void edge(int u, int v, int w) {
    assert(u<V&&v<V);
    E[u].emplace_back(v,w);
  }
  int solve() {
    set<pair<int,int>> Q;
    Q.emplace(0,0);
    int res=0;
    while(Q.size()) {
      auto it=Q.begin();
      auto p=*it;
      int w=p.first,u=p.second;
      Q.erase(it);
      if(viz[u]) continue;
      viz[u]=true;
      res+=w;
      for(auto p : E[u]) if(!viz[p.first]) {
        Q.emplace(p.second,p.first);
      }
    }
    return res;
  }
private:
  vector<int> viz;
};

// Prim's algorithm, O(E*lg V) time
class KingdomReorganization_prim {
public:
  int cost(char c) {
    if(islower(c)) return c-'a'+26;
    else return c-'A';
  }
  int getCost(vector<string> A, vector<string> B, vector<string> C) {
    int V=SZ(A);
    Prim mst(V);
    int tot=0;
    REP(j,V) REP(i,j) {
      if(A[i][j]=='1') {
        mst.edge(i,j,-cost(C[i][j]));
        mst.edge(j,i,-cost(C[i][j]));
        tot+=cost(C[i][j]);
      } else {
        mst.edge(i,j,cost(B[i][j]));
        mst.edge(j,i,cost(B[i][j]));
      }
    }
    return tot+mst.solve();
  }
};

// O(V^3) time
int G[51][51];
class KingdomReorganization_org {
  public:
  int cost(char c) {
    if(islower(c)) return c-'a'+26;
    else return c-'A';
  }
  int getCost(vector<string> A, vector<string> B, vector<string> C) {
    int V=SZ(A);
    int tot=0;
    REP(j,V) REP(i,j) {
      if(A[i][j]=='1') {
        G[i][j]=G[j][i]=-cost(C[i][j]);
        tot+=cost(C[i][j]);
      } else {
        G[i][j]=G[j][i]=cost(B[i][j]);
      }
    }
    
    SETI Q; Q.emplace(0);
    VI prev(V,-1);
    while(SZ(Q)<V) {
      II x={-1,-1};
      FORR(u,Q) REP(v,V) if(Q.count(v)==0) {
        if(x.first==-1||G[x.first][x.second]>G[u][v]) {
          x={u,v};
          prev[v]=u;
        }
      }
      Q.emplace(x.second);
    }
    
    int res=tot;
    FOR(i,1,V) res+=G[i][prev[i]];
    return res;
  }
};

// CUT begin
ifstream data("KingdomReorganization.sample");

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

bool do_test(vector<string> kingdom, vector<string> build, vector<string> destroy, int __expected) {
    time_t startClock = clock();
    KingdomReorganization *instance = new KingdomReorganization();
    int __result = instance->getCost(kingdom, build, destroy);
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
        vector<string> kingdom;
        from_stream(kingdom);
        vector<string> build;
        from_stream(build);
        vector<string> destroy;
        from_stream(destroy);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(kingdom, build, destroy, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1518542329;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "KingdomReorganization (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
