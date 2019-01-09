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
 
 10/19/2017
 
 9:53-10:15 analysis
 10:15-10:45 tried dfs to detect cycle with multiple paths though, TLEed in sample 7
 10:45-10:58 implement by Floyd-Warshall and system test passed (382.04 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+608
   - checking if there is a vertex whose outdegree>=2. very smart.
  - http://kmjp.hatenablog.jp/entry/2014/02/10/0930
   - simpler implementation to find outdegree>=2
 
 Editorials are finding multiple path of cycles by outdegree.
 If we use dfs, we can find it at vertex whose indegree >=2.
 
 In order to detect multiple paths of cycle, we can use in/out-degree.
 ∑indegree(v) = ∑outdegree(v). So we can use either condition.
 
 Thus we can check condition A) AND B) AND C)
  A) edge u->v exists
  B) path v↝u exists
  B) u's indegree >=2 OR v's outdegree>=2
 
 21:10-21:14 add dfs solution detecting outdegree>=2
 
 key:
  - Number of unique path is O(k^L) => There is a cycle with multiple paths
  - There exists a cycle with multiple paths => There is a vertex whose degree>=2 in strongly connected component
 
 summary:
  - analysis was not hard though, I couldn't implement code to find cycle with multiple paths quickly
  - looking at degree is so smart!
 
 submit solutions:
  - dfs
   - https://community.topcoder.com/stat?c=problem_solution&rm=320562&rd=15841&pm=13002&cr=22773690
   - https://community.topcoder.com/stat?c=problem_solution&rm=320572&rd=15841&pm=13002&cr=23032346
  - floyd-warshall
   - https://community.topcoder.com/stat?c=problem_solution&rm=320568&rd=15841&pm=13002&cr=22935387
  - bfs
   - https://community.topcoder.com/stat?c=problem_solution&rm=320593&rd=15841&pm=13002&cr=22859007
 
 */

// O(V^3) time
int mx[51][51];
class BigOEasy_org {
  public:
  string yes="Bounded",no="Unbounded";
  int V;
  string isBounded(vector<string> G) {
    this->V=SZ(G);
    ZERO(mx);
    REP(i,V)REP(j,V) mx[i][j]=G[i][j]=='Y';

    // no proof for this logic :(
    REP(k,V)REP(i,V)REP(j,V) if(i!=k&&k!=j) {
      mx[i][j]+=mx[i][k]*mx[k][j];
//      dump4(i,k,j,mx[i][j]);
    }
    REP(i,V) {
//      dump2(i,mx[i][i]);
      if(mx[i][i]>1) return no;
    }
    return yes;
  }
};

// O(V^3) time, SCC by floyd-warshall
class BigOEasy_floydwarshall_SCC {
public:
  string yes="Bounded",no="Unbounded";
  int V;
  string isBounded(vector<string> G) {
    this->V=SZ(G);
    ZERO(mx);
    REP(i,V)REP(j,V) mx[i][j]=G[i][j]=='Y';
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]|=mx[i][k]&mx[k][j];
    
    vector<vector<int>> SCCs;
    int viz[51]={0};
    ZERO(viz);
    // try all the pairs to build SCCs or use union-find tree
    REP(u,V) if(!viz[u]) {
      viz[u]=true;
      VI vs={u};
      REP(v,V) if(u!=v&&mx[u][v]&&mx[v][u]) vs.push_back(v),viz[v]=true;
      SCCs.push_back(vs);
    }
    
    FORR(vs, SCCs) {
      FORR(u,vs) {
        int deg=0;
        FORR(v,vs) if(u!=v&&G[u][v]=='Y') ++deg;
        if(deg>1) return no;
      }
    }
    return yes;
  }
};

// O(V^3) time, floyd-warshall, in/out-degree>=2
class BigOEasy {
public:
  string yes="Bounded",no="Unbounded";
  int V;
  string isBounded(vector<string> G) {
    this->V=SZ(G);
    ZERO(mx);
    REP(i,V)REP(j,V) mx[i][j]=G[i][j]=='Y';
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]|=mx[i][k]&mx[k][j];
    
    REP(i,V) {
      int deg=0;
      // outdegree>=2
      //REP(j,V) if(i!=j&&mx[j][i]&&G[i][j]=='Y') ++deg;
      // indegree>=2
      REP(j,V) if(i!=j&&mx[j][i]&&G[i][j]=='Y') ++deg;
      if(deg>1) return no;
    }
    
    return yes;
  }
};

// O(V^2) time
int viz[51];
class BigOEasy_dfs {
public:
  string yes="Bounded",no="Unbounded";
  int V;
  int dfs(int u, int st) {
    if(viz[u]) return 0;
    viz[u]=true;
    int res=0;
    REP(v,V) if(mx[u][v]) {
      res+=v==st;
      res+=dfs(v,st);
    }
    return res;
  }
  
  string isBounded(vector<string> G) {
    this->V=SZ(G);
    ZERO(mx);
    REP(i,V)REP(j,V) mx[i][j]=G[i][j]=='Y';
    
    REP(i,V) {
      ZERO(viz);
      if(dfs(i,i)>1) return no;
    }
    
    return yes;
  }
};

// O(2^V) time due to back-tracking
class BigOEasy_TLE {
public:
  string yes="Bounded",no="Unbounded";
  int V;
  set<VI> P;
  void dfs(VI &cur, int st) {
    if(SZ(P)>1) return;
    int u=cur.back();
    REP(i,SZ(cur)-1) if(cur[i]==u) return;
    dumpAR(cur);
    REP(v,V) if(mx[u][v]) {
      //      dump2(u,v);
      cur.push_back(v);
      if(v==st) {
        P.emplace(cur);
        //        dumpAR(cur);
      } else {
        dfs(cur,st);
      }
      cur.pop_back();
    }
  }
  
  string isBounded(vector<string> G) {
    this->V=SZ(G);
    ZERO(mx);
    REP(i,V)REP(j,V) mx[i][j]=G[i][j]=='Y';
    
     REP(i,V) {
     VI p={i};
     P.clear();
     dfs(p,i);
     dump2(i,SZ(P));
     //      FORR(p,P) dumpAR(p);
     
     if(SZ(P)>1) return no;
     }
     
     return yes;
  }
};

// CUT begin
ifstream data("BigOEasy.sample");

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

bool do_test(vector<string> graph, string __expected) {
    time_t startClock = clock();
    BigOEasy *instance = new BigOEasy();
    string __result = instance->isBounded(graph);
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
        string __answer;
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
        int T = time(NULL) - 1508431970;
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
        cout << "BigOEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
