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
typedef vector <int> VI;
typedef unordered_map <int,int> MAPII;
typedef unordered_set <int> SETI;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline bool SMIN(T &l,const T &r){return l<r?l=r,1:0;}
template<class T> inline bool SMAX(T &l,const T &r){return l>r?l=r,1:0;}
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
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 10/17/2018
 
 14:27-14:42 submit with rough proof and AC (200.89 pt)
 15:10 proof is done.
 
 a) A has even => YES
 b) A has only odd => YES if X+Y is even, NO otherwise
 
 After submission, I proved above.
 
 a) A is even
 
 Parity of walking cells can be either odd or even.
 We can make hypothesis that any cell is reachable.
 
 It's possible to figure out that (0,0)->(0,1) is possible:
 (0,0)->(2,1)->(1,3)->(0,1)
 
 With similar transition for `x`, (0,0)->(x-2,1) is reachable.
 If `x` is zero, we can reach arbitrary cell.
 If `x` is not zero, we can reach (2,1). Due to (0,0)->(2,1)->(0,1) path, we can reach arbitrary cells as well.
 
 b) A is odd
 
 If x is 3, we can reach (1,1) with below path:
 (0,0)->(-1,-3)->(-2,0)->(1,1)
 Thus arbitrary cell is reachable as long as x+y = even (Same color cell in a checkerboard)
 
 We can move to (2-x,1) for `x` step. That means that we can construct (3,1) move with (x,1) moves.
 
 http://apps.topcoder.com/wiki/display/tc/SRM+514
 
 Summary:
  - knight walk => math with modular arithmetic or parity
  - How to solve it?
   - Do you know similar problem? Yes, knight walk is math problem
   - Can we decompose problem and recombine? Yes, parity is the key
   - Can you prove your hypothesis? Yes
   - Look at special case as an auxiliary problem. We can reduce arbitrary moves to special cases (1,2) or (1,3)
 
 */
const string yes="YES",no="NO";
class MagicalGirlLevelOneDivOne {
  public:
  string isReachable(vector<int> A, int X, int Y) {
    int P[2]={0};
    int N=SZ(A);
    REP(i,N) P[A[i]&1]++;
    if(P[0]) return yes;
    return ((X+Y)&1)==0?yes:no;
  }
};

// CUT begin
ifstream data("MagicalGirlLevelOneDivOne.sample");

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

bool do_test(vector<int> jumpTypes, int x, int y, string __expected) {
    time_t startClock = clock();
    MagicalGirlLevelOneDivOne *instance = new MagicalGirlLevelOneDivOne();
    string __result = instance->isReachable(jumpTypes, x, y);
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
        vector<int> jumpTypes;
        from_stream(jumpTypes);
        int x;
        from_stream(x);
        int y;
        from_stream(y);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(jumpTypes, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539811643;
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
        cout << "MagicalGirlLevelOneDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
