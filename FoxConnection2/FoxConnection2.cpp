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
 
 10/28/2017
 
 16:58-17:39 analysis
 17:40-17:55 implementation
 17:55-18:14 debug and pause
 22:05-22:11 fixed a bug and system test passed
 
 Editorials:
  - http://kmjp.hatenablog.jp/entry/2014/01/12/1000
   - limit accessible nodes by x >= root node to avoid duplicated counting
  - https://apps.topcoder.com/wiki/display/tc/SRM+604
   - make one direction edge to form tree to avoid duplicated counting

 Key:
  - Avoid duplicated count by tracing path in consistent manner
  - Tree DP to count sub-trees
 
 Summary:
  - I should have solved this kind of tree DP. However it took too much time to remember back it 👎
  - Also I spent significant time to figure out that I need to differentiate states to count root or not.
   - poor analysis
 
 Submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=320187&rd=15837&pm=12951&cr=23264406
   - use visited flag to avoid duplicated counting
  - https://community.topcoder.com/stat?c=problem_solution&rm=320185&rd=15837&pm=12951&cr=23138918
   - same as official editorial
 
 */
constexpr int MOD = 1e9+7;

vector<int> E[51];

// O(N^4) time, O(N^2) space
class FoxConnection2_org {
  public:
  LL memo[51][51][2];
  LL f(int u, int cnt, int pre, bool req) {
    if(cnt==0) return 0;
//    dump4(u,cnt,pre,memo[u][cnt]);
//    dump3(u,cnt,pre);
    if(memo[u][cnt][req]>=0) return memo[u][cnt][req];
    VI vs;
    FORR(v,E[u]) if(v!=pre) vs.push_back(v);
//    dumpAR(vs);
    int N=SZ(vs);
    
    LL res=0;
    if (!req) {
      FORR(v,vs) res+=f(v,cnt,u,0),res%=MOD;
    }
//    dump4(u,cnt,N,res);
    LL dp[51][51]={};
    dp[0][0]=1;
    FOR(i,1,N+1) REP(x,cnt) REP(k,x+1) {
      if (k==0) {
        dp[i][x]+=dp[i-1][x-k]; dp[i][x]%=MOD;
      } else {
        dp[i][x]+=dp[i-1][x-k]*f(vs[i-1],k,u,1); dp[i][x]%=MOD;
      }
    }
//    dump3(u,cnt,dp[N][cnt-1]);
    res+=dp[N][cnt-1],res%=MOD;
//    dump3(u,cnt,res);
    return memo[u][cnt][req]=res;
  }
  
  int ways(vector<int> A, vector<int> B, int k) {
    REP(i,51) E[i].clear();
    MINUS(memo);
    REP(i,SZ(A)) {
      int u=A[i]-1,v=B[i]-1;
      E[u].push_back(v);
      E[v].push_back(u);
    }
    return f(0,k,-1,0);
  }
};

// O(N^3) time
// As shown in official editorial, Number of (u,e) is |E|+|V| = 2*N-1 in total
// We have {(u,e)} = { (v,degree(v)+1) : v∈V }
// |{u,e}| = ∑ { degree(v)+1 : v∈V } = ∑ { degree(v) : v∈V } + ∑ { 1 : v∈V } = |E|+|V|
class FoxConnection2 {
public:
  int V;
  int degree[51];
  int g[51][51];
  int mem[51][51][51];
  void makeTree(int u, int pre, VI &A, VI &B) {
    degree[u]=0;
    REP(i,SZ(A)) {
      int x=A[i]-1,y=B[i]-1;
      if(x==u&&y!=pre) {
        g[x][degree[u]++]=y;
        makeTree(y,u,A,B);
      }
      if(y==u&&x!=pre) {
        g[y][degree[u]++]=x;
        makeTree(x,u,A,B);
      }
    }
  }
  
  set<II> S;
  LL f(int u, int cnt, int e) {
    if(mem[u][cnt][e]>=0) return mem[u][cnt][e];
    S.emplace(u,e);
//    dump4(u,cnt,e,degree[u]);
    if(cnt==0) return 1; // no assgnment
    if(e==degree[u]) return cnt==1; // no more children
    LL res=0;
    REP(k,cnt) {
      LL x=f(g[u][e],k,0);
      LL y=f(u,cnt-k,e+1);
      res+=(x*y)%MOD,res%=MOD;
    }
    return mem[u][cnt][e]=res;
  }
  
  int ways(vector<int> A, vector<int> B, int K) {
    this->V=SZ(A)+1;
    ZERO(degree);
    makeTree(0,-1,A,B);
    MINUS(mem);
    LL res=0;
    REP(u,V) res+=f(u,K,0),res%=MOD;
    
    FORR(p,S) dump2(p.first,p.second);
//    dump2(V,SZ(S));
    return res;
  }
};

// CUT begin
ifstream data("FoxConnection2.sample");

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

bool do_test(vector<int> A, vector<int> B, int k, int __expected) {
    time_t startClock = clock();
    FoxConnection2 *instance = new FoxConnection2();
    int __result = instance->ways(A, B, k);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509235075;
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
        cout << "FoxConnection2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
