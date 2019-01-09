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
 
 9/21/2017
 
 9:28-9:44 analysis
 9:45-10:22 implemented and system test passed (413.05 pt)
 
 LCM(x,y) = x*y/GCD(x,y)
 Brute force x and validate it by DFS.
 candidate of x is at most 800 because highly composit number of 10^8 is at most 800.
 
 24:10-24:50 add simpler solution inspired by editorials
 
 editorial:
 - http://kmjp.hatenablog.jp/entry/2014/09/19/1000
 - https://apps.topcoder.com/wiki/display/tc/SRM+633
 
 key:
  - candidate of X[i] is upper-bounded by LCM. we can brute-force them
  - easy to validate candidate of X[i] by dfs
  - pay attention to different SCCs
 
 summary:
  - analysis was not so hard
  - I needed to fix bugs for some corner cases in implementation
  - solved by myself 👍
 
 */

vector<II> E[501];
int nn[501];
class GCDLCMEasy {
public:
  string yes= "Solution exists",no="Solution does not exist";
  int V;
  VI G,L;
  VI CC;
  
  bool dfs(int u) {
    int x=nn[u];
    FORR(p,E[u]) {
      int v=p.first,i=p.second,gcd=G[i],lcm=L[i];
      if(x%gcd!=0) return false;
      if(lcm%x!=0) return false;
      int y=lcm*gcd/x;
      // gcd=gcd(x,y) => lcm=x*y/gcd is TRUE
      // lcm=x*y/gcd => gcd=gcd(x,y) is FALSE
      // so below check is mandatory
      if(__gcd(x,y)!=gcd) return false;
      
      if(nn[v]!=0) {
        if(nn[v]!=y) return false;
        else continue;
      }
      nn[v]=y; CC.push_back(v);
      if(!dfs(v)) return false;
    }
    return true;
  }
  
  string possible(int V, vector<int> A, vector<int> B, vector<int> G, vector<int> L) {
    this->V=V;
    this->G=G; this->L=L;
    REP(i,V) E[i].clear();
    ZERO(nn);
    
    REP(i,SZ(A)) {
      int u=A[i],v=B[i];
      E[u].emplace_back(v,i);
      E[v].emplace_back(u,i);
    }
    
    REP(u,V) if(nn[u]==0) {
      bool ok=false;
      for(int x=1; x<=10000; ++x) {
        CC.clear();
        nn[u]=x; CC.push_back(u);
        if(dfs(u)) {
          ok=true;
          break;
        }
        FORR(u,CC) nn[u]=0;
      }
      if(!ok) return no;
    }
    
    return yes;
  }
};

int mx[501][501];
int GCD[501][501];
int LCM[501][501];
int ns[501];
int viz[501];
class GCDLCMEasy_org {
  public:
  string yes= "Solution exists",no="Solution does not exist";
  int V;
  void conn(int u) {
    if(viz[u]) return;
    viz[u]=true;
    REP(v,V) if(mx[u][v]>=0) conn(v);
  }
  
  bool dfs(int u, int n) {
    if(ns[u]>=0) return ns[u]==n;
    ns[u]=n;
    bool res=true;
    REP(v,V) if(mx[u][v]>=0) {
      if(n>mx[u][v]||mx[u][v]%n!=0) {
        res=false;
        break;
      }
      int n2=mx[u][v]/n;
      int gcd=__gcd(n,n2);
      if(gcd!=GCD[u][v]) return false;
      if((n*n2/gcd)!=LCM[u][v]) return false;
      res&=dfs(v,n2);
    }
    return res;
  }
  
  string possible(int V, vector<int> A, vector<int> B, vector<int> G, vector<int> L) {
    this->V=V;
    MINUS(mx); MINUS(LCM); MINUS(GCD);
    REP(i,SZ(A)) {
      int u=A[i],v=B[i],gcd=G[i],lcm=L[i];
      if(mx[u][v]!=-1&&mx[u][v]!=gcd*lcm) return no;
      mx[u][v]=mx[v][u]=gcd*lcm;
      GCD[u][v]=GCD[v][u]=gcd;
      LCM[u][v]=LCM[v][u]=lcm;
    }
    
    bool ok=true;
    MINUS(viz);
    MINUS(ns);
    REP(u,V) if(ns[u]==-1) {
      int mul=-1;
      REP(v,V) if(u!=v&&mx[u][v]>0) mul=mx[u][v];
      if(mul==-1) continue;
      
      ZERO(viz);
      conn(u);
      
//      dump2(u,mul);
      
      bool found=false;
      for(int n=1; n*n<=mul&&!found; ++n) if(mul%n==0) {
        REP(i,V) if(viz[i]) ns[i]=-1;
        if(dfs(u,n)) {
          found=true;
//          dump3(u,n,"ok");
          continue;
        }
        REP(i,V) if(viz[i]) ns[i]=-1;
        if(dfs(u,mul/n)) {
          found=true;
//          dump3(u,mul/n,"ok");
          continue;
        }
      }
//      dump2(u,found);
      if(!found) ok=false;
    }
    return ok?yes:no;
  }
};

// CUT begin
ifstream data("GCDLCMEasy.sample");

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

bool do_test(int n, vector<int> A, vector<int> B, vector<int> G, vector<int> L, string __expected) {
    time_t startClock = clock();
    GCDLCMEasy *instance = new GCDLCMEasy();
    string __result = instance->possible(n, A, B, G, L);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        vector<int> G;
        from_stream(G);
        vector<int> L;
        from_stream(L);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, A, B, G, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506011299;
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
        cout << "GCDLCMEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
