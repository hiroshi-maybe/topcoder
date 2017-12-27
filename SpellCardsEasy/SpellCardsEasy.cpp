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
 
 12/26/2017
 
 10:57-11:03 analysis
 11:12 ok, figured out that we don't need to use cards from left to right
 11:13-11:32 analyze again
 11:33-11:44 implement, submit and system test passed (441.42 pt)
 
 Recurrence relation of DP:
 
 f(i,N-i) = 0
 f(i,  r) = max(D[i]+f(i+1,r+L[i]-1), f(i+1,max(r-1,0)) if r+L[i]-1<=N-i-1
            f(i+1,max(r-1,0))                           otherwise
 
 res = f(0,0)
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+563
  - http://rkx1209.hatenablog.com/entry/2013/03/13/182203
 
 Key:
  - Add "debt" as part of states to ensure that cards can be removed later
  - If current "debt" is managed, what card caused the debt doesn't matter
 
 Summary:
  - If I've not misunderstood problem, I could have solved faster
 
 */

// O(N^2) time
int memo[51][51];
class SpellCardsEasy {
public:
  const int Inf=1e6;
  int N;
  VI L,D;
  
  // Original code before looking at editorial. cleaned up as seen in `f`
  int f_org(int i, int r) {
    if(N-i<r) return -Inf;
    if(i==N) return r==0?0:-Inf;
    int &res=memo[i][r];
    if(res>=0) return res;
    
    res=0;
    res=max({res,D[i]+f(i+1,r+L[i]-1), f(i+1,max(r-1,0))});
    return res;
  }
  
  int f(int i, int r) {
    if(N-i==r) return 0;
    int &res=memo[i][r];
    if(res>=0) return res;
    
    res=0;
    int rest=N-i-1;
    int a=r+L[i]-1<=rest?D[i]+f(i+1,r+L[i]-1):0;
    int b=f(i+1,max(r-1,0));
    res=max(a,b);
    return res;
  }
  
  int maxDamage(vector<int> LL, vector<int> DD) {
    this->L=LL,this->D=DD;
    this->N=SZ(L);
    MINUS(memo);
    return max(f(0,0),0);
  }
};

int dp[51];
class SpellCardsEasy_wrong {
  public:
  int maxDamage(vector<int> L, vector<int> D) {
    int N=SZ(L);
    int res=0;
    //const int Inf=1e6;
    ZERO(dp);
    REP(i,N) {
      int ii=i+L[i];
      if(ii<=N) {
        dp[ii]=max(dp[ii],dp[i]+D[i]);
        dump4(i,ii,dp[i]+D[i],dp[ii]);
        res=max(res,dp[ii]);
      }
      dp[i+1]=max(dp[i+1],dp[i]);
    }
    return res;
  }
};

// CUT begin
ifstream data("SpellCardsEasy.sample");

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

bool do_test(vector<int> level, vector<int> damage, int __expected) {
    time_t startClock = clock();
    SpellCardsEasy *instance = new SpellCardsEasy();
    int __result = instance->maxDamage(level, damage);
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
        vector<int> level;
        from_stream(level);
        vector<int> damage;
        from_stream(damage);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(level, damage, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514314655;
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
        cout << "SpellCardsEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
