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

const int MX=105;
LL A[MX][MX], B[MX][MX];
constexpr int MOD = 1e9+7;

// matrix multiplication
// X = XxY, X: NxN matrix, Y: NxN matrix, N<MX
void timeMat(LL X[MX][MX], LL Y[MX][MX], int N) {
  LL tmp[MX][MX]; memset(tmp,0,sizeof(tmp));
  
  for(int i=0; i<N; ++i) {
    for(int j=0; j<N; ++j) {
      for(int k=0; k<N; ++k) tmp[i][j] += (X[i][k]*Y[k][j])%MOD, tmp[i][j]%=MOD;
    }
  }
  
  for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) X[i][j]=tmp[i][j];
}

// power matrix O(N^3*lg n)
// B = A^n, B: NxN matrix, A: NxN matrix, N<MX
//
// prequisite: A is initialized
void powerMat(LL n, int N) {
  assert(N<=MX);
  assert(n>=0);
  
  // B = I (identity matrix)
  memset(B,0,sizeof B);
  for(int i=0; i<N; ++i) B[i][i]=1;
  
  LL X[MX][MX];
  for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) X[i][j]=A[i][j];
  
  while(n) {
    // invariant: X = A^(2^i)
    if (n&1) timeMat(B,X,N); // B=B*X
    timeMat(X,X,N); // X=X^2
    n>>=1;
  }
}

/**
 
 7/9/2017
 
 12:42 start
 12:47 design done. ok let's use matrix power
 13:10 passed samples (519.32 pt) (it took some time to figure out matrix transformation)
 
 http://kmjp.hatenablog.jp/entry/2016/12/29/1130
 https://community.topcoder.com/stat?c=problem_solution&rd=16849&rm=329525&cr=40181468&pm=14467
 
 15:32 improve matrix library and add simpler solution with `n` multiplication instead of `n-1` multiplication
 
 */

// O(K^3*lg N)
class ModEquationEasy {
public:
  int count(int n, int K, int v) {
    memset(A,0,sizeof A);
    
    REP(i,K) REP(j,K) {
      // how many ((i*j)%K) for each i?
      A[i][(i*j)%K]++;
    }
    powerMat(n,K);
    
    return B[1][v]; // 1 * ∏ {X[i],i=1..n} = v
  }
};

// O(K^3*lg N)
class ModEquationEasy_org {
  public:
  int count(int n, int K, int v) {
    memset(A,0,sizeof A);

    REP(i,K) REP(j,K) {
      A[i][(i*j)%K]++;
    }
    // B=I*A^(n-1)
    powerMat(n-1,K);
    
    LL res=0;
    REP(i,K) {
      res += B[i][v], res%=MOD;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ModEquationEasy.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int n, int K, int v, int __expected) {
    time_t startClock = clock();
    ModEquationEasy *instance = new ModEquationEasy();
    int __result = instance->count(n, K, v);
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
        int K;
        from_stream(K);
        int v;
        from_stream(v);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, K, v, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499629312;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ModEquationEasy (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
