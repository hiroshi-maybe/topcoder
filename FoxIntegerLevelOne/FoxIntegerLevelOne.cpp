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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/8/2018
 
 8:49-9:34 Submit (218.46 pt) but WA
 17:30-17:32 fix too small Inf and ACC

 A*B=G*L is true. However G*L is too large < 10^24.
 We need to somehow upper-bound to brute-force something.
 
 By condition A<=L, I tried to brute-force in O(√L)
 
 A*p = L where p=B/G
 
 If A satisfies L%A==0, p = L/A = B/G.
 => B = p*G
 
 When L%x == 0, x could be either A or p.
 I missed x=p case. It took more time to catch up this bug 👎
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+535
  - http://mayokoex.hatenablog.com/entry/2016/03/18/234104
  - http://rkx1209.hatenablog.com/entry/2012/11/07/214858
  - http://topcoder.g.hatena.ne.jp/agw/20120303
  - http://www.vexorian.com/2012/03/srm-535-lame.html

 Official editorial is starting from G.
 
 A = a*G, B = b*G (a and b are co-prime)
 
 A*B = G*L
 <=> a*b*G*G = G*L
 <=> a*b = L/G
 
 We can brute-force a and b in O(√L/G)
 
 Key:
  - Find nice upper-bound so that search by O(√N) fits in 10^8
  - Co-prime => gcd(a,b)=1
 
 Summary:
  - too slow analysis 👎👎👎👎👎👎👎
   - I was wrongly remembering relationship between LCM and GCD
   - G*L is large. I should have changed my mind to find better upper-bound for search
   - Appropriate upper-bound is A=a*G or A*p=L
  - 1WA due to implementation bug 👎👎👎👎👎👎👎👎👎👎👎👎👎👎
   - A+B>1e12. A+B<=2*1e12
 
 */

class FoxAndGCDLCM {
public:
  LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
  long long get(long long G, long long L) {
    const LL Inf=1e13;
    if(L%G!=0) return -1;
    LL res=Inf;
    LL ab=L/G;
    for(LL a=1; a*a<=ab; ++a) if(ab%a==0) {
      LL b=ab/a;
      if(gcd(a,b)!=1) continue;
      res=min(res,G*(a+b));
    }
    return res;
  }
};

class FoxAndGCDLCM_org {
  public:
  LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
  long long get(long long G, long long L) {
    dump2(G,L);
    const LL Inf=1e13;
    LL res=Inf;
    for(LL x=1; x*x<=L; ++x) if(L%x==0) {
      LL A=x;
      LL p=L/x;
      LL B=p*G;
      dump4(A,B,A+B,gcd(A,B));
      if(gcd(A,B)==G) res=min(res,A+B);
//      dump3(A,B,A+B);
      B=L/x;
      A=x*G;
      dump4(A,B,A+B,gcd(A,B));
      if(gcd(A,B)==G) res=min(res,A+B);
    }
    return res==Inf?-1:res;
  }
};

// CUT begin
ifstream data("FoxIntegerLevelOne.sample");

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

bool do_test(long long G, long long L, long long __expected) {
    time_t startClock = clock();
    FoxAndGCDLCM *instance = new FoxAndGCDLCM();
    long long __result = instance->get(G, L);
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
        long long G;
        from_stream(G);
        long long L;
        from_stream(L);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(G, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1518108585;
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
        cout << "FoxIntegerLevelOne (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
