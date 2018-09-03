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
 
 9/2/2018
 
 16:40-16:58 analysis
 17:01 (170.55 pt)
 
 Editorials:
  - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm418
  - https://topcoder.g.hatena.ne.jp/peryaudo/20130928/1380331463
  - https://ameblo.jp/utmath/entry-10972124972.html?frm=theme
 
 I tried to solve leveraging math. However I couldn't.
 Thus I solved by brute-force. Math solution is shown in editorial.
 
 There are some options to take for sample space.
 I tried to see C(N,M) x C(N,M) product set for sample space.
 I couldn't move forward by myself though, I found how to compute on it.
 
 Suppose there are two sets of numbers, A and B.
 
 A: set of numbers that I choose
 B: set of numbers that organizer chooses
 
 |A|=|B|=M
 
 We want to know probability that `x` numbers are common between A and B.
 The size of sample space is C(N,M)*C(N,M). Firstly we choose `x` numbers, C(N,x) ways.
 We should choose M-x numbers out of N-x numbers, which is C(N-x,M-x) ways.
 Organizer finally chooses M-x out of N-x-(M-x)=N-M numbers.
 
 Now probability P(x) is..
 
  P(x) = C(N,x)*C(N-x,M-x)*C(N-M,M-x) / C(N,M) * C(N,M)
 
 Official editorial is focusing on my choice with sample space whose size is C(N,M).
 Organizer is already choosing M numbers. Note that it's already done.
 Ogranizer's choice is out of our sample space.
 We are choosing `x` numbers out of `M` which is organizer's choice.
 Now we are choosing `M-x` numbers which should not be contained in organizer's choice.
 Thus we can choose them out of M-M numbers.
 
  P(x) = C(M,x) * C(N-M,M-x) / C(N,M)
 
 This is eaual to P(x) that we previously made.
 Key to make formula in this model is that `x` is already fixed out of my sample space.
 
 Summary:
  - Poor math taste
 
 */

// 16:40-16:58 analysis
// 17:01 (170.55 pt)
class TwoLotteryGames {
  public:
  double getHigherChanceGame(int N, int M, int K) {
    LL tot=0,ok=0;
    REP(mask1,1<<N) if(__builtin_popcount(mask1)==M) {
      REP(mask2,1<<N) if(__builtin_popcount(mask2)==M) {
        tot++;
        int x=mask1&mask2;
        if(__builtin_popcount(x)>=K) ok++;
      }
    }
    return 1.0*ok/tot;
  }
};

// CUT begin
ifstream data("TwoLotteryGames.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int n, int m, int k, double __expected) {
    time_t startClock = clock();
    TwoLotteryGames *instance = new TwoLotteryGames();
    double __result = instance->getHigherChanceGame(n, m, k);
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
        int n;
        from_stream(n);
        int m;
        from_stream(m);
        int k;
        from_stream(k);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535931568;
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
        cout << "TwoLotteryGames (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
