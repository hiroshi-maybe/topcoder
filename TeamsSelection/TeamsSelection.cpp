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
 
 11/16/2017
 
 8:52-9:07 system test passed (199.05 pt)
 18:50-18:58 add a bit simpler solution
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+586
  - https://topcoder.g.hatena.ne.jp/firewood/20130819/1376911103
  - http://torus711.hatenablog.com/entry/20130801/p3
  - http://emkcsharp.hatenablog.com/entry/SRM586/TeamsSelection
 
 */

class TeamsSelection {
public:
  string simulate(vector<int> P1, vector<int> P2) {
    vector<int> P[2];
    P[0]=P1,P[1]=P2;
    int N=SZ(P1);
    int viz[55]={};
    REP(i,N) {
      int t=i%2;
      REP(j,N) if(viz[P[t][j]]==0) {
        viz[P[t][j]]=1+t;
        break;
      }
    }
    string res;
    FOR(i,1,N+1) res.push_back('0'+viz[i]);
    return res;
  }
};

class TeamsSelection_org {
  public:
  string simulate(vector<int> P1, vector<int> P2) {
    int N=SZ(P1);
    MAPII xs;
    int t=0;
    vector<VI> P={P1,P2};
    int i1=0,i2=0;
    VI is={i1,i2};
    while(SZ(xs)<N) {
      int i=is[t];
      VI PP=P[t];
      while(xs.count(PP[i])>0) i++;
      xs[PP[i]]=t+1;
//      dump2(PP[i],t+1);
      is[t]=i;
      t=1^t;
    }
    string res(N,'#');
    FOR(i,1,N+1) res[i-1]='0'+xs[i];
    return res;
  }
};

// CUT begin
ifstream data("TeamsSelection.sample");

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

bool do_test(vector<int> preference1, vector<int> preference2, string __expected) {
    time_t startClock = clock();
    TeamsSelection *instance = new TeamsSelection();
    string __result = instance->simulate(preference1, preference2);
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
        vector<int> preference1;
        from_stream(preference1);
        vector<int> preference2;
        from_stream(preference2);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(preference1, preference2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510851130;
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
        cout << "TeamsSelection (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
