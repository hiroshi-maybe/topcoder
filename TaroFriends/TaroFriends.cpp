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
 
 10/13/2017
 
 8:34-8:57 analysis
 8:58-9:02 implemented and systemt test passed (295.10 pt)
 
 same as div1 easy
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+613
   - semi brute-force solution and greedy solution
  - http://torus711.hatenablog.com/entry/20140321/p1
   - semi brute-force
  - http://kmjp.hatenablog.jp/entry/2014/03/22/0900
   - greedy solution (similar to my original solution)
  - http://topcoder.g.hatena.ne.jp/kojingharang/20140323#1395589137?utm_source=twitterfeed&utm_medium=twitter
   - semi brute-force
 
 24:20-24:29 add semi brute-force solution
 
 Running time to try x-D and x+D for all x is O(2^N) time.
 We don't need to know all the positions of cats.
 We can try all the pairs of edges and verify rest of cats.
 
 Another analysis is that left most position is at most 100.
 We try all left positions and move others to minimize distance.
 
 summary:
  - After analyzing 2^N algorithm, I jumped to find greedy. It took more time to solve
    - Brute-force to greedy by intuition does not seem to be efficient
  - I should try to upper bound partial conditions (in this problem, position of left-most or right-most positions)
   - pin partial state by search
   - basic strategy is brute force
 
 */

// O(N^3) time
class TaroFriends {
public:
  int getNumber(vector<int> xs, int D) {
    int N=SZ(xs);
    if(N<=1) return 0;
    int res=2e8;
    REP(j,N) REP(i,j) {
      VI xx1={xs[i]-D, xs[i]+D},xx2={xs[j]-D, xs[j]+D};
      FORR(x1,xx1) FORR(x2,xx2) {
        int L=min(x1,x2), R=max(x1,x2);
        
        bool ok=true;
        REP(k,N) if(k!=i&&k!=j) {
          int x=xs[k];
          ok &= (L<=x-D&&x-D<=R) || (L<=x+D&&x+D<=R);
        }
        if(ok) res=min(res,R-L);
      }
    }
    
    return res;
  }
};

// O(N^2) time
class TaroFriends_org {
  public:
  int getNumber(vector<int> xs, int D) {
    sort(xs.begin(),xs.end());
    int res=1e9;
    int N=SZ(xs);
    REP(k,N+1) {
      int l=1e9, r=-1e9;
      REP(i,N) {
        int xx=i<k?xs[i]+D:xs[i]-D;
        l=min(l,xx), r=max(r,xx);
      }
      res=min(res,abs(r-l));
    }
    return res;
  }
};

// CUT begin
ifstream data("TaroFriends.sample");

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

bool do_test(vector<int> coordinates, int X, int __expected) {
    time_t startClock = clock();
    TaroFriends *instance = new TaroFriends();
    int __result = instance->getNumber(coordinates, X);
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
        vector<int> coordinates;
        from_stream(coordinates);
        int X;
        from_stream(X);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(coordinates, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507908874;
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
        cout << "TaroFriends (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
