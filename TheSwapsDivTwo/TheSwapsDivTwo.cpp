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
 
 12/11/2017
 
 8:38-8:41 system test passed (247.68 pt)
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+575
  - http://kmjp.hatenablog.jp/entry/2013/04/08/0930
  - http://tatsyblog.sakura.ne.jp/wordpress/contests/topcoder/200/
  - http://kujira16.hateblo.jp/entry/2013/04/07/183401
  - http://sucrose.hatenablog.com/entry/2013/04/07/031251
 
 Good to know how to count without using set. Added the solution too.
 
 We need to count unique sequence after swapping elements only once.
 
 Suppose we are swapping xs[i] and xs[j].
 Obviously when xs[i]==xs[j], sequence doesn't change.
 This happens only when same elements are being swapped.
 We can count it only once by searching pair of the same character.
 
 Suppose we are swapping xs[i] (=A) and xs[j] (=B) only once.
 We get sequence ***B**A* from ***A**B*.
 The obtained sequence should be different and distinct as long as A!=B.
 We can just count them.
 
 */

class TheSwapsDivTwo {
public:
  int find(vector<int> xs) {
    int N=SZ(xs);
    int res=0;
    // count sequence which is same as original only once.
    REP(j,N)REP(i,j) if(xs[i]==xs[j]) { ++res; goto next; }
  next:
    REP(j,N)REP(i,j) if(xs[i]!=xs[j]) ++res;
    return res;
  }
};


class TheSwapsDivTwo_org {
  public:
  int find(vector<int> xs) {
    set<VI> S;
    int N=SZ(xs);
    REP(j,N)REP(i,j) {
      VI ys=xs;
      swap(ys[i],ys[j]);
      S.emplace(ys);
    }
    return SZ(S);
  }
};

// CUT begin
ifstream data("TheSwapsDivTwo.sample");

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

bool do_test(vector<int> sequence, int __expected) {
    time_t startClock = clock();
    TheSwapsDivTwo *instance = new TheSwapsDivTwo();
    int __result = instance->find(sequence);
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
        vector<int> sequence;
        from_stream(sequence);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(sequence, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513010311;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheSwapsDivTwo (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
