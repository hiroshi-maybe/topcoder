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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/27/2018
 
 20:19-20:53 analysis
 21:26 Submit (377.51 pt) but TLE due to ordered set :(
 21:30 System test passed

 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+545
  - http://kmjp.hatenablog.jp/entry/2014/01/02/1100
    - Smart O(L*H) solution
    - In each `y`, count by assuming that K-th singal is at `y`
  - http://area.hateblo.jp/entry/2013/10/31/013635
 
 Key:
  - K=1 is a corner case
  - Once segment is determined, number of integer grid is given by gcd(delta x, delta y)
 
 Summary:
  - Some analysis mistakes were found during implementation 👎
   - Exit of rectangle does not need to be integer grid
   - K=1 corner case
 
 */

// O(L^2*H) time
LL C[601][601];
constexpr long long MOD = 1e9+7;
class SpacetskE {
  public:
  int gcd(int a, int b) {
    return b==0?a:gcd(b,a%b);
  }
  int grid(int x1, int y1, int x2, int y2) {
    if(x1<x2) swap(x1,x2);
    int xx=x2-x1,yy=y2-y1;
    return gcd(xx,yy)+1;
  }
  int countsets(int L, int H, int K) {
    if(K==1) return (L+1)*(H+1);
    REPE(i,600) {
      C[i][0]=1;
      FORE(j,1,i) C[i][j]=C[i-1][j-1]+C[i-1][j],C[i][j]%=MOD;
    }
    
    LL res=0;
    REPE(x1,L) {
      dump(x1);
      int viz[401][401]={};
      for(int y2=H; y2>=1; --y2) REPE(x2,L) {
        int xx=x2-x1,yy=y2-0;
        int a=gcd(xx,yy);
//        dump4(x2,y2,xx,yy);
//        dump4(a,xx/a,yy/a,viz.count({xx/a,yy/a}));
        if(viz[xx/a+200][yy/a+200]) continue;
        viz[xx/a+200][yy/a+200]=1;
        int b=abs(a)+1;
//        dump4(x2,y2,b,C[b][K]);
        if(b>=K) res+=C[b][K],res%=MOD;
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("SpacetskE.sample");

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

bool do_test(int L, int H, int K, int __expected) {
    time_t startClock = clock();
    SpacetskE *instance = new SpacetskE();
    int __result = instance->countsets(L, H, K);
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
        int L;
        from_stream(L);
        int H;
        from_stream(H);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, H, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517113166;
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
        cout << "SpacetskE (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
