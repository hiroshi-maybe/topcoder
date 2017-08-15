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

/**
 
 8/14/2017
 
 9:15-9:50 understood problem and time up
 
 8/15/2017
 
 8:20-9:00,9:30-9:50 read editorials
  - https://apps.topcoder.com/wiki/display/tc/SRM+669
  - http://kmjp.hatenablog.jp/entry/2015/09/28/1000
  - https://topcoder.g.hatena.ne.jp/yambe2002/20151120/1447995907
 
 9:50-10:19 add solution
 
 Submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=327155&rd=16549&pm=14018&cr=40012557
    - actually no need to remember weight of all the patterns
    - once we figure out line weight, it's easy to count patterns by O(V^3)
    - brute-force V[l] and V[r] (r=l+2). if w[i] (l<=i<r) is 2, we can pick only 2 (multiply by 1).
  - https://community.topcoder.com/stat?c=problem_solution&rm=327141&rd=16549&pm=14018&cr=40001864
    - using DFS though, basic idea is same. look at line-weight between l and r
 
 Key:
  - res = number of each pattern * V!/2
  - V is small. brute-force 2^(V-1) assignments of 1 or 2 for line edges
  - assignment of weight affects all other edge assignment to satisfy MST condition
    - suppose there are two vertex sets V_L={v[i]:i=0..k} and V_R={v[i]:i=k+1..<V}
      - if w(v[k],v[k+1]) is p (p={1,2}), ∀v_l,v_r, w(v_l,v_r)>=p, v_l∈V_L, v_r∈V_R
  - pin line edges and determine edges so that they satisfy MST condition under pinned edge
  - don't divide by 2. OK: FACT(n)/2=3*4*..*n, NG: FACT(n)/2=2*3*..*n/2
 
 Summary:
  - it turns out this is kind of brute-force (not DP) in terms of search space
  - start from brute force. reduce search space ONLY if necessary
 
 */

constexpr int MOD = 1e9+7;

int minw[17][17];
class LineMSTDiv2 {
  public:
  int count(int V) {
    LL res=0;
    
    LL FACT=1;
    for(int n=3;n<=V;++n) FACT*=n, FACT%=MOD;
    
    REP(mask,1<<(V-1)) {
      ZERO(minw);
      REP(i,V-1) {
        if(mask&(1<<i)) {
          REP(l,i+1)FOR(r,i+1,V) minw[l][r]=1;
        }
      }
      
      LL cnt=1;
      REP(l,V-1)FOR(r,l+2,V) if(!minw[l][r]) cnt*=2, cnt%=MOD;
      (cnt*=FACT)%=MOD;
      res+=cnt, res%=MOD;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("LineMSTDiv2.sample");

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

bool do_test(int N, int __expected) {
    time_t startClock = clock();
    LineMSTDiv2 *instance = new LineMSTDiv2();
    int __result = instance->count(N);
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
        int __answer;
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
        int T = time(NULL) - 1502727319;
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
        cout << "LineMSTDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
