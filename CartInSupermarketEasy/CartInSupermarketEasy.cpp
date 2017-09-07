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
 
 9/6/2017
 
 8:47-9:22 (255.82 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+649
  - http://kmjp.hatenablog.jp/entry/2015/02/13/1030
 
 recurrence relation in DP:
 
 f(n,k) = min { 1+f(n-1,k) } ∪ { 1+max(f(i,j),f(n-i,k-j) : i=1..n, j=0..i }
 f(0,_) = 0
 
 analysis of greedy solution:
  
 if we split carts, we can reduce them in parallel. thus we should split as early as possible.
 by this approach, split carts form binary tree.
 Suppose we want to split into x chunks of carts. Then it would have ceil(lg x) height of binary tree.
 define y = ceil(lg x). at height y-1, 2^(y-1) nodes exists as child of perfect binary tree.
 some of nodes are split out of 2^(y-1) nodes again. suppose p nodes are NOT split.
 then at y-th turn, p nodes are reduced by 1. 2^(y-1)-p nodes are split and creates 2*(2^(y-1)-p) nodes
 sum of them should be x.
 x = 2*(2^(y-1)-p) + p <=> p = 2^y-x
 
 at y turn, number of remaining cart is N-p. we'll reduce them in parallel by x by one turn
 
 necessary turn is y + ceil((N-p)/x) = y + 1 + ceil((N-2^y)/x)
 
 since x-1 split makes x chunks of carts, we can iterate x = 1..K+1
 res = min { y + 1 + ceil((N-2^y)/x) : x = 1..K+1 }
 
 key:
  - simple DP suffices to solve the sizes
  - greedy solution is used to solve div1 hard
    - analysis of greedy approach
    - accurate computation of nodes of binary search and split carts
 
 summary:
  - solved by DP guessing that there is a greedy solution...
  - wasted time to find a bug of f(i,j)+f(n-i,k-j) instead of max(f(i,j),f(n-i,k-j)) 👎
  - anyway solved by myself 👍
 
 everyone is solving by DP
  - https://community.topcoder.com/stat?c=problem_solution&rm=325152&rd=16313&pm=13659&cr=22931169
  - https://community.topcoder.com/stat?c=problem_solution&rm=325149&rd=16313&pm=13659&cr=22835034
  - https://community.topcoder.com/stat?c=problem_solution&rm=325161&rd=16313&pm=13659&cr=23137570
  - https://community.topcoder.com/stat?c=problem_solution&rm=325142&rd=16313&pm=13659&cr=40043950
 
*/

class CartInSupermarketEasy {
public:
  int calc(int N, int K) {
    int res=N;
    FOR(x,1,K+2) {
      int y=0;
      while((1<<y)<=x) ++y;
      if(x>N) continue;
      
      res=min(res, y + 1 + (N-(1<<y)+x-1)/x);
    }
    return res;
  }
};

int memo[101][101];
class CartInSupermarketEasy_dp {
  public:
  int f(int n, int k) {
    if(n==0) return 0;
    if(memo[n][k]>=0) return memo[n][k];
    
    int &res=memo[n][k];
    res=1+f(n-1,k);
    --k;
    FOR(i,1,n) REP(j,i+1) if(j<=k) {
      res=min(res,1+max(f(i,j),f(n-i,k-j)));
    }
    return res;
  }
  int calc(int N, int K) {
    MINUS(memo);
    return f(N,min(N,K));
  }
};

// CUT begin
ifstream data("CartInSupermarketEasy.sample");

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

bool do_test(int N, int K, int __expected) {
    time_t startClock = clock();
    CartInSupermarketEasy *instance = new CartInSupermarketEasy();
    int __result = instance->calc(N, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504712835;
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
        cout << "CartInSupermarketEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
