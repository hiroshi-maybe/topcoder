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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/27/2018
 
 9:20-9:49 system test passed (314.09 pt)
 
 I created array and painted because comparing border seemed to be error prone for me
 
 Editorials:
  - http://d.hatena.ne.jp/kusano_prog/20120616/1339876746
   - interval
  - http://topcoder.g.hatena.ne.jp/hotoku/20120617/1339932225
   - interval
  - http://purple-jwl.hatenablog.com/?page=1349518636
   - paint
  - http://rkx1209.hatenablog.com/entry/2012/10/30/224436
   - paint
 
 It's smart to reduce to two sub-problems of interval intersection.
 12:30-12:38 add solution with interval intersection.
 
 Key:
  - Paint or solve interval intersection
 
 Summary:
  - Analysis mistake in conversion to board 👎
 
 */

// math, O(1) solution
class TwoRectangles {
public:
  string ol="rectangle",seg="segment",poi="point",none="none";
  int intersection(int l1, int r1, int l2, int r2) {
    return min(r1,r2)-max(l1,l2);
  }
  string describeIntersection(vector<int> A, vector<int> B) {
    int x=intersection(A[0],A[2],B[0],B[2]);
    int y=intersection(A[1],A[3],B[1],B[3]);
    
    if(x<0||y<0) return none;
    if(x==0&&y==0) return poi;
    if(x>0&&y>0) return ol;
    return seg;
  }
};

// Simulation, O(W*H) time
int X[1001][1001];
class TwoRectangles_paint {
  public:
  string ol="rectangle",seg="segment",poi="point",none="none";
  void paint(VI &P) {
    FORE(x,P[0],P[2]) FORE(y,P[1],P[3]) ++X[x][y];
  }
  string describeIntersection(vector<int> A, vector<int> B) {
    ZERO(X);
    paint(A),paint(B);
    
    int cnt=0;
    FORE(x,0,1000) FORE(y,0,1000) cnt+=X[x][y]>1;
    if(cnt==0) return none;
    if(cnt==1) return poi;
    
    FORE(x,0,1000) FORE(y,0,1000) if(X[x][y]>1) {
      bool v=false,h=false;
      if(x<1000) h=X[x+1][y]>1;
      if(y<1000) v=X[x][y+1]>1;
      return v&&h?ol:seg;
    }
    
    /*
    FORE(x,A[0],A[2]) {
      if(A[1]>0) cnt+=X[x][A[1]-1];
      if(A[3]<1000) cnt+=X[x][A[3]+1];
    }
    FORE(y,A[1],A[3]) {
      if(A[0]>0) cnt+=X[A[0]-1][y];
      if(A[2]<1000) cnt+=X[A[2]+1][y];
    }
    if(cnt==0) {
      if(A[0]>0&&A[1]>0&&X[A[0]-1][A[1]-1]) return poi;
      if(A[2]<1000&&A[3]<1000&&X[A[2]+1][A[3]+1]) return poi;
      return none;
    }*/
    
    return seg;
  }
};

// CUT begin
ifstream data("TwoRectangles.sample");

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

bool do_test(vector<int> A, vector<int> B, string __expected) {
    time_t startClock = clock();
    TwoRectangles *instance = new TwoRectangles();
    string __result = instance->describeIntersection(A, B);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517073601;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TwoRectangles (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
