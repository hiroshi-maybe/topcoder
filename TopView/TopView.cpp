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
 
 1/14/2018
 
 13:35-13:45 analysis
 13:46-14:07 implement, submit and ACC (547.74 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+550
  - http://kmjp.hatenablog.jp/entry/2013/12/28/1030
  - http://d.hatena.ne.jp/kusano_prog/20120721/1342903730
  - http://area.hateblo.jp/entry/2013/12/10/011255
 
 Summary:
  - I figured out topological sort quickly 👍
  - Slow implementation 👎
  - outdegree is not necessary
 
 */
int viz[128];
set<char> IN[128];
set<char> OUT[128];
class TopView {
  public:
  string err="ERROR!";
  string findOrder(vector<string> G) {
    ZERO(viz);
    for(char c='0'; c<='z'; ++c) IN[c-'0'].clear(),OUT[c-'0'].clear();
    int R=SZ(G),C=SZ(G[0]);
    
    for(char c='0'; c<='z'; ++c) {
      int minr=100,maxr=-1,minc=100,maxc=-1;
      REP(i,R)REP(j,C) if(G[i][j]==c) {
        MINS(minr,i),MAXS(maxr,i);
        MINS(minc,j),MAXS(maxc,j);
      }
      if(maxr==-1) continue;
      viz[c-'0']=1;
      FORE(i,minr,maxr) FORE(j,minc,maxc) if(G[i][j]!=c) {
        if(G[i][j]=='.') return err;
        OUT[c-'0'].emplace(G[i][j]);
        IN[G[i][j]-'0'].emplace(c);
      }
    }
    
    string res;
    while(true) {
      char x='#';
      for(char c='0'; c<='z'; ++c) if(SZ(IN[c-'0'])==0&&viz[c-'0']) {
        x=c;
        break;
      }
      if(x=='#') {
        int cnt=0;
        for(char c='0'; c<='z'; ++c) cnt+=viz[c-'0'];
        if(cnt>0) return err;
        else break;
      }
      viz[x-'0']=0;
      res+=x;
      FORR(c,OUT[x-'0']) IN[c-'0'].erase(x);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("TopView.sample");

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

bool do_test(vector<string> grid, string __expected) {
    time_t startClock = clock();
    TopView *instance = new TopView();
    string __result = instance->findOrder(grid);
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
        vector<string> grid;
        from_stream(grid);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515965695;
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
        cout << "TopView (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
