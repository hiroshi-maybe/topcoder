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
 
 3/12/2018
 
 9:04-9:24 analysis
 9:25-9:32 ACC (292.75 pt)
 
 Editorials:
  - https://topcoder.g.hatena.ne.jp/JAPLJ/20110810/1312974278
  - https://apps.topcoder.com/wiki/display/tc/SRM+514
  - http://d.hatena.ne.jp/kusano_prog/20110810/1312947798
   - Clear explanation of property of reachable cells in terms of parity
  - https://topcoder.g.hatena.ne.jp/jackpersel/20110810/1312959412
  - https://chngng.blogspot.com/2015/05/srm-514-div1-easy-magicalgirllevelonedi.html
  - http://kyuridenamida.hatenablog.com/entry/2011/08/10/122913
  - http://purple-jwl.hatenablog.com/entry/20121114/1352881658
  - http://d.hatena.ne.jp/firisu/20110821/1313930166
 
 Editorial is introducing more math solution.
 Important approach of it:
  - Problem is asking just reachability => Analyze property of reachable place
  - Start from simple cases. Move with only one of A. Compound case is on top of simple case.
  - If (a+1,b) is reachable from (a,b), any cell is reachable. Try to find if it's feasible.
  - Experiment, experiment, experiment!
 
 Let's solve simple case first. We just use only one move with `n`.
 
 By taking moves of (n,1), (-n,1), we can cancel `n` and move from (a,b) to (a+2,b).
 This means any even cells are reachalbe from (0,0) by symmetry property.
 
 (even, even) is possible
 
 We tried two (n,1) moves. Next let's see (n,1) and (1,n). We may be able to find different pattern.
 (a,b)->(a+n,b+1)->(a+n+1,b+n+1)
 
 It's moving `n+1` cells in both axis. If `n` is even, this is (odd, odd).
 We already know that any even move is possible.
 Thus any (odd, odd) positions are possible.
 
 From above discussion, res = "YES" if any n is even.
 
 If n is odd, we can still move to only even positions from (0,0) with (n+1,n+1) move.
 We analyzed two moves {(n,1),(1,n)} and {(n,1),(n,1)}. Let's see one step {(n,1)}.
 This is actually moving to (odd, odd) position.
 Generally it's possible to add even moves to it. Thus any (odd,odd) positions are reachable.
 
 Above discussion is only when single move is used. Things change when even step and odd step are combined?
 Whenever even `n` exists, result is "YES". So even step is more "powerful" than odd step.
 Conclusion:
  a) even `n` exists => res = "YES"
  b) step is only odd `n` => res = (X,Y) = (even,even) or (odd,odd)
 
 Summary:
  - Easier version of https://github.com/k-ori/topcoder/blob/master/KnightCircuit/KnightCircuit.cpp
  - I just did brute-force. However probably I was not able to solve div1 easy version
 
 */

class MagicalGirlLevelTwoDivTwo {
public:
  string yes="YES",no="NO";
  string isReachable(vector<int> A, int tx, int ty) {
    FORR(n,A) if(n%2==0) return yes;
    tx=abs(tx),ty=abs(ty);
    if (tx%2==0&&ty%2==0) return yes;
    if (tx%2==1&&ty%2==1) return yes;
    return no;
  }
};

class MagicalGirlLevelTwoDivTwo_org {
  public:
  string yes="YES",no="NO";
  bool ok(int x, int y) {
    return -30<=x&&x<=30&&-30<=y&&y<=30;
  }
  string isReachable(vector<int> A, int tx, int ty) {
    set<II> viz;
    queue<II> Q;
    Q.emplace(0,0); viz.emplace(0,0);
    while(SZ(Q)) {
      auto p=Q.front(); Q.pop();
      int x=p.first,y=p.second;
//      dump2(x,y);
      FORR(a,A) for(int sx=-1; sx<=1; sx+=2) for(int sy=-1; sy<=1; sy+=2) {
        int xx=x+sx*a,yy=y+sy*1;
        if(ok(xx,yy)&&!viz.count({xx,yy})) Q.emplace(xx,yy), viz.emplace(xx,yy);
        xx=x+sx*1,yy=y+sy*a;
        if(ok(xx,yy)&&!viz.count({xx,yy})) Q.emplace(xx,yy), viz.emplace(xx,yy);
      }
    }
    return viz.count({tx,ty})?yes:no;
  }
};

// CUT begin
ifstream data("MagicalGirlLevelTwoDivTwo.sample");

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

bool do_test(vector<int> jumpTypes, int x, int y, string __expected) {
    time_t startClock = clock();
    MagicalGirlLevelTwoDivTwo *instance = new MagicalGirlLevelTwoDivTwo();
    string __result = instance->isReachable(jumpTypes, x, y);
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
        vector<int> jumpTypes;
        from_stream(jumpTypes);
        int x;
        from_stream(x);
        int y;
        from_stream(y);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(jumpTypes, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520870656;
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
        cout << "MagicalGirlLevelTwoDivTwo (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
