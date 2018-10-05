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
 
 10/4/2018
 
 16:17-16:47 give up
 18:15-18:37 read editorials and got AC
 
 http://apps.topcoder.com/wiki/display/tc/SRM+484

 Typical "problem to prove" problem. Some hypothesis is needed to search without TLE.
 My observation focusing on carry was correct. However I misunderstood that 14*14 has no carry (actually it has). Thus I got lost.
 
 Suppose x=a*10+b (ab in decimal representation).
 
 S(x)*S(x) = (a+b)*(a+b) = a^2 + 2*a*b + b^2
 
 x*x = (a*10+b)*(a*10+b) = a^2 *10^2 + 2*a*b *10^1 + b^2 *10^0
 If we want to make S(x*x) = S(x)*S(x), a^2<10 and 2*a*b<10 and b^2<10 should hold.
 Thus digit ∈ {0,1,2,3} (3*3<10, 4*4>=10)
 
 N has at most 10 digits. 4^10 is affordable in terms of time limit.
 
 Summary:
  - misunderstanding of 14*14 was critical
  - I was looking at x=abc (in decimal) and figured out co-efficient. I should review 14*14 in terms of it
  - Experiment by small numbers was nice start to induct general property. I needed accurate understanding hypothesis and proof
 
 */
class RabbitNumber {
  public:
  int S(LL n) {
    int res=0;
    while(n>0) res+=n%10,n/=10;
    return res;
  }
  int res=0;
  void dfs(int p, LL cur, int N) {
    if(p==9) {
      if(cur>N) return;
      if(S(cur*cur)==S(cur)*S(cur)) ++res;
      return;
    }
    REPE(d,3) dfs(p+1,cur*10+d,N);
  }
  int f(int N) {
    res=0;
    if(N==1e9) ++res;
    dfs(0,0,N);
    return res;
  }
  int theCount(int low, int high) {
    return f(high)-f(low-1);
  }
};

// CUT begin
ifstream data("RabbitNumber.sample");

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

bool do_test(int low, int high, int __expected) {
    time_t startClock = clock();
    RabbitNumber *instance = new RabbitNumber();
    int __result = instance->theCount(low, high);
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
        int low;
        from_stream(low);
        int high;
        from_stream(high);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(low, high, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1538695025;
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
        cout << "RabbitNumber (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
