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
 
 9/10/2017
 
 17:04-17:35 pause
 20:20-20:40
 22:50-23:04 system test passed

 recurrence relation:
 
 f(n,k) = p * f(n-ceil(n/M),k-1) + (1-p) * f(n-floor(n/M),k-1)
 f(0,k) = 0
 f(n,0) = n>=1
 
 res = f(N,K)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+645
  - http://kmjp.hatenablog.jp/entry/2015/01/21/1000
  - http://mayokoex.hatenablog.com/entry/2015/03/31/082745
 
 key:
  - recurrence relation is trivial
  - state is pretty small
    - every time subproblems consist of n-floor(n/M) or n-ceil(n/M)
    - every K, actually size of n increases by at most 2 as described in official editorial
 
 summary:
  - dp recurrence relation was easy 👍
  - it took 30 mins to fix a bug of probability computation between LL and double 👎
  - I was not sure why number of states is small though, understood by printing states in sample 3
  - error is only 1e-3. I wondered if I would prune function call though, it was not necessary.
 
 iterative dp solution:
  - https://community.topcoder.com/stat?c=problem_solution&rm=324795&rd=16277&pm=13349&cr=40022337
 
 */
class JanuszInTheCasino {
  public:
  int M;
  unordered_map<LL,unordered_map<int,double>> memo;
  double f(LL n, int k) {
    if(n==0) return 0;
    if(k==0) return n>=1?1.0:0.0;
    if(memo.count(n)&&memo[n].count(k)) return memo[n][k];
    double p=(double)(n%(LL)M)/(double)M,q=1.0-p;
    return memo[n][k]=p*f(n-((n+M-1)/M), k-1) + q*f(n-n/M,k-1);
  }
  
  double findProbability(long long N, int M, int K) {
    this->M=M;
    double x= f(N,K);
    return x;
  }
};

/*
 
 memoized states in sample 4 n=10^12,m=2,k=40
 
 Testcase #4 ...
 n = 1000000000000, k = 40
 n = 500000000000, k = 39
 n = 250000000000, k = 38
 n = 125000000000, k = 37
 n = 62500000000, k = 36
 n = 31250000000, k = 35
 n = 15625000000, k = 34
 n = 7812500000, k = 33
 n = 3906250000, k = 32
 n = 1953125000, k = 31
 n = 976562500, k = 30
 n = 488281250, k = 29
 n = 244140625, k = 28
 n = 122070312, k = 27
 n = 61035156, k = 26
 n = 30517578, k = 25
 n = 15258789, k = 24
 n = 7629394, k = 23
 n = 3814697, k = 22
 n = 1907348, k = 21
 n = 953674, k = 20
 n = 476837, k = 19
 n = 238418, k = 18
 n = 119209, k = 17
 n = 59604, k = 16
 n = 29802, k = 15
 n = 14901, k = 14
 n = 7450, k = 13
 n = 3725, k = 12
 n = 1862, k = 11
 n = 931, k = 10
 n = 465, k = 9
 n = 232, k = 8
 n = 116, k = 7
 n = 58, k = 6
 n = 29, k = 5
 n = 14, k = 4
 n = 7, k = 3
 n = 3, k = 2
 n = 1, k = 1
 n = 2, k = 1
 n = 4, k = 2
 n = 15, k = 4
 n = 8, k = 3
 n = 233, k = 8
 n = 117, k = 7
 n = 59, k = 6
 n = 30, k = 5
 n = 466, k = 9
 n = 1863, k = 11
 n = 932, k = 10
 n = 7451, k = 13
 n = 3726, k = 12
 n = 59605, k = 16
 n = 29803, k = 15
 n = 14902, k = 14
 n = 238419, k = 18
 n = 119210, k = 17
 n = 1907349, k = 21
 n = 953675, k = 20
 n = 476838, k = 19
 n = 7629395, k = 23
 n = 3814698, k = 22
 n = 122070313, k = 27
 n = 61035157, k = 26
 n = 30517579, k = 25
 n = 15258790, k = 24
 
 */

// CUT begin
ifstream data("JanuszInTheCasino.sample");

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

bool do_test(long long n, int m, int k, double __expected) {
    time_t startClock = clock();
    JanuszInTheCasino *instance = new JanuszInTheCasino();
    double __result = instance->findProbability(n, m, k);
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
        long long n;
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
        int T = time(NULL) - 1505088252;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "JanuszInTheCasino (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
