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

int dp[101][101][101];

// 1167(ms)->175(ms) for 100,100,100,1
// locally 30(ms) though
class CheeseSlicing {
public:
  int totalArea(int A, int B, int C, int S) {
    memset(dp, -1, sizeof(dp));
    return dfs(A,B,C, S);
  }
  
  int dfs(int a, int b, int c, int S) {
    if (a>b) swap(a,b);
    if (a>c) swap(a,c);
    if (b>c) swap(b,c);
    if (a<S) return 0;
    if (a==S) return b*c;
    if (dp[a][b][c]!=-1) return dp[a][b][c];
    
    int res=b*c;

    /* test cases pass without those commented out code. However I don't have proof of it.
    for(int o=S; a-o>=S; ++o) {
      res = max(res, dfs(o,b,c,S)+dfs(a-o,b,c,S));
    }
    for(int o=S; b-o>=S; ++o) {
      res = max(res, dfs(a,o,c,S)+dfs(a,b-o,c,S));
      }*/
    for(int o=S; c-o>=S; ++o) {
      res = max(res, dfs(a,b,o,S)+dfs(a,b,c-o,S));
    }
    
    return dp[a][b][c] = res;
  }
};

int p[3];
// TLE for 100,100,100,1
// 1.53(sec) locally though
// Found two bottle necks
// - a,b,c shouldn't be passed by vector
// - vector shouldn't be copied to ns1 and ns2
// (otherwise the test case passes 1.167(s))
class CheeseSlicing_TLE {
  public:
  int totalArea(int A, int B, int C, int S) {
    memset(dp, -1, sizeof(dp));
    VI ns={A,B,C};
    return dfs(ns, S);
  }
  
  int dfs(VI &ns /* bottle neck 1 */, int S) {
    sort(ns.begin(),ns.end());
    if (ns[0]<S) return 0;
    if (ns[0]==S) return ns[1]*ns[2];
    if (dp[ns[0]][ns[1]][ns[2]]!=-1) return dp[ns[0]][ns[1]][ns[2]];
    
    int res=ns[1]*ns[2];
    int i=2;
//    REP(i,3) {
      for(int o=S; ns[i]-o>=S; ++o) {
	VI ns1=ns, ns2=ns; // bottle neck 2
        ns1[i]=o; ns2[i]=ns[i]-o;
	res=max(res,dfs(ns1,S)+dfs(ns2,S));
      }
//    }
    
    return dp[ns[0]][ns[1]][ns[2]] = res;
  }
};

// CUT begin
ifstream data("CheeseSlicing.sample");

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

bool do_test(int A, int B, int C, int S, int __expected) {
    time_t startClock = clock();
    CheeseSlicing *instance = new CheeseSlicing();
    int __result = instance->totalArea(A, B, C, S);
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        int C;
        from_stream(C);
        int S;
        from_stream(S);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, C, S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1491063501;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CheeseSlicing (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
