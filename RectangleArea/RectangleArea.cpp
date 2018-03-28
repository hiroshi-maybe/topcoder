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
 
 3/27/2018
 
 9:35-10:05 analysis
 10:06-10:26 ACC (382.16 pt)
 
 Editorials:
  - http://d.hatena.ne.jp/kusano_prog/20110505/1304609369
   - union-find
  - http://kmjp.hatenablog.jp/entry/2014/03/26/1000
   - dfs
  - http://kenkoooo.hatenablog.com/entry/2016/08/04/024243
   - greedy
  - http://d.hatena.ne.jp/simezi_tan/20110611/1307727956
   - greedy
  - https://chngng.blogspot.jp/2014/01/srm-505-div1-easy-rectanglearea.html
   - greedy
  - http://topcoder.g.hatena.ne.jp/firewood/20110510/1305044277
   - union-find
 
 Summary:
  - Slow analysis
   - Too slow after figuring out that this is graph problem
   - I was confused how to identify R+C vertices
   - I was confused about default edges from input
  - Poor implementation. It took 20 mins to implement
   - I knew that either dfs and union find works
   - However I wanted to try dfs instead of union find
 
 */

int viz[101];
class RectangleArea {
public:
  VI G[101];
  void dfs(int u) {
    if(viz[u]) return;
    viz[u]=true;
    FORR(v,G[u]) dfs(v);
  }
  int minimumQueries(vector<string> GG) {
    int R=SZ(GG),C=SZ(GG[0]);
    ZERO(viz);
    REP(i,100) G[i].clear();
    //    REP(r,R) G[r].push_back(R+r),G[R+r].push_back(r);
    REP(i,R) REP(j,C) if(GG[i][j]=='Y') {
      int u=i,v=R+j;
      G[u].push_back(v),G[v].push_back(u);
    }
    int res=0;
    VI temp;
    REP(u,R) if(!viz[u]) ++res,dfs(u),temp.push_back(u);
    REP(u,C) if(!viz[u+R]) ++res,dfs(u+R),temp.push_back(u);
    //     dumpAR(temp);
    return res-1;
  }
};

// CUT begin
ifstream data("RectangleArea.sample");

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

bool do_test(vector<string> known, int __expected) {
    time_t startClock = clock();
    RectangleArea *instance = new RectangleArea();
    int __result = instance->minimumQueries(known);
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
        vector<string> known;
        from_stream(known);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(known, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522168525;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "RectangleArea (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
