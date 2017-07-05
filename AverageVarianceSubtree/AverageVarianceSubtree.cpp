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

#define FORR(x,arr) for(auto& x:arr)
#define ZERO(dp) memset(dp, 0, sizeof(dp))
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define SZ(a) int((a).size())
typedef vector < int > VI;

typedef long double LB;
int N;
LB W[101]; // x[i]-mu
VI E[101];

LB SN[51][51]; // Number of subsets
LB SUM[51][51]; // SUM(X)
LB EX2[51][51]; // SUM(X^2) (E(X^2)=SUM(X^2)/N)
LB E2X[51][51]; // SUM(X)^2 (E^2(X)=SUM(X)^2/N^2)

/**
 
 7/3/2017
 
 22:58-23:25 time up
 
 7/4/2017
 
 read http://kmjp.hatenablog.jp/entry/2017/05/07/1000
 23:12 start copying solution
 25:30 passed samples and system test
 
 */

class AverageVarianceSubtree {
public:
  
  int dfs(int u, int pre, int ng) {
    SN[u][1]=1;
    SUM[u][1]=W[u];
    EX2[u][1]=W[u]*W[u];
    E2X[u][1]=SUM[u][1]*SUM[u][1];
    
    int C=1; // tree size
    FORR(v,E[u]) if(v!=pre&&v>ng) {
      int TC=dfs(v,u,ng);
      LB SN_[52]={};
      LB SUM_[52]={};
      LB EX2_[52]={};
      LB E2X_[52]={};
      
      FOR(n,1,C+TC+1) {
        // DP for `n`-sized subtree
        FOR(l,1,C+1) {
          // L = { `l`-sized `u`-rooted subtree outside `v` }
          // R = { `r`-sized subtree whose root is `v` }
          // sum for L x R
          int r=n-l;
          if(r<0||r>TC) continue;
          EX2_[n]+=EX2[u][l]*SN[v][r]/* SUM_X^2(L)*|R| */+2*SUM[u][l]*SUM[v][r]+EX2[v][r]*SN[u][l]/* SUM_X^2(R)*|L| */;
          SUM_[n]+=SN[u][l]*SUM[v][r]/* SUM(R)*|L| */+SN[v][r]*SUM[u][l]/* SUM(L)*|R| */;
          E2X_[n]+=SN[u][l]*E2X[v][r]/* SUM^2(R)*|L| */+SN[v][r]*E2X[u][l]/* SUM^2(L)*|R| */;
          SN_[n]+=SN[u][l]*SN[v][r]/* |L|*|R| */;
        }
      }
      C+=TC;
      
      REP(i,C+1) {
        SN[u][i]=SN_[i];
        SUM[u][i]=SUM_[i];
        EX2[u][i]=EX2_[i];
        E2X[u][i]=E2X_[i];
      }
    }
    SN[u][0]=1;
    
    return C;
  }
  
  double average(vector<int> p, vector<int> weight) {
    N=SZ(weight);
    
    LB mu=0;
    REP(i,N) {
      E[i].clear();
      W[i]=weight[i];
      mu+=W[i];
    }
    mu /= N;
    REP(i,N) W[i]-=mu;
    
    REP(i,N-1) {
      E[i+1].push_back(p[i]);
      E[p[i]].push_back(i+1);
    }
    
    ZERO(SN); ZERO(SUM); ZERO(EX2); ZERO(E2X);
    
    LB Y=0, VN=0;
    REP(u /* root of tree */,N) {
      dfs(u,u,u);
      
      FOR(n,1,51) {
        VN += SN[u][n];
        Y += E2X[u][n]/n - EX2[u][n]/n/n;
      }
    }
    
    return Y/VN;
  }
};

// CUT begin
ifstream data("AverageVarianceSubtree.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> p, vector<int> weight, double __expected) {
    time_t startClock = clock();
    AverageVarianceSubtree *instance = new AverageVarianceSubtree();
    double __result = instance->average(p, weight);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> p;
        from_stream(p);
        vector<int> weight;
        from_stream(weight);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(p, weight, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499147884;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "AverageVarianceSubtree (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
