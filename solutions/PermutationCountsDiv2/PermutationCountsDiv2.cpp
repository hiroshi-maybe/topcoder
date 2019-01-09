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
 
 8/31/2017
 
 16:30-17:42 give up
 
 17:43-18:30 read editorials
  - https://apps.topcoder.com/wiki/display/tc/SRM+656
  - http://topcoder.g.hatena.ne.jp/yambe2002/20160206/1454729150
  - http://kyoupuro8thnote.blogspot.com/2015/05/topcoder-srm656-permutationcountsdiv2.html
  - http://kmjp.hatenablog.jp/entry/2015/04/20/1000
 
 18:30-19:00 add solution
 
 f(l,r) = ∑ { C(r-l-1,i-l)*f(l,i)*f(i+1,r) :  i = bottom of a valley in [l,r) <=> (i∈P||i=r-1)&&(i=l||i-1∉P) }
 f(x,x)=f(x,x+1)=1
 
 Key:
  - if we observe up and down of numbers, smallest number shows up only at i∈pos or right most position
  - insertion dp from 1 to N
   - note that if i and i+1 (i,i+1∈pos) are in current interval, we take only i because p(i)<p(i+1)
   - once smallest value is inserted, problem is divided into two subproblems (left interval and right interval)
    - we can choose i-l out of r-l-1 for left interval. rest of elements go to right interval.
      - left interval does not affect right interval. they can be solved independently
    - we don't need to remember what is used or what is not used out of 1..N
      - we always pick up just smallest number in current set first. actual value doesn't matter.
      - that's why we can just choose i-l out of r-l-1
 
 Summary:
  - I could not solve insertion DP problem again 💢
   - SRM 694 div2 hard UpDownNess
   - http://kmjp.hatenablog.jp/entry/2016/07/16/1100
  - if there is a rule of order of permutation of distinct N numbers, insertion DP may help
 
 Other solutions:
  - no precomputation of combinations
    - https://community.topcoder.com/stat?c=problem_solution&rm=326034&rd=16416&pm=13739&cr=23330633
    - https://community.topcoder.com/stat?c=problem_solution&rm=326010&rd=16416&pm=13739&cr=40118296
    - https://community.topcoder.com/stat?c=problem_solution&rm=326021&rd=16416&pm=13739&cr=40122674
 
 */

constexpr int MOD = 1e9+7;
LL memo[201][201];
LL C[201][201];
class PermutationCountsDiv2 {
  public:
  VI P;
  int N;
  LL f(int l, int r) {
    if(r-l<=1) return 1;
    if(memo[l][r]>=0) return memo[l][r];
    LL &res=memo[l][r];
    res=0;
    FOR(i,l,r) {
      if((i==r-1||P[i]) && (i==l||!P[i-1])) {
        LL x=C[r-l-1][i-l];
        x*=f(l,i),x%=MOD;
        x*=f(i+1,r),x%=MOD;
        res+=x, res%=MOD;
      }
    }
    return res;
  }
  
  int countPermutations(int N, vector<int> pos) {
    this->N=N;
    ZERO(C);
    REP(i,N+1) {
      C[i][0]=1;
      FOR(j,1,i+1) C[i][j]=C[i-1][j]+C[i-1][j-1],C[i][j]%=MOD;
    }
    MINUS(memo);
    
    P=VI(N);
    REP(i,SZ(pos)) P[pos[i]-1]=true;
    return f(0,N);
  }
};

// CUT begin
ifstream data("PermutationCountsDiv2.sample");

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

bool do_test(int N, vector<int> pos, int __expected) {
    time_t startClock = clock();
    PermutationCountsDiv2 *instance = new PermutationCountsDiv2();
    int __result = instance->countPermutations(N, pos);
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
        vector<int> pos;
        from_stream(pos);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, pos, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504222072;
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
        cout << "PermutationCountsDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
