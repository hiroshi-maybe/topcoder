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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/9/2017
 
 12:19-12:41 (336.04 pt)
 
 13:48 reduce edges (no need to be complete graph in component)
 https://community.topcoder.com/stat?c=problem_solution&rd=16849&rm=329526&cr=40427782&pm=14466
 
 */

// O(V^2) time
class ConnectedComponentConstruction {
public:
  vector<string> construct(vector<int> s) {
    int V=SZ(s);
    unordered_map<int,VI> M;
    vector<VI> cs;
    REP(i,V) {
      int n=s[i];
      M[n].push_back(i);
      if (SZ(M[n])==n) cs.push_back(M[n]), M.erase(n);
    }
    
    if (M.size()) return {};
    string empty(V,'N');
    vector<string> res(V,empty);
    
    FORR(vs, cs) {
      FOR(i,1,SZ(vs)) {
        res[vs[0]][vs[i]]='Y';
        res[vs[i]][vs[0]]='Y';
      }
    }
    
    return res;
  }
};

class ConnectedComponentConstruction_org {
  public:
  vector<string> construct(vector<int> s) {
    int V=SZ(s);
    unordered_map<int,VI> M;
    vector<VI> cs;
    REP(i,V) {
      int n=s[i];
      M[n].push_back(i);
      if (SZ(M[n])==n) cs.push_back(M[n]), M.erase(n);
    }
    
    if (M.size()) return {};
    string empty(V,'N');
    vector<string> res(V,empty);
    
    FORR(vs, cs) {
      REP(i,SZ(vs)) {
        REP(j,i) {
          int v1=vs[i],v2=vs[j];
          res[v1][v2]='Y';
          res[v2][v1]='Y';
        }
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ConnectedComponentConstruction.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> s, vector<string> __expected) {
    time_t startClock = clock();
    ConnectedComponentConstruction *instance = new ConnectedComponentConstruction();
    vector<string> __result = instance->construct(s);
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
        vector<int> s;
        from_stream(s);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499627962;
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
        cout << "ConnectedComponentConstruction (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
