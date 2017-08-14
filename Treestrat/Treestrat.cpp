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

/**
 
 8/13/2017
 
 9:52-10:40,10:45-11:08 time up
 
 read editorials:
  - find max move from A[i] to a vertex where any B[i] cannot reach with the same number move
    - http://kenkoooo.hatenablog.com/entry/2015/10/11/034713
    - https://apps.topcoder.com/wiki/display/tc/SRM+670
    - most popular approach
    - some people are pre-computing closest B[x] from each vertex
  - http://kmjp.hatenablog.jp/entry/2015/10/11/1000
    - pre-compute reachable vertices within x moves
    - try moves in ascendent order. first x where there exists v where vertices reachable from B[i] covers reachable vertices for A[i]
    - for move x = 0...V,
        res = min { x : x=0...|V|,
          ∃A[i] V_A ⊆ V_B, V_A={v : dist(A[i],v)<=x}, V_B={v : dist(B[i],v)<=x}
        }
 
 12:00-13:45, 14:15-15:05 add solution
 19:00-19:12 add @kmjp solution
 
 Key:
  - We can solve each A[i] separatedly
  - Move is at most |V|
  - Size in problem is small. Use brute-force if applicable
  - distance from closest B[i] vs distance from A[i]
  - find vertex where A[i] can reach but B[i] cannot catch up by `x` move
  - number of move or distance from B[i] is more critical than distance from A[i]
 
 Summary:
  - separated problem for each A[i] 👍
  - tried to divide to two cases though, I could not solve 👎
    - surrounded by B[i]
    - go away to a branch where no B[i] stays
  - N is small. Try brute-force first and reduce states on top of it.
     - in this case, we can visit all the vertices many times because N is small
     - no specialization or classification is necessary for vertices
 
 */

// O(V^3) time
int MX[51][51];
class Treestrat {
public:
  const int Inf=100;
  VI A,B;
  int V;
  int roundcnt(vector<int> T, vector<int> A, vector<int> B) {
    V=SZ(T)+1;
    REP(i,V)REP(j,V) {
      if(i==j) MX[i][j]=0;
      else MX[i][j]=Inf;
    }
    FOR(i,1,V) {
      MX[i][T[i-1]]=MX[T[i-1]][i]=1;
    }
    REP(k,V)REP(i,V)REP(j,V) {
      MX[i][j]=min(MX[i][j],MX[i][k]+MX[k][j]);
    }
    
    LL R[51][51]={};
    REP(u,V)REP(d,V+1)REP(v,V) if(MX[u][v]<=d) R[u][d]|=1LL<<v;
    
    REP(m,51) {
      LL V_B=0;
      FORR(b,B) V_B|=R[b][m];
      FORR(a,A) {
        LL V_A=R[a][m];
        if((V_A&V_B)==V_A) return m;
      }
    }
    
    return V;
  }
};

// O(V^3+A*B*V^2) time < O(V^4) time < 7*10^6
class Treestrat_org {
  public:
  int MX[51][51];
  const int Inf=100;
  VI A,B;
  int V;
  int roundcnt(vector<int> T, vector<int> _A, vector<int> _B) {
    A=_A; B=_B;
    V=SZ(T)+1;
    REP(i,V)REP(j,V) {
      if(i==j) MX[i][j]=0;
      else MX[i][j]=Inf;
    }
    FOR(i,1,V) {
      MX[i][T[i-1]]=MX[T[i-1]][i]=1;
    }
    REP(k,V)REP(i,V)REP(j,V) {
      MX[i][j]=min(MX[i][j],MX[i][k]+MX[k][j]);
    }
//    REP(i,V)REP(j,V) dump3(i,j,MX[i][j]);
    
    int res=Inf;
    FORR(a,A) {
      int m=1;
      for(; m<=50; ++m) {
        if(!ok(a,m)) break;
      }
      res=min(res,m);
    }
    
    return res;
  }
  
  bool ok(int a, int m) {
    REP(v,V) {
      if(MX[a][v]>m) continue;
      // a can reach v
      bool ok=true;
      FORR(b,B) ok&=MX[v][b]>m;
      if(ok) return true; // no B[i] can teach v
    }
    
    return false;
  }
};

// CUT begin
ifstream data("Treestrat.sample");

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

bool do_test(vector<int> tree, vector<int> A, vector<int> B, int __expected) {
    time_t startClock = clock();
    Treestrat *instance = new Treestrat();
    int __result = instance->roundcnt(tree, A, B);
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
        vector<int> tree;
        from_stream(tree);
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(tree, A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502643147;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1050 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Treestrat (1050 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
