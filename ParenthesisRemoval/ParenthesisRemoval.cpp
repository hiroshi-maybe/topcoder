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
using namespace std;

// type alias
typedef unsigned long UL;
typedef long long LL;

typedef vector < bool > VB;
typedef vector < int > VI;
typedef vector < string > VS;
typedef vector < vector < int > > VVI;
typedef unordered_map < int, int > MAPII;
typedef unordered_map < string, int > MAPSI;
typedef unordered_set < int > SETI;
typedef unordered_set < string > SETS;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

// vector
#define PUSH(s, e) (s).push_back(e)
#define POP(s) (s).pop_back()
#define REVERSE(c) reverse((c).begin(),(c).end())
#define SORT(c) sort((c).begin(),(c).end())
#define CONCAT(a,b) (a).insert((a).begin(), (b).begin(),(b).end())
#define ERASE(arr,i) (arr).erase((arr).begin()+i)

// pair/tuple
typedef pair< int , int > II;
typedef vector<II> VII;
#define MP make_pair
#define _1 first
#define _2 second
typedef tuple< int , int, int > III;
#define MT make_tuple

// matrix
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };

// priority queue
#define MAX_PQ(T) priority_queue<T>
#define MIN_PQ(T) priority_queue<T,vector<T>,greater<T>>

// binary search
#define LB(a,n,k) lower_bound(a,a+(n),(k))
#define UB(a,n,k) upper_bound(a,a+(n),(k))

// dp
#define DP(dp,i,j) int dp[i][j]
#define FILL(dp,x) memset(dp, x, sizeof(dp))
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

constexpr LL MOD = 1e9+7;

// 8:15-8:28 passed all the samples
// failed system test for "()()()()()()(()())(())(()())(()())(()())(()(()))(()()()(()))(()()()(()()()()(()())))(()(())()()()(())()(()(()())(())))(()()()()()(()())(()())((())())((()())(()(())())))(()()(())()(()()()))((())()()()(()()()()(()()))(()()()()()()(()()(())(()()())))(()()(()()())(()()(())(()))))(()()(())()()()()(()())(()())(()()())(()())(())(()(())()(()(()))(()()()))(()()()()()())(()()()(())()())(()())(()()()())(()()()(())(()(()())))(()()()()()()(())((())(()())()))(()(())(()())(()())(()()()()()))(()()()(())(())))((())((())())()(()()()()())(()(()()())(()()))(()()())(())(()()(())(())(()()()(())))(()()()()(()(()(()))))(()()()()(()(()()()))(()()))(()()()(()))(()(())()()(()()())(()()()()()(()())(()(()))))(()()(())(())(())))(()(()(()))((())()(()(())(()))(()()))(()()(())(()()())(()()())()(()))(()()()()()()(()()()())(()()(()())())(()()()(()())(()()())())(()())(()()()(())()()(()()()()(()))(()()(()()()))(()()())((())(()((())())))))(()()(())(())))(()()(())(())(()())(())((()))(()()(()()()())(()(())(())))(()()()()(())(()())(()()())((()()))((()())(())(()()()())))(()()()(())((()()))(())(()())())(()()(())(()()())(())(())(())(()(()()))(()()(())(())(())(()()(()))(()(()()()())())(()()()(()(())())))(()()()((()))(())(()()()()(()))(()(()))((()()))(()()()()(()())()(()()))(()(()()()()(()))))))(()()()(())(()(()))(()()()(()())()(()(()())))(()()()(())(()())(()()())(()(()()))(()())(()()())(()()()())(()()(()())(())(()()(()))))(()()(())(()())(()()()(()))(()()()()())(()()()())((())))(()()(()())(()()(()))(()(())))(()()()(()())(())()(()()()()())(()()()()(())(()()()(())))(()()(()()())((()))()(()()()(())(()))))(()()(())(())(())(()())(()()()(()))(()()(()))(())(()(())())()(()()()(())))(()()()()()(())()(()()())(()()(()))()(())((()))(()()()(()())())(())(()()(())(()()())(()(())()()()(()))))(()(())(()())(())(())(()(()))(()()()()())(()(())(()()))(()()()()(())(()())))(()()()(())(())(())(()())(()()()()()())(()()()()(()())(()()()))(()())(()()()()()(()())()(()()))(()(()))(()()(()(()))(()())(()()))(()()()(())(())(()))))(()(())()()()((()))(()()(())(()))()((()))(()()(())(()))(()()(()()())())(()()()()()()()()(()(()))()(())()(()()(()()))(()(()))(()(())()(()))(()()(())()(()))((())))(()()()(())(())(())()()(()())(()())(()(()())(()()((()))()())))((())()()()(()()()()(()()))(()()()(()))(()()()(())(()())(()))(()()())))" (TLE 10(s))

class ParenthesisRemoval {
  public:
  MAPSI memo;
  int countWays(string s) {
    int N=SZ(s), d=0;
    if (s=="") return 1;
    if (memo.count(s)) return memo[s];
    
    LL res = 0;
    REP(i,N) {
      if (s[i]=='(') {
        ++d; continue;
      }
      --d;
      
      string t = s.substr(1,i-1) + s.substr(i+1);
      res += (LL)countWays(t);
      res %= MOD;
      
      if (d==0) break;
    }
    
    return memo[s] = (int)res;
  }
};

// CUT begin
ifstream data("ParenthesisRemoval.sample");

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

bool do_test(string s, int __expected) {
    time_t startClock = clock();
    ParenthesisRemoval *instance = new ParenthesisRemoval();
    int __result = instance->countWays(s);
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
        string s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498749298;
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
        cout << "ParenthesisRemoval (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
