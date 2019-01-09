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


constexpr int MOD = 1e9+7;

LL memo[1005][2];
LL alllower[1005];

/**
 
 7/8/2017
 
 TCO 17 Round 2B div1
 
 9:30-10:25 time up
 
 8/6/2017
 
 22:47-23:19 revisit problem
 23:19-24:24 read editorials. still cannot understand
 - DP in both up/down directions
  - http://kmjp.hatenablog.jp/entry/2017/07/09/0930
 - taking intervals of vetically consective same letters
  - https://www.topcoder.com/blog/2017-tco-algorithm-round-2b-editorials/
  - https://community.topcoder.com/stat?c=problem_solution&rd=16946&rm=330314&cr=22692969&pm=14633
 
 */

class DengklekGaneshAndTree {
public:
  vector<SETI> E;
  int N;
  string ls;
  int dfs(int cur, int upper, int lv) {
    if(cur>=N) return 0;
    if(memo[cur][upper]!=-1) return memo[cur][upper];
    
    LL lowern = (upper==1);
    
    LL res=1;
    FORR(vi,E[cur]) {
      LL x = dfs(vi,upper,lv+1);
      x %= MOD;
      if(ls[vi]!=ls[cur]) x+=dfs(vi,!upper,lv+1), x%=MOD;
      res *= x;
      res %= MOD;
    }
    
//    dump4(cur,upper,ls[cur],res);
    
    alllower[lv]+=lowern;
    
    return memo[cur][upper]=res;
  }
  
  int getCount(string _ls, vector <int> ps) {
    ls = _ls;
    memset(memo,-1,sizeof(memo));
    memset(alllower,-1,sizeof(alllower));
    
    N=SZ(ls);
    E = vector<SETI>(N);
    FOR(i,1,N) {
      E[ps[i-1]].insert(i);
    }
    
    LL res = dfs(0,true,1);
    res %= MOD;
    return res;
  }
};

// CUT begin
ifstream data("DengklekGaneshAndTree.sample");

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

bool do_test(string labels, vector<int> parents, int __expected) {
    time_t startClock = clock();
    DengklekGaneshAndTree *instance = new DengklekGaneshAndTree();
    int __result = instance->getCount(labels, parents);
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
        string labels;
        from_stream(labels);
        vector<int> parents;
        from_stream(parents);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(labels, parents, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502084559;
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
        cout << "DengklekGaneshAndTree (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
