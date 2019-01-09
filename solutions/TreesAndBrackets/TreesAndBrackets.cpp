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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/17/2018 SRM731
 
 9:01-9:23 ACC (162.39 pt)
 
 res = true if T2 is subtree of T1.
 
 Suppose we have two roots r1 and r2. We want to know f(r1,r2) where r2 is subtree of r1.
 If children of r2 are all subtree of children of r1, r2 is subtree of r1.
 Order of children matters. So we can keep comparing from left to right.
 If f(c1,c2) is true, we can move pointer of r2.
 f(r1,r2) = true if pointer of r2 reaches the end.
 
 Editorials:
  - https://togetter.com/li/1209650
  - http://kmjp.hatenablog.jp/entry/2018/03/19/0900
   - dp by interval of substring
  - http://hamayanhamayan.hatenablog.jp/entry/2018/03/18/082351
   - Parsing tree before comparison. Otherwise same as mine
 
 Summary:
  - I was not very confident about complexity though, solved without even compilation error 👍
  - Raring 1272->1377 (highest 👏)
 
 */

class TreesAndBrackets {
  public:
  string yes="Possible",no="Impossible";
  bool f(string s1, string s2) {
    if(s1==s2) return true;
    if(s2.empty()) return true;
    
    string ts[2]={s1,s2};
    vector<string> T[2];
    REP(c,2) {
      string t=ts[c];
      int b=0;
      string x="";
      FOR(i,1,SZ(t)) {
        b+=t[i]=='('?1:-1;
        x+=t[i];
        if(b==0) T[c].push_back(x),x="";
      }
    }
    int p=0;
    REP(i,SZ(T[0])) if(p<SZ(T[1])&&f(T[0][i],T[1][p])) ++p;
    return p==SZ(T[1]);
  }
  string check(string t1, string t2) {
    return f(t1,t2)?yes:no;
  }
};

// CUT begin
ifstream data("TreesAndBrackets.sample");

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

bool do_test(string t1, string t2, string __expected) {
    time_t startClock = clock();
    TreesAndBrackets *instance = new TreesAndBrackets();
    string __result = instance->check(t1, t2);
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
        string t1;
        from_stream(t1);
        string t2;
        from_stream(t2);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(t1, t2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521302468;
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
        cout << "TreesAndBrackets (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
