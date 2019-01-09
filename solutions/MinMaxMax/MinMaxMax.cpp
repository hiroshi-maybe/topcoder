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

/**
 
 7/3/2017
 
 8:48-9:46 time up
 
 20:30 read https://www.topcoder.com/blog/single-round-match-710-editorials/
 21:11 passed samples and system test
 */

LL W[300][300];
LL dp[300][300];

// Floyd-Warshall, O(VN^3)
class MinMaxMax {
public:
  long long findMin(vector<int> a, vector<int> b, vector<int> ws, vector<int> vs) {
    int VN = SZ(vs), EN = SZ(a);
    vector<pair<int,int>> _vs;
    REP(i,VN) _vs.emplace_back(vs[i],i);
    sort(_vs.begin(),_vs.end());
    REP(i,VN) REP(j,VN) {
      W[i][j]=dp[i][j]=LLONG_MAX;
    }
    REP(i,EN) W[a[i]][b[i]]=W[b[i]][a[i]]=ws[i];
    
    REP(_k,VN) {
      int k = _vs[_k].second;
      REP(i,VN) {
        REP(j,VN) {
          LL w2 = max(W[i][k],W[k][j]);
          W[i][j] = min(W[i][j], w2);
          if (W[i][j]!=LLONG_MAX) dp[i][j] = min(dp[i][j], W[i][j]*max({vs[k],vs[i],vs[j]}));
        }
      }
    }
    
    LL res=0;
    REP(i,VN) REP(j,i) {
      res += dp[i][j];
    }
    return res;
  }
};

// vertices should have been sorted, so that we are sure path going through v[k] is upper bound at that moment.
class MinMaxMax_org {
  public:
  LL maxvs[300][300];
  LL maxes[300][300];
  unordered_map<int, unordered_map<int, LL>> W;

  void floydWarshall(int VN, vector<int> VW) {
    for(int k=0; k<VN; ++k) {
      for(int i=0; i<VN; ++i) {
        for(int j=0; j<VN; ++j) {
          if (W.count(i)==0||W[i].count(k)==0) continue;
          if (W.count(k)==0||W[k].count(j)==0) continue;
          
          LL cur = maxes[i][j] * maxvs[i][j];
          LL emax = max(W[i][k],W[k][j]);
          LL vmax = max(VW[i],max(VW[k],VW[j]));
          
          if (cur==0||emax*vmax<cur) {
            maxes[i][j] = emax;
            maxvs[i][j] = vmax;
          }
        }
      }
    }
  }
  
  long long findMin(vector<int> a, vector<int> b, vector<int> w, vector<int> vs) {
    int VN=SZ(vs), EN=SZ(a);
    REP(i,300) REP(j,300) {
      maxvs[i][j]=0; maxes[i][j]=0;
    }
    //memset(maxvs, 0, sizeof(maxvs));
    //memset(maxes, 0, sizeof(maxes));
    
    REP(i,EN) {
      int u = a[i], v=b[i];
      W[u][v] = w[i];
      W[v][u] = w[i];
      
      maxvs[u][v] = max(vs[u],vs[v]);
      maxvs[v][u] = max(vs[u],vs[v]);
      maxes[u][v] = w[i];
      maxes[v][u] = w[i];
    }
    
    floydWarshall(VN,vs);
    
    LL res=0;
    REP(i,VN) {
      FOR(j,i+1,VN) {
        res += maxes[i][j]*maxvs[i][j];
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("MinMaxMax.sample");

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

bool do_test(vector<int> a, vector<int> b, vector<int> w, vector<int> v, long long __expected) {
    time_t startClock = clock();
    MinMaxMax *instance = new MinMaxMax();
    long long __result = instance->findMin(a, b, w, v);
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        vector<int> w;
        from_stream(w);
        vector<int> v;
        from_stream(v);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, w, v, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499096905;
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
        cout << "MinMaxMax (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
