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
 
 12/20/2017
 
 9:28-10:00 pause
 11:30-12:00 time up
 
 We can iterate from top to bottom and figure out X tops are required.
 Then we want to count distinct sequence with X mandatory elements and N-X optional elements.
 I tried to pin X elements first and put N elements in N-X positions though, I couldn't resolve duplicated count.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+567
  - http://kmjp.hatenablog.jp/entry/2013/01/26/0900
  - http://ekaing.hatenablog.com/entry/2013/03/31/221005
 
 12/21/2017
 
 18:00-18:27 took a look at editorial and analyze from state by myself
 18:28-18:44 add solution (1WA due to small size of memo for `Y`)
 
 We want to differentiate X (must be used at least once) from Y (optional to be used).
 One observation is that, once X is used, Y increases by one.
 If we add another state `i` for current index, state transition is DAG.

 f(i,X,Y) = X*f(i+1,X-1,Y+1) + Y*f(i+1,X,Y)
            ^                  ^
            X options to use   Y options to use
 
 f(_,-1,_) = 0
 f(N,X,_) = X==0

 O(N*R*C) time <= 50^3 ≈ 2*10^5
 X+Y = number of 'X'
 Possible state of (X,Y) is upper-bounded by R*C as shown in official editorial.
 
 Key:
  - There are two numbers X and Y that we want to differentiate
  - It's possible to build recurrence relation by them
 
 Summary:
  - Incredibly smart state definition to count!
 
 */
constexpr int MOD = 1e9+9;
LL memo[51][2501][51];
class MountainsEasy {
  public:
  int N;
  LL f(int i, int X, int Y) {
    if(X<0) return 0;
    LL &res=memo[i][X][Y];
    if(res>=0) return res;
    if(i==N) return res=(X==0);
    LL x=X*f(i+1,X-1,Y+1)%MOD,y=Y*f(i+1,X,Y)%MOD;
    return res=(x+y)%MOD;
  }
  int countPlacements(vector<string> G, int N) {
    this->N=N;
    MINUS(memo);
    int R=SZ(G),C=SZ(G[0]);
    int X=0,Y=0;
    REP(i,R) REP(j,C) if(G[i][j]=='X') {
      ++X,G[i][j]='.';
      FOR(ii,i+1,R) {
        int d=ii-i;
        for(int jj=max(j-d,0); jj<=min(j+d,C-1); ++jj) if(G[ii][jj]=='X') ++Y,G[ii][jj]='.';
      }
    }
    
//    dump3(X,Y,N);
    return f(0,X,Y);
  }
};

// CUT begin
ifstream data("MountainsEasy.sample");

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

bool do_test(vector<string> picture, int N, int __expected) {
    time_t startClock = clock();
    MountainsEasy *instance = new MountainsEasy();
    int __result = instance->countPlacements(picture, N);
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
        vector<string> picture;
        from_stream(picture);
        int N;
        from_stream(N);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(picture, N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513790879;
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
        cout << "MountainsEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
