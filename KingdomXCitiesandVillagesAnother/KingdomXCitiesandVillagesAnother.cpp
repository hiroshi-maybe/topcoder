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
 
 3/26/2018
 
 10:15-10:33 analysis
 10:41 submit (549.27 pt). However 1WA
 10:45 fix implementation bug and resubmit. ACC :(
 
 I chose minimal edge until All the villages are covered.
 Proof of correctness should be same as the one of minimum spanning tree.
 
 After reading the editorial, it turns out that my solution is same as MST by assuming all the cities are already connected.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/Member+SRM+503
  - http://kmjp.hatenablog.jp/entry/2014/04/19/1300
  - http://d.hatena.ne.jp/kusano_prog/20110420/1303324746
  - http://www.vexorian.com/2011/04/member-srm-503-div2-250-div2-900.html?m=0
  - http://pushl.hatenablog.com/entry/2013/06/14/164821
  - https://topcoder.g.hatena.ne.jp/kita_yuta/20110420/1303306268
  - http://peryaudo.hatenablog.com/entry/20110417/1303048038
 
 Summary:
  - I used Prim's algorithm to solve MST
 
 */
int viz[51];
class KingdomXCitiesandVillagesAnother {
  public:
  double determineLength(vector<int> CX, vector<int> CY, vector<int> VX, vector<int> VY) {
    int N=SZ(CX), M=SZ(VX);
    ZERO(viz);
    set<pair<double,int>> Q;
    REP(i,N) REP(j,M) {
      double d=hypot(CX[i]-VX[j], CY[i]-VY[j]);
      Q.emplace(d, j);
    }
    
    double res=0;
    while(SZ(Q)) {
      auto it=Q.begin();
      double d=it->first; int u=it->second;
      Q.erase(it);
      if(viz[u]) continue;
//      dump2(u,d);
      res+=d; viz[u]=true;
      REP(j,M) if(!viz[j]) Q.emplace(hypot(VX[u]-VX[j],VY[u]-VY[j]), j);
    }
    return res;
  }
};

// CUT begin
ifstream data("KingdomXCitiesandVillagesAnother.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> cityX, vector<int> cityY, vector<int> villageX, vector<int> villageY, double __expected) {
    time_t startClock = clock();
    KingdomXCitiesandVillagesAnother *instance = new KingdomXCitiesandVillagesAnother();
    double __result = instance->determineLength(cityX, cityY, villageX, villageY);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> cityX;
        from_stream(cityX);
        vector<int> cityY;
        from_stream(cityY);
        vector<int> villageX;
        from_stream(villageX);
        vector<int> villageY;
        from_stream(villageY);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cityX, cityY, villageX, villageY, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522084524;
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
        cout << "KingdomXCitiesandVillagesAnother (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
