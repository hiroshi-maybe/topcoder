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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

// mod
constexpr int MOD = 1e9+7;

/**
 
 7/13/2017
 
 8:50-9:32 time up
 
 20:30 read solutions and editorials
 - http://kmjp.hatenablog.jp/entry/2016/10/26/0930
 - http://codeforces.com/blog/entry/47675
 - https://www.quora.com/What-is-the-approach-to-solve-Topcoder-SRM-700-Div2-Hard-problem
 - http://yu3mars.hatenablog.com/entry/2016/10/14/190000
 - https://apps.topcoder.com/wiki/display/tc/SRM+700
 
 Ok, I was thinking rooms are fixed. rankings are delivered.
 However, iterating rankings 1 by 1. Rooms can be ordered in R! way.
 This is easier approach. If I figured out room order can be permutated, I should have come up with this approach.
 We are interested in rank of winners. We can think of two cases.
  i)  rank is assigned to winner
  ii) rank is assigned to others
 Key point is to understand limitation of winner assignment.
 
 21:41 start coding
 22:40 couldn't find bug. copied existing solution.
 23:00 resumed original design
 23:30 passed
  - It took a lot of time to find bug to cut room assignment by `rank<=room*S`
  - confused by relationship between current rank and remaining slot
 */

LL memo[10005][105];
LL R,S;

class XYZCoder {
public:
  int x=0;
  int dfs(int rank, int room) {
    if(room>R) return 0;
    if(memo[rank][room]>=0) return memo[rank][room];
    if(rank==R*S) return memo[rank][room]=(room==R);
    LL res=0;
    res+=dfs(rank+1,room), res%=MOD;
    if(rank<=room*S) res+=dfs(rank+1,room+1), res%=MOD;
    return memo[rank][room]=res;
  }
  
  int countWays(int room, int size) {
    R=room, S=size;
    memset(memo,-1,sizeof memo);
    LL res = dfs(0,0);
    FOR(n,1,R+1) res*=n, res%=MOD;
    return res;
  }
};

class XYZCoder_wrong {
  public:
  int dfs(int i, int rank) {
    if(i==R) return 1;
    if(rank==R*S) return 0;
    if(memo[rank][i]>=0) return memo[rank][i];
    LL res=0;
    if(i<R&&rank<=(R-i)*S-1) res += dfs(i+1,rank+1), res%=MOD;
    res += dfs(i, rank+1), res%=MOD;
    
    return memo[rank][i]=res;
  }
  
  int countWays(int room, int size) {
    R=room, S=size;
    memset(memo,-1,sizeof memo);
    LL res = dfs(0,0);
    FOR(n,1,R) res*=n, res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("XYZCoder.sample");

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

bool do_test(int room, int size, int __expected) {
    time_t startClock = clock();
    XYZCoder *instance = new XYZCoder();
    int __result = instance->countWays(room, size);
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
        int room;
        from_stream(room);
        int size;
        from_stream(size);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(room, size, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499960998;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "XYZCoder (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
