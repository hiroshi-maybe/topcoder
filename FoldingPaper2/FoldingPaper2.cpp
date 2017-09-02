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
 
 9/1/2017
 
 8:38-8:57,8:58-9:21 (230.49 pt)
 17:40-17:43 WA. fixed a bug and resubmit.
 
 editorials:
  - http://kmjp.hatenablog.jp/entry/2015/04/10/0930
  - https://apps.topcoder.com/wiki/display/tc/SRM+655
  - http://roiti46.hatenablog.com/entry/2015/04/10/TopCoder_SRM_655_Div2%3A_Med
  - http://torus711.hatenablog.com/entry/20150412/1428848899
 
 key:
  - brute force pair of potential w and h by O(sqrt(A))
  - number of fold is independent in two dimensions
  - If w is folded by x, ceil(w/2) <= w-x <= w-1
 
 summary:
  - analysis of possible range was correct 👍
  - take ceil not floor
   - first time I missed to take ceil
   - second time I made a mistake of ceil(k/n)
    - ceil(k/n) should be (k+n-1)/n (not (k+n)/n)
    - otherwise infinite loop may happen
  - x<y for W<H, (x,W) and (y,H) are not always optimal
   - we should check (y,W) and (x,H) too
   - suppose W<H and x<y and H==x, then we may get y from W by one fold
   - loose analysis 👎
   - hit WA in first submission :(
  - nice problem to test analysis 👍
 
 */

class FoldingPaper2 {
  public:
  const int Inf=1e9;
  
  int f(int x,int T) {
    if(x<T) return -1;
    if(x==T) return 0;
    int res=0;
    while((x+1)/2>T) {
      x=(x+1)/2;
      ++res;
    }
    
    return res+1;
  }
  
  int solve(int W, int H, int A) {
    int res=Inf;
    for(int a=1; a<=A; ++a) if(A%a==0) {
      int b=A/a;
      int x=f(W,a),y=f(H,b);
      if(x>=0&&y>=0) res=min(res,x+y);
    }
    return res==Inf?-1:res;
  }
};

// CUT begin
ifstream data("FoldingPaper2.sample");

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

bool do_test(int W, int H, int A, int __expected) {
    time_t startClock = clock();
    FoldingPaper2 *instance = new FoldingPaper2();
    int __result = instance->solve(W, H, A);
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
        int W;
        from_stream(W);
        int H;
        from_stream(H);
        int A;
        from_stream(A);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(W, H, A, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504280296;
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
        cout << "FoldingPaper2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
