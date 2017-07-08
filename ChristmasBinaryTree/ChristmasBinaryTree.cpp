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

constexpr int MOD = 1e9+7;

/**
 
 7/7/2017
 
 9:30-9:49 time up
 10:10-10:40 pause
 19:25-20:30 give up
 
 21:50 read http://webcache.googleusercontent.com/search?q=cache:9AJRsQPUnFcJ:kmjp.hatenablog.jp/entry/2017/01/17/0930_1+&cd=4&hl=en&ct=clnk&gl=us&client=safari
 22:43 learned power matrix
 23:10 passed samples
 */

const int MX=105;
LL A[MX][MX];
LL S[MX][MX];

int N;
void powerMat(LL n) {
  LL X[105][105];
  LL tmp[105][105];
  memset(X,0,sizeof(X));
  REP(i,N) REP(j,N) X[i][j]=A[i][j];
  
  while(n) {
    // invariant: B = A^(2^i)
    memset(tmp,0,sizeof(tmp));
    if (n&1) {
      REP(i,N) REP(j,N) REP(k,N) tmp[i][j] += (S[i][k]*X[k][j])%MOD, tmp[i][j]%=MOD;
      REP(i,N) REP(j,N) S[i][j]=tmp[i][j];
    }
    memset(tmp,0,sizeof(tmp));
    REP(i,N) REP(j,N) REP(k,N) tmp[i][j] += (X[i][k]*X[k][j])%MOD, tmp[i][j]%=MOD;
    REP(i,N) REP(j,N) X[i][j]=tmp[i][j];
    
    n>>=1;
  }
}

class ChristmasBinaryTree {
public:
  int count(long long depth, vector<int> left, vector<int> right) {
    memset(A,0,sizeof(A));
    memset(S,0,sizeof(S));
    N=SZ(left);
    
    REP(i,N) ++A[i][left[i]], ++A[i][right[i]];
    REP(i,N) S[i][i]=1;
    
    powerMat(depth-1);
    LL res=0;
    REP(i,N) {
      LL sum=0;
      REP(j,N) sum += (S[i][j]*S[i][j])%MOD, sum%=MOD;
      res = max(res, sum);
    }
    
    return res;
  }
};

class ChristmasBinaryTree_wrong {
  public:
  LL dp[100][65][100];
  int count(long long depth, vector<int> left, vector<int> right) {
    memset(dp,0,sizeof(dp));
    int N=SZ(left);
    REP(i,N) {
      dp[i][0][i]=1LL;
      ++dp[i][1][left[i]];
      ++dp[i][1][right[i]];
    }

    FOR(bi,1,61) {
      REP(i,N) {
        vector<LL> tmp(N,0);
        REP(j,N) {
          REP(k,N) {
            tmp[j] += ((dp[i][bi][k]%MOD)*(dp[k][bi][j]%MOD))%MOD;
            tmp[j] %= MOD;
          }
        }
        REP(j,N) {
          REP(k,N) {
            dp[i][bi+1][j] += ((tmp[k]%MOD)*(dp[k][bi][j]%MOD))%MOD;
            dp[i][bi+1][j] %= MOD;
          }
        }
      }
    }

    LL res=0;
    REP(i,N) {
      VI cs(N,0);
      cs[i]=1;
      REP(bi,61) if((depth>>bi)&1) {
        REP(j,N) {
          cs[j]*=dp[i][bi][j]%MOD;
          cs[j]%=MOD;
          dump4(i,bi,j,cs[j]);
        }
//        dump2(i,bi);
      }
      LL x=0;
      REP(j,N) {
        dump2(j,cs[j]);
        x += (cs[j]*cs[j])%MOD;
      }
      res = max(res, x);
    }
    
    return (int)res;
  }
};

// CUT begin
ifstream data("ChristmasBinaryTree.sample");

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

bool do_test(long long depth, vector<int> left, vector<int> right, int __expected) {
    time_t startClock = clock();
    ChristmasBinaryTree *instance = new ChristmasBinaryTree();
    int __result = instance->count(depth, left, right);
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
        long long depth;
        from_stream(depth);
        vector<int> left;
        from_stream(left);
        vector<int> right;
        from_stream(right);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(depth, left, right, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499445023;
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
        cout << "ChristmasBinaryTree (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
