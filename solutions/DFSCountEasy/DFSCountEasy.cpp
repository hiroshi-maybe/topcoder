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

/*
 6/30/2017
 
 22:54 start
 23:42 I see. current position matters
 23:49 crap, edge is WRONG!!!! LOL
 23:52 fix memoization too and passed samples
 23:53 Wrong for {{"NYYNYYYN", "YNNNYYNY", "YNNYNNNN", "NNYNYYYN", "YYNYNYNN", "YYNYYNYY", "YNNYNYNN", "NYNNNYNN"}} in system test :(
 24:10 time up
 
 7/1/2017
 
 8:45 retry
 8:47 figured out small misunderstanding of the problem
 8:59 read https://www.topcoder.com/blog/single-round-match-713-editorials/
 9:58 passed system test
 */
LL fact(LL n) {
  LL res=1;
  FOR(m,1,n+1) res*=m;
  return res;
}

class DFSCountEasy {
  public:
  vector<unordered_map<int, LL>> memo;
  unordered_map<int, SETI> E;
  int N;
  int done;
  long long count(vector<string> G) {
    N = SZ(G); done = (1<<N)-1;
    memo = vector<unordered_map<int, LL>>(N, unordered_map<int, LL>());
    
    if (N==1) return 1;
    LL res = 0;
    REP(i,N) {
      REP(j,N) {
        if (G[i][j]=='Y') E[i].insert(j);
      }
    }
    
    REP(i,N) {
      res += dfs(done, i);
    }
    
    return res;
  }
  
  // mask == available nodes
  LL dfs(int mask, int cur) {
    mask = mask & (~(1<<cur));
    if (memo[cur].count(mask)) return memo[cur][mask];
    
    unordered_map<int, LL> comps;
    REP(start, N) {
      if (canVisit(mask, start) && E[cur].count(start)) {
        int compmask = 1<<start;
        queue<int> Q; Q.push(start);
        while(Q.size()) {
          int u = Q.front(); Q.pop();
          REP(v,N) {
            if (!canVisit(mask,v)) continue;
            if (!E[u].count(v)) continue;
            if (compmask&(1<<v)) continue;
            
            Q.push(v);
            compmask |= (1<<v);
          }
        }
        
        comps[compmask] += dfs(compmask, start);
      }
    }
    
    LL res = 1;
    for(auto &kvp : comps) res*=kvp.second;
    res *= fact((LL)comps.size());
    
    return memo[cur][mask] = res;
  }
          
  bool canVisit(int mask, int p) {
    return (mask&(1<<p))!=0;
  }
};

// CUT begin
ifstream data("DFSCountEasy.sample");

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

bool do_test(vector<string> G, long long __expected) {
    time_t startClock = clock();
    DFSCountEasy *instance = new DFSCountEasy();
    long long __result = instance->count(G);
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
        vector<string> G;
        from_stream(G);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(G, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498888417;
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
        cout << "DFSCountEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
