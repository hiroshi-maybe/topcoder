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
 
 10/3/2018
 
 11:15-11:50 give up
 12:17 got AC after looking at @tourist's solution
 
 http://community.topcoder.com/stat?c=problem_solution&rm=305433&rd=14187&pm=11022&cr=22263204
 
 To achieve unknown (min number of jumps), we can transform condition.
 4^a*8^b*(s+1) ≡ 1 (mod 1e9+7) is the condition where k*(1e9+7) is reachable
 
 I tried to leverage another math property about x ≡ 1 (mod "prime number"). However I had no luck.
 I should have played around to induct property of cycle of 4^a*8^b.
 
 4^3=8^2 means that we can greedily select 8^2 to minimize (a+b).
 For each 8^b, we can check 8^b*4 and 8^b*4^2, which is optimal to minimize (a+b).
 
 Key:
  - If cycle is not co-prime, we can get minimal attempts by maximizing longer jump
 
 Summary:
  - Nice to figure out formula 4^a*8^b*(s+1) ≡ 1 (mod 1e9+7) from problem
  - I should have tested by simple and small numbers
   - 1 (0,0), 4 (1,0), 8(0,1), 16 (2,0), 64 (3,0) or (0,2), ..
   - This simple experiment should have suggested that we can greedily take 8 and adjust by 4
  - Try guessing in principal part nearer to the unknown ("How to solve it")
   - Observing behavior by 4^a*8^b is closer than my attempt of math w.r.t. 1 (mod "prime")
 
 */
class CarrotJumping {
  public:
  const LL MOD=1e9+7;
  const int L=1e5;
  int theJump(int s) {
    LL x=(s+1)%MOD; int res=L+1;
    REP(l,L) {
      if(x*4%MOD==1) SMIN(res,l+1);
      if(x*16%MOD==1) SMIN(res,l+2);
      x=x*8%MOD;
      if(x%MOD==1) SMIN(res,l+1);
    }
    return res<=L?res:-1;
  }
};

// CUT begin
ifstream data("CarrotJumping.sample");

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

bool do_test(int init, int __expected) {
    time_t startClock = clock();
    CarrotJumping *instance = new CarrotJumping();
    int __result = instance->theJump(init);
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
        int init;
        from_stream(init);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(init, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1538590514;
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
        cout << "CarrotJumping (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
