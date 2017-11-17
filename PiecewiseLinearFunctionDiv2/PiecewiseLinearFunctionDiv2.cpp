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
 
 11/16/2017
 
 9:09-9:28 analysis
 9:29-9:34 implement and system test passed (310.28 pt)
 19:18-19:22 add simpler solution
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+586
  - http://torus711.hatenablog.com/entry/20130801/p2
  - https://topcoder.g.hatena.ne.jp/firewood/20130819/1376911103
  - http://emkcsharp.hatenablog.com/entry/SRM586/PiecewiseLinearFunctionDiv2
 
 Key:
  - Interval problem
  - Each query is independnet
 
 Summary:
  - I was doing unnecessary analysis to make formula of segments
   - y = (Y[i]-Y[i-1])*x + i*(Y[i]-Y[i-1])-Y[i]
   - this is not necessary to solve a problem
   - huge loss of time
  - It turned out that this is more likely to be an interval problem..
 
 */
class PiecewiseLinearFunctionDiv2 {
public:
  VI Y;
  int f(int q) {
    int N=SZ(Y);
    int res=count(Y.begin(),Y.end(),q);
    REP(i,N-1) {
      int l=min(Y[i],Y[i+1]),h=max(Y[i],Y[i+1]);
      if(l==h&&l==q) return -1;
      if(l<q&&q<h) ++res;
    }
    return res;
  }
  vector<int> countSolutions(vector<int> Y, vector<int> Q) {
    this->Y=Y;
    int M=SZ(Q);
    VI res(M,0);
    REP(i,M) res[i]=f(Q[i]);
    return res;
  }
};

class PiecewiseLinearFunctionDiv2_org {
  public:
  vector<int> countSolutions(vector<int> Y, vector<int> Q) {
    int M=SZ(Q),N=SZ(Y);
    VI res(M,0);
    REP(j,M) {
      int q=Q[j];
      REP(i,N-1) {
        if(Y[i]==Y[i+1]&&Y[i]==q) {
          res[j]=-1; break;
        }
        if(Y[i]<Y[i+1]) {
          res[j]+=(Y[i]<=q&&q<Y[i+1]);
        } else {
          res[j]+=(Y[i+1]<q&&q<=Y[i]);
        }
      }
      if(res[j]!=-1) res[j]+=(Y[N-1]==q);
    }
    return res;
  }
};

// CUT begin
ifstream data("PiecewiseLinearFunctionDiv2.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> Y, vector<int> query, vector<int> __expected) {
    time_t startClock = clock();
    PiecewiseLinearFunctionDiv2 *instance = new PiecewiseLinearFunctionDiv2();
    vector<int> __result = instance->countSolutions(Y, query);
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
        vector<int> Y;
        from_stream(Y);
        vector<int> query;
        from_stream(query);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(Y, query, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510852134;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PiecewiseLinearFunctionDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
