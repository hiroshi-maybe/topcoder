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

constexpr int MOD = 1e9+7;

/*
 
 9/1/2017
 
 9:24-10:00 it took 36 mins to understand the problem statement. poooooor English reading.
 10:00-10:25, 18:40-19:15 time up
 
 19:15-19:37 read editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+655
  - http://mayokoex.hatenablog.com/entry/2015/04/11/152105
  - http://kmjp.hatenablog.jp/entry/2015/04/10/1000

 dp[0][0][0][0][0][0]=1
 dp[i+1][(a+n0)%9][(b+n1)%9][(c+n2)%9][(d+n3)%9][(e+n4)%9]+=dp[i][a][b][c][d][e]
  if(N>0&&D[i][0]==1) n0=n else 0
  if(N>1&&D[i][1]==1) n1=n else 0
  if(N>2&&D[i][2]==1) n2=n else 0
  if(N>3&&D[i][3]==1) n3=n else 0
  if(N>4&&D[i][4]==1) n4=n else 0
 n=0..9
 
 res=dp[M][0][0][0][0][0]
 
 19:38-19:50 add solution

 Key:
  - 10 ≡ 1 (mod 9)
   - 4671 ≡ (4*1000 + 6*100 + 7*10 + 1) ≡ 4*1 + 6*1 + 7*1 + 1*1 ≡ 4 + 6 + 7 + 1 ≡ 18 ≡ 0 (mod 9)
   - D ≡ ∑ d[i] (mod 9)
   - check if sum of digit (mod 9) = 0
  - column DP
   - if ∑ { d[i][j] : column i=0..<M and question j=0..<N } %9 = 0, 9|D[j]
   - if digits at each i is given, sum of digits for each question j can be determined
   - we can brute-force all the digits at i for question j
   - if we remember d[i][j]%9, we know d[i+1][j] for each n=0..9
  - N<5 => N is so small. we can leverage N dimension DP table
 
 Summary:
  - figured out to get D ≡ ∑ d[i] (mod 9) though, I had no idea to remember states
   - actually tried to use bitmask of each question though, no idea to make state transition
   - result of each question is independent (there is NO dependency between them). OBVIOUSLY THIS IS BAD IDEA.
  - transition from left to right, variable dimension based on small N was key
  - count from left to right is popular pattern. DO NOT SKIP THE IDEA.
  - in this problem, there seem to be only two dimensions, left-to-right or top-to-bottom
   - if top-to-bottom does not work, try left-to-right different dimension
 
   i = | 0 -> 1 -> 2  (left to right)
   d = | 1    3    2
 ----------------------
 j = 0 | 1    1    0  ^
 j = 1 | 0    1    1  |
 (N=2)                (bottom to top)
 
 */

LL dp[21][10][10][10][10][10];
class NineEasy {
  public:
  int count(int N, vector<int> D) {
    int M=SZ(D);
    ZERO(dp);
    dp[0][0][0][0][0][0]=1;
    REP(i,M) REP(a,10) REP(b,10) REP(c,10) REP(d,10) REP(e,10) if(dp[i][a][b][c][d][e]) {
      int a2=a,b2=b,c2=c,d2=d,e2=e;
      REP(n,10) {
        if(N>0&&(D[i]&(1<<0))) a2=(a+n)%9;
        if(N>1&&(D[i]&(1<<1))) b2=(b+n)%9;
        if(N>2&&(D[i]&(1<<2))) c2=(c+n)%9;
        if(N>3&&(D[i]&(1<<3))) d2=(d+n)%9;
        if(N>4&&(D[i]&(1<<4))) e2=(e+n)%9;
        
        (dp[i+1][a2][b2][c2][d2][e2] += dp[i][a][b][c][d][e])%=MOD;
      }
    }
    return dp[M][0][0][0][0][0];
  }
};

// CUT begin
ifstream data("NineEasy.sample");

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

bool do_test(int N, vector<int> d, int __expected) {
    time_t startClock = clock();
    NineEasy *instance = new NineEasy();
    int __result = instance->count(N, d);
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
        int N;
        from_stream(N);
        vector<int> d;
        from_stream(d);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504283064;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "NineEasy (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
