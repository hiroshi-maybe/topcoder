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
 
 1/7/2018
 
 15:20-15:27 system test passed (242.13 pt)
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+555
  - http://topcoder.g.hatena.ne.jp/agw/20120929/1348891177
 
 Add O(N^3) solution.
 
 */

// O(N^3) time
int mx[51][51];
class XorBoardDivTwo {
public:
  int R,C;
  int theMax(vector<string> B) {
    this->R=SZ(B),this->C=SZ(B[0]);
    int tot=0;
    REP(i,R)REP(j,C) mx[i][j]=B[i][j]=='1',tot+=mx[i][j];

    VI rsum(R,0),csum(C,0);
    REP(i,R) REP(j,C) rsum[i]+=mx[i][j],csum[j]+=mx[i][j];

    int res=0;
    REP(i,R)REP(j,C) {
      int rs=rsum[i]-mx[i][j],cs=csum[j]-mx[i][j];
      int sum=tot-rs-cs+(C-1-rs)+(R-1-cs);
      res=max(res,sum);
    }
    
    return res;
  }
};

// O(N^4) time
class XorBoardDivTwo_org {
  public:
  int R,C;
  int theMax(vector<string> B) {
    this->R=SZ(B),this->C=SZ(B[0]);
    REP(i,R)REP(j,C) mx[i][j]=B[i][j]=='1';
    
    int res=0;
    REP(i,R) {
      REP(j,C) mx[i][j]^=1;
      REP(j,C) {
        REP(k,R) mx[k][j]^=1;
        res=max(res,f());
        REP(k,R) mx[k][j]^=1;
      }
      REP(j,C) mx[i][j]^=1;
    }
  
    return res;
  }
  int f() {
    int res=0;
    REP(i,R)REP(j,C)res+=mx[i][j];
    return res;
  }
};

// CUT begin
ifstream data("XorBoardDivTwo.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    XorBoardDivTwo *instance = new XorBoardDivTwo();
    int __result = instance->theMax(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515367229;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 255 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "XorBoardDivTwo (255 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
