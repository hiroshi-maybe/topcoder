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
 
 3/14/2018
 
 11:41-11:55 analysis
 11:56-12:14 ACC (657.85 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+512
  - http://d.hatena.ne.jp/kusano_prog/20111016/1318744255
  - http://kmjp.hatenablog.jp/entry/2014/02/13/1000
    - solution with min-cost flow!
  - http://purple-jwl.hatenablog.com/entry/20130321/1363874435
  - http://area.hateblo.jp/entry/2013/08/23/021933
 
 One A's gesture can be paired with one B's gesture.
 Max point for gesture is two.
 Also corresponding gesture to A's specific gesture to gain two points is one gesture.
 If there is such gesture in B, we can greedily pick it up.
 
 Proof:

 We have A's gesture `x`. Also we are using B's gesture `y` which gives two points.
 Suppose we gain higher points for `y`.
 One possibility is that there is x' which gives three points higher than two.
 That contradicts that two point is maximum.
 Symmetrically x should be paired with y as well. Thus `x` should be paired with `y`.
 
 Now we are selecting pairs from remaining gestures to make as many one points as possible.
 Actually Only one gesture is possible to gain 1 point for specific A's gesture.
 By the similar proof to two points, we can greedily pick up B's gesture.
 
 Summary:
  - misunderstood condition of 1 pt and wasted 10 mins. Sigh 😩
 
 */
int viz[2][50];
class DoubleRoshambo {
  public:
  int win(char a, char b) {
    if(a=='R'&&b=='S') return 1;
    if(a=='P'&&b=='R') return 1;
    if(a=='S'&&b=='P') return 1;
    return a==b?0:-1;
  }
  int f(string a, string b) {
    int x=win(a[0],b[0]),y=win(a[1],b[1]);
    if(x==1&&y==1) return 2;
    if(x==0&&y==1) return 1;
    return 0;
  }
  int maxScore(vector<string> A, vector<string> B) {
    ZERO(viz);
    int res=0;
    int N=SZ(A);
    REP(i,N) REP(j,N) if(!viz[0][i]&&!viz[1][j]&&f(A[i],B[j])==2) {
      viz[0][i]=viz[1][j]=1;
      res+=2;
      dump3(i,j,res);
      break;
    }
    dump(res);
    REP(i,N) REP(j,N) if(!viz[0][i]&&!viz[1][j]) {
      if(f(A[i],B[j])==1) {
        res+=1;
        viz[0][i]=viz[1][j]=1;
        dump3(i,j,res);
        break;
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("DoubleRoshambo.sample");

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

bool do_test(vector<string> A, vector<string> E, int __expected) {
    time_t startClock = clock();
    DoubleRoshambo *instance = new DoubleRoshambo();
    int __result = instance->maxScore(A, E);
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
        vector<string> A;
        from_stream(A);
        vector<string> E;
        from_stream(E);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, E, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521052880;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1024 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DoubleRoshambo (1024 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
