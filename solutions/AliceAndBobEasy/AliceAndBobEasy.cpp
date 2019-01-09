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
 
 9/19/2018 SRM 737
 
 4:00-5:15 time is up
 
 9/20/2018
 
 https://www.topcoder.com/blog/single-round-match-737-editorials/
 http://hamko.hatenadiary.jp/entry/2018/09/19/222759
 https://twitter.com/HIR180/status/1042392269418950659
 https://twitter.com/kuuso1/status/1042436726411558912
 https://twitter.com/hamko_intel/status/1042437647937921024
 https://twitter.com/hamko_intel/status/1042393076046520320
 
 https://togetter.com/li/1268515
 
 I was confused about description "previous items" during the contest.
 Also I could not even estimate maximal number of moves. Very ashamed performance.
 
 16:30-18:00, 21:00-22:30 read editorials and add solution.
 
 If XOR{A}=0 in a Nim game, it's lose state. There is 0 win move.
 The first question is how many win moves can exist for one element?

 To make it simpler, define `all` = XOR{A}.
 (A[i]-x)^(all^A[i]) = 0, 0<x<A[i] should hold to make it lose state.
 <=> A[i]-x = all^A[i], 0<x<A[i]
 <=> 0 < x = A[i] - all^A[i] < A[i]
 
 Thus `x` can be dermined to one specific value. There exists at most one win move for one element.
 Now we figure out there are at most N win moves in size N heaps.
 
 Also we get A[i]>all^A[i] (from 0<A[i]-all^A[i])
 
 If we find A which satisfies A[i]>all^A[i] for all `i`, win move is maximal `N`.
 
 Suppose all = 1*****.
 If MSB of all is ON in all elements in A, all^A[i] removes the MSB. all^A[i]<A[i] is guaranteed.
 It's obviously possible if N is odd. XOR{A} = 1***** if A = {1*****,1*****,..}
 We can build with arbitrary ***** to keep them unique.
 
 If N is even, it's possible to achieve N win move? Suppose it's possible.
 
 all = 1*****
 Now we should have odd number of elements (=A1) with 1*****.
 A[i]^all<A[i] holds for A1.
 
 We also have 0***** for rest of elements (=A2).
 However MSB in `all` cannot be canceled by A[i]^all.
 Thus it contradicts that there exists N win moves.
 
 If we have minimal 0***** for A2, we can achieve N-1 win moves. It achieves all = 1*****.
 This should be optimal for even N.
 
 Summary:
  - I tried to show maximal number of win move. However I couldn't. Poor math taste.
  - I was trying to make array like { 1, 10, 100, 1000, 10000, 11111 } which is nonsense
   - If at most 1 win move, it's important to make sure we can cancel all the bits
   - However it was not proved during the contest
   - Look at unknown first to solve it. What is unknown? Figuring out maximal win move should be first unknown to be resolved.
  - Pay attention to MSB in binary representation. That makes major contribution to determine if subtraction gives positive or negative.
  - XOR => parity makes significant role
 
 */


class AliceAndBobEasy {
  public:
  
  int mcnt(VI A) {
    int N=SZ(A);
    int all=0; REP(i,N) all^=A[i];
    int res=0;
    REP(i,N) res+=((A[i]^all)<A[i]);
    return res;
  }
  
  vector<int> make(int N) {
    VI res;
    if(N%2==1) {
      REP(i,N) res.push_back((1<<10)+i+1);
      assert(mcnt(res)==N);
    } else {
      res.push_back(40);
      REP(i,N-1) res.push_back((1<<10)+i+1);
      assert(mcnt(res)==N-1);
    }
    return res;
  }
};

// CUT begin
ifstream data("AliceAndBobEasy.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(int N, vector<int> __expected) {
    time_t startClock = clock();
    AliceAndBobEasy *instance = new AliceAndBobEasy();
    vector<int> __result = instance->make(N);
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
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1537354846;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "AliceAndBobEasy (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
