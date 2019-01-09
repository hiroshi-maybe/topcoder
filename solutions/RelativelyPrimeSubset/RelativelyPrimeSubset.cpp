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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/26/2018
 
 8:56-9:40 analysis
 9:41-10:06 implemented, but 2^25 integer does not fit in 64MB memory :(
 10:30-10:40 Take a look at editorial. No need to look at primes over 53
 10:41-10:51 implement and submit. However 1WA due to corner case `1`
 10:52-10:56 Bug fix. System test passed.
 
 Set packing: https://en.wikipedia.org/wiki/Set_packing
 
 Some people are solving maxclique problem 🤔
  - https://community.topcoder.com/stat?c=problem_solution&rm=313545&rd=14739&pm=12074&cr=23067703
  - https://community.topcoder.com/stat?c=problem_solution&rm=313522&rd=14739&pm=12074&cr=23078632
 
 Reduction to graph problem max clique is another way.
 If we make an edge between numbers which are co-prime each other, problem is reduced to max clique problem. 
 
 Key:
  - Problem is reduced to maximum set packing which is NP-hard
    - https://cs.stackexchange.com/questions/48298/algorithm-for-finding-maximum-mutually-coprime-subset-of-a-multiset-of-integers
  - If S[i] has prime which is larger than 50, it's guaranteed that it's co-prime with any other number
    - No need to compute those numbers
    - Number of interesting prime is in [2,47] (15 primes)
    - 2^15 bit DP
  - 1 is always co-prime with other number
 
 Summary:
  - Basic idea was right. However I couldn't reduce memory from 2^25 to 2^15 👎
  - Given constraint may not directly upper-bound runtime or memory
  - If runtime or memory does not fit a bit, try problem-specific optimization
 
 */
VI PS={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int dp[1<<15];
class RelativelyPrimeSubset {
  public:
  int findSize(vector<int> SS) {
    int N=SZ(SS);
    ZERO(dp);
    VI S(N,0);
    int B=0;
    REP(i,N) REP(j,SZ(PS)) if(SS[i]%PS[j]==0) {
      if(PS[j]<50) S[i]|=1<<j;
    }
    REP(i,N) B+=S[i]==0;
    
    int res=0;
    REP(i,N) if(S[i]!=0) {
      REP(mask,1<<15) if((S[i]&mask)==0) {
        MAXS(dp[mask|S[i]], dp[mask]+1);
        res=max(res,dp[mask|S[i]]);
      }
    }
//    dump2(res,B);
    return res+B;
  }
};

// CUT begin
ifstream data("RelativelyPrimeSubset.sample");

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

bool do_test(vector<int> S, int __expected) {
    time_t startClock = clock();
    RelativelyPrimeSubset *instance = new RelativelyPrimeSubset();
    int __result = instance->findSize(S);
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
        vector<int> S;
        from_stream(S);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1516985768;
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
        cout << "RelativelyPrimeSubset (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
