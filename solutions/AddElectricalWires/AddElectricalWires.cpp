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
 
 8/30/2018
 
 15:00-15:13 analysis
 15:33 AC (132.07 pt)
 
 Editorials:
  - https://chngng.blogspot.com/2014/02/srm-410-div1-easy-addelectricalwires.html
  - https://topcoder.g.hatena.ne.jp/nitoyon/20081101/1225548419
  - http://82rensa.blogspot.com/2012/06/srm410-div2-medium.html
 
 Clean implementation by @Petr: http://community.topcoder.com/stat?c=problem_solution&rm=298031&rd=12182&pm=8817&cr=10574855
 
 */

// 15:00-15:13 analysis
// 15:33 AC (132.07 pt)
int uf[51];
int find(int x) { return x==uf[x]?x:uf[x]=find(uf[x]); }
void unite(int x, int y) {
  int xx=find(x),yy=find(y);
  if(xx!=yy) uf[xx]=yy;
}

class AddElectricalWires {
  public:
  int V;
  int maxNewWires(vector<string> mx, vector<int> gr) {
    V=SZ(mx);
    REP(i,V)uf[i]=i;
    REP(j,V)REP(i,j) if(mx[i][j]=='1') unite(i,j);
    VI G(V,-1);
    vector<II> cnts;
    REP(i,SZ(gr)) {
      int u=gr[i];
      int cnt=0;
      REP(v,V) if(find(u)==find(v)) {
        G[v]=i;
        cnt++;
      }
      cnts.emplace_back(cnt,i);
    }
    sort(cnts.rbegin(),cnts.rend());
    REP(i,V) if(G[i]==-1) {
      cnts[0].first++;
      G[i]=cnts[0].second;
    }
//    dumpAR(G);
    int res=0;
    REP(i,SZ(cnts)) {
      int id=cnts[i].second,cnt=cnts[i].first;
      VI X; REP(u,V) if(G[u]==id) X.push_back(u);
      int e=0;
      FORR(u,X) REP(v,V) if(u<v) e+=mx[u][v]=='1';
      
//      dump3(id,cnt,e);
//      dumpAR(X);
      res+=cnt*(cnt-1)/2-e;
    }
    return res;
  }
};

// CUT begin
ifstream data("AddElectricalWires.sample");

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

bool do_test(vector<string> wires, vector<int> gridConnections, int __expected) {
    time_t startClock = clock();
    AddElectricalWires *instance = new AddElectricalWires();
    int __result = instance->maxNewWires(wires, gridConnections);
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
        vector<string> wires;
        from_stream(wires);
        vector<int> gridConnections;
        from_stream(gridConnections);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(wires, gridConnections, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535666388;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "AddElectricalWires (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
