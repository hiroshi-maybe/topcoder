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
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/10/2018
 
 SRM 729
 
 9:13-9:47 System test failed due to 4 step cases (234.59 pt)
 17:30-18:00 Read twitter timeline and add solution.
 
 I though that possible step is at most 3. However that's not the case.
 I was also expecting corners though, it was two corners which are diagonal.
 
 Look at this diagram: https://twitter.com/uwitenpen/status/962395169772355585
 
 Iterating all the valid areas exceeds TLE.
 Just going through only borders are sufficient.
 
 Editorials:
  - https://togetter.com/li/1198121
 
 Key:
  - At most 4 (not 3) steps
  - Brute-force valid four borders is sufficient
 
 Summary:
  - Focusing corner was good. However consider more various cases.
  - Two diagonal corners are necessary condition. It's not sufficient 😞
 
 */

// @nuip's solution
int dist[1123][1123];
class FrogSquare {
public:
  int N,D;
  bool ok(int x, int y) { return x*x+y*y>=D*D; }
  void move(int x1, int y1, int x2, int y2, queue<II> &Q) {
    if(ok(x1-x2,y1-y2)&&dist[y2][x2]>dist[y1][x1]+1) {
      dist[y2][x2]=dist[y1][x1]+1;
      Q.emplace(x2,y2);
    }
  }
  int minimalJumps(int N, int D, int sx, int sy, int tx, int ty) {
    this->N=N,this->D=D;
    if(sx==tx&&sy==ty) return 0;
    if(ok(sx-tx,sy-ty)) return 1;
    REP(i,N)REP(j,N) dist[i][j]=1e9;
    
    queue<II> Q; Q.emplace(sx,sy);
    dist[sy][sx]=0;
    while(SZ(Q)) {
      int x,y;
      tie(x,y)=Q.front(); Q.pop();
      if(ok(x-tx,y-ty)) return dist[y][x]+1;
      move(x,y,0,N-1,Q);
      move(x,y,N-1,0,Q);
      move(x,y,0,0,Q);
      move(x,y,N-1,N-1,Q);
      /*
      REP(i,N) {
        move(x,y,0,i,Q);
        move(x,y,i,0,Q);
        move(x,y,N-1,i,Q);
        move(x,y,i,N-1,Q);
      }*/
    }
    return -1;
  }
};

// System test failed
class FrogSquare_org {
  public:
  int N,D;
  set<II> f(int rr, int cc) {
    set<II> res;
    REP(r,N)REP(c,N) {
      int dx=r-rr;
      int dy=c-cc;
      if(dx*dx+dy*dy>=D*D) res.emplace(r,c);
    }
    return res;
  }
  int minimalJumps(int N, int D, int sc, int sr, int tc, int tr) {
    this->N=N,this->D=D;
    if(sr==tr&&sc==tc) return 0;
    set<II> S1=f(sr,sc),S2=f(tr,tc);
//    dump2(SZ(S1),SZ(S2));
    if(SZ(S1)==0||SZ(S2)==0) return -1;
    if(S1.count({tr,tc})) return 1;
    FORR(p1,S1) if(S2.count(p1)) return 2;
    return 3;
  }
};

// CUT begin
ifstream data("FrogSquare.sample");

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

bool do_test(int n, int d, int sx, int sy, int tx, int ty, int __expected) {
    time_t startClock = clock();
    FrogSquare *instance = new FrogSquare();
    int __result = instance->minimalJumps(n, d, sx, sy, tx, ty);
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
        int n;
        from_stream(n);
        int d;
        from_stream(d);
        int sx;
        from_stream(sx);
        int sy;
        from_stream(sy);
        int tx;
        from_stream(tx);
        int ty;
        from_stream(ty);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, d, sx, sy, tx, ty, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1518282783;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FrogSquare (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
