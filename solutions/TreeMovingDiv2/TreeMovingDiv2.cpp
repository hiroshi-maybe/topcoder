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
using namespace std;

// type alias
typedef long long LL;

typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;

typedef pair<int,int> II;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

constexpr int MOD = 1e9+7;

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/*
 7/2/2017
 
 14:34-15:22 understand problem and design
 15:22 coding
 16:28 give up

 17:10-17:55,19:15-, read editorial and solutions
 https://www.topcoder.com/blog/single-round-match-711-editorials/
 https://community.topcoder.com/stat?c=problem_solution&rd=16880&rm=329835&cr=23331831&pm=14556
 http://kmjp.hatenablog.jp/entry/2017/03/26/1000
 http://suikaba.hatenablog.com/entry/2017/03/25/235808
 
 20:24 finally understood algorithm.
 21:10 passed samples and system test
 */

int u[51][51];
int v[51][51];
int deletable[51][51][51];
LL dp[51][51];

class TreeMovingDiv2 {
public:
  int M, N;
  bool dfs(int tid, int eid, int u, int T, int prev) {
    if (u==T) return true;
    
    FORR(p,es[tid%M][u]) {
      int v=p.first, eid2 = p.second;
      if (v==prev) continue;
      if (dfs(tid,eid,v,T,u)) {
        deletable[tid][eid][eid2] = true;
        return true;
      }
    }
    
    return false;
  }
  
  vector<vector<vector<II>>> es;
  int count(int _N, vector<int> roots, vector<int> a, vector<int> b, vector<int> c) {
    N = _N;
    M=SZ(roots);
    
    es = vector<vector<vector<II>>>(51, vector<vector<II>>(51));
    memset(u, 0, sizeof(u));
    memset(v, 0, sizeof(v));
    memset(deletable, 0, sizeof(deletable));
    
    buildEdges(N,roots,a,b,c);
    
    REP(i,M) {
      REP(j,N-1) dfs(i+1,j,u[i][j],v[i][j], -1);
    }
    
    LL res = 0;
    REP(j,N-1) {
      memset(dp,0,sizeof(dp));
      dp[0][j]=1;
      FOR(i,1,M+1) {
        REP(eid1, N-1) {
          REP(eid2, N-1) {
            if (deletable[i][eid1][eid2]) {
              dp[i][eid2] += dp[i-1][eid1];
              dp[i][eid2] %= MOD;
            }
          }
        }
      }
      
      res += dp[M][j];
    }
    
    return res%MOD;
  }
  
  void buildEdges(int N, VI &roots, VI &as, VI &bs, VI &cs) {
    int M=SZ(roots);
    vector<LL> x(N);
    REP(i,M) {
      x[0] = cs[i];
      FOR(k,1,N-1) x[k] = ((LL)as[i]*x[k-1]+(LL)bs[i])%MOD;
      
      REP(j,N-1) {
        u[i][j] = (roots[i]+j+1) % N;
        v[i][j] = (roots[i]+(x[j] % (j+1))) % N;
        es[i][u[i][j]].emplace_back(v[i][j], j);
        es[i][v[i][j]].emplace_back(u[i][j], j);
      }
    }
  }
};


class TreeMovingDiv2_wrong {
  public:
  LL dp[51][51][51];
  int es[51][51][51];
  int count(int N, vector<int> roots, vector<int> a, vector<int> b, vector<int> c) {
    memset(dp, 0, sizeof(dp));
    memset(es, 0, sizeof(es));
    
    int M=SZ(roots);
    buildEdges(N,roots,a,b,c);
    
    LL sumk=0;
    REP(i,N) {
      REP(j,i) {
        dp[i][j][1] = es[i][j][0];
        if(!es[i][j][1]) sumk+=dp[i][j][1];
      }
    }
    
    FOR(k,1,M) {
      dump2(k,sumk);

      LL nextSumk=0;
      
      REP(i,N) {
        REP(j,i) {
          if (es[i][j][k]) {
            dp[i][j][k+1] = dp[i][j][k];
          } else {
            dp[i][j][k+1] = sumk;
          }
          if (k<N-1&&!es[i][j][k+1]) nextSumk += dp[i][j][k+1];

//          dump4(i,j,k+1,dp[i][j][k+1]);
          nextSumk %= MOD;
        }
      }
      
      sumk = nextSumk;
    }
    
    LL res=0;
    REP(i,N) {
      REP(j,i) {
        dump4(i,j,N,dp[i][j][M]);
        if (es[i][j][0]) res += dp[i][j][M];
        res %= MOD;
      }
    }
    
    return (int)res;
  }
  
  void buildEdges(int N, VI &roots, VI &as, VI &bs, VI &cs) {
    int M=SZ(roots);
    vector<LL> x(N);
    REP(i,M) {
      x[0] = cs[i];
      FOR(k,1,N-1) x[k] = (LL)as[i]*x[k-1]+(LL)bs[i];
      
      REP(j,N-1) {
        LL u = (roots[i]+j+1) % N;
        LL v = (roots[i]+(x[j] % (j+1))) % N;
        if (v>u) swap(u,v);
        es[u][v][i] = true;
      }
    }
  }
};

// CUT begin
ifstream data("TreeMovingDiv2.sample");

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

bool do_test(int n, vector<int> roots, vector<int> a, vector<int> b, vector<int> c, int __expected) {
    time_t startClock = clock();
    TreeMovingDiv2 *instance = new TreeMovingDiv2();
    int __result = instance->count(n, roots, a, b, c);
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
        vector<int> roots;
        from_stream(roots);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        vector<int> c;
        from_stream(c);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, roots, a, b, c, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499031268;
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
        cout << "TreeMovingDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
