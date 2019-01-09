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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('\n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

/*
 
 11/8/2018
 
 12:21-13:50 give up
 
 14:23 got AC after reading editorial.
 
 http://apps.topcoder.com/wiki/display/tc/SRM+544

 Key:
  - Estimate of upper bound of total votes 200 ✅
   - larger `sum` covers larger range. It should be large enough to find integer vote
  - Accumulating lower bound and upper bound and compare with total votes ✅
  - Computation of lower bound ✅
  - Computation of upper bound ❌
 
 Accumulation of exclusive upper-bound gives larger upper-bound than expected value as seen in sample #2
 When we accumulate ranges, inclusive bound should be used.
 @sugim48's solution is close to mine.
 
 Summary:
  - I needed to resolve some of blockers
   - Restored # of votes should be integer
   - Translating range of real number to integer number
   - Estimate of maximum possible total votes.
  - Technique of aggregation of range is nice to know
  - Don't be worried about range of real number. It can be translated to integer by floor/ceil.
 
 */

class ElectionFraudDiv1 {
public:
  VI A;
  bool ok(int sum) {
    int N=SZ(A);
    int l=0,r=0;
    REP(i,N) {
      int lb=((2*A[i]-1)*sum+199)/200,ub=((2*A[i]+1)*sum+199)/200-1;
//      if(sum==3)dump4(sum,i,lb,ub);
      if(ub-lb<0) return false;
      l+=lb,r+=ub;
    }
    return l<=sum&&sum<=r;
//    return dp[sum];
  }
  int MinimumVoters(vector<int> A) {
    this->A=A;
    REPE(x,300) {
      if(ok(x)) return x;
    }
    return -1;
  }
};

class ElectionFraudDiv1_wrong {
  public:
  VI A;
  bool ok(LL sum) {
    LL lb=0,ub=0;
    int N=SZ(A);
    REP(i,N) {
      lb+=(2LL*A[i]-1)*sum,ub+=(2LL*A[i]+1)*sum;
    }
    bool res=lb<=200LL*sum&&200LL*sum<ub;
//    dump4(sum,lb,200*sum,ub);
//    dump2(sum,res);
    return res;
  }
  int MinimumVoters(vector<int> A) {
    this->A=A;
    const LL Inf=1e10;
    LL good=Inf,bad=-1;
    while(abs(good-bad)>1) {
  //    dump2(good,bad);
      LL m=(good+bad)/2;
      (ok(m)?good:bad)=m;
    }
    if(good<0||!ok(good)) return -1;
    return good;
  }
};

// CUT begin
ifstream data("ElectionFraudDiv1.sample");

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

bool do_test(vector<int> percentages, int __expected) {
    time_t startClock = clock();
    ElectionFraudDiv1 *instance = new ElectionFraudDiv1();
    int __result = instance->MinimumVoters(percentages);
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
        vector<int> percentages;
        from_stream(percentages);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(percentages, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541708471;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 275 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ElectionFraudDiv1 (275 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
