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
 
 2/6/2018
 
 9:31-10:05 analysis
 10:15 submit (424.01 pt) but 1WA (returning 0 wheneve cycle exists 👎)
 10:20 bug fix and ACC
 
 Probability space can be defined as below:
 
 Ω = { permutation of {0..N-1} }
 𝐹 = power set of I { knowledge of book `i` is gained }
 
 If random variable X is defined as number of gained knowledge, it equals to sum of indicator randome variables.
 
 X = ∑ { X_i }
 
   X_i
 = I { gains knowledge of book i }
 = 1 if knowledge of book i is gained
   0 otherwise
 
   E[X]
 = E[∑{X_i}]
 = ∑ E[X_i] // linearity of expectation
 = ∑ Pr{ knowledge of book i is gained }
 
 If `p` books must show up in order to gain knowledge of book `i`, probability is shown as blow.
 
   Pr { knowledge of book i is gained }
 = C(n,p)*(N-p)!/N!
 = 1/p!
 
 Another way to compute probability:
 
 Suppose event to choose j-th book is shown as E[j].
   Pr{E[p] ∩ E[p-1] ∩..∩ E[1]}
 = Pr{E[1]}*Pr{E[2]|E[1]}*Pr{E[3]|E[2] ∩ E[1]}*..*Pr{E[p]|E[p-1] ∩..∩ E[1]}
 = ∏ { 1/(p-k) : k=0..p-1 }
 = 1/p!
 
 Reference: CLRS 5.3 Randomized algorithms, Exercise C.2-5
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+537
  - http://kmjp.hatenablog.jp/entry/2014/01/05/1030
  - http://area.hateblo.jp/entry/2013/10/17/035720
 
 Key:
  - By linearity of expectation, we can sum probability to get knowledge of each book
  - Prequisite books can be found by dfs
 
 Summary:
  - Finally I solved with linearity of expectation by myself 👍
  - It took a lot of time to build formula of probability calculation. I need more training.
 
 */
class PrinceXToastbook {
  public:
  double pr(double p) {
    double res=1.0;
    FORE(k,1,p) res/=1.0*k;
    return res;
  }
  double eat(vector<int> P) {
    int N=SZ(P);
    double res=0;
    REP(i,N) {
      int j=i,p=1;
      while(P[j]!=-1&&p<=N) j=P[j],++p;
      if(p>=N+1) continue;
      res+=pr(p);
    }
    return res;
  }
};

// CUT begin
ifstream data("PrinceXToastbook.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> prerequisite, double __expected) {
    time_t startClock = clock();
    PrinceXToastbook *instance = new PrinceXToastbook();
    double __result = instance->eat(prerequisite);
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
        vector<int> prerequisite;
        from_stream(prerequisite);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(prerequisite, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517938275;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 925 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PrinceXToastbook (925 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
