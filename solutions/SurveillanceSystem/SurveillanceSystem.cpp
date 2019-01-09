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
 
 11/30/2017
 
 8:25-9:02 analysis
 9:03-9:39 implementation, debug and submit. System test passed (182.46 pt)
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+581
   - searching negated cases
   - Find `+` first. oterwise judge `-` or `?`
  - http://kmjp.hatenablog.jp/entry/2013/06/05/0900
  - http://emkcsharp.hatenablog.com/entry/SRM581/SurveillanceSystem
  - http://d.hatena.ne.jp/simezi_tan/20140516/1400225006
   - solving by flow 🤔
 
 Key:
  - Need deep observation
 
 Summary:
  - I completed analysis by going through many samples manually
  - In implementation, it took time to find missing analysis of sample 3 case.
 
 */
class SurveillanceSystem {
  public:
  int L;
  string C;
  SETI search(int T) {
    SETI res;
    REP(i,SZ(C)-L+1) {
      int cnt=0;
      REP(j,L) cnt+=C[i+j]=='X';
      if(cnt==T) res.emplace(i);
    }
    return res;
  }
  string getContainerInfo(string C, vector<int> R, int L) {
    this->C=C;
    this->L=L;
    int N=SZ(C);
    string res(N,'-');
    MAPII cnt;
    unordered_map<int, SETI> ps;
    
    FORR(m,R) cnt[m]++;
    FORR(kvp,cnt) ps[kvp.first]=search(kvp.first);
    
    FORR(kvp,cnt) {
      int cnt2=kvp.second;
      SETI ps2=ps[kvp.first];

      VI xs(N,0);
      FORR(s,ps2) {
        FOR(i,s,s+L) xs[i]++;
      }
      REP(i,N) {
        if(xs[i]>=SZ(ps2)-cnt2+1) res[i]='+';
        else if(res[i]!='+'&&xs[i]>0) res[i]='?';
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("SurveillanceSystem.sample");

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

bool do_test(string containers, vector<int> reports, int L, string __expected) {
    time_t startClock = clock();
    SurveillanceSystem *instance = new SurveillanceSystem();
    string __result = instance->getContainerInfo(containers, reports, L);
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
        string containers;
        from_stream(containers);
        vector<int> reports;
        from_stream(reports);
        int L;
        from_stream(L);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(containers, reports, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512059099;
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
        cout << "SurveillanceSystem (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
