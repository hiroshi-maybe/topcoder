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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/12/2018
 
 8:34-8:44 analysis
 8:45-9:13 Submit after keeping implementation and debug (291.42 pt). However system test didn't pass.
 System test passed after some work around
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+532
  - http://www.vexorian.com/2012/02/srm-532-easy-problems-can-be-evil.html
  - https://chngng.blogspot.com/2013/09/srm-532-div1-easy-dengklekmakingchains.html
  - http://topcoder.g.hatena.ne.jp/firewood/20120223/1330012087
  - http://mayokoex.hatenablog.com/entry/2016/02/17/151537
  - http://naoyat.hatenablog.jp/category/TopCoder?page=1329670158
 
 Summary:
  - There were a lot of annoying corner cases.
 
 */
class DengklekMakingChains {
  public:
  int score(char c) { return c=='.'?0:c-'0'; }
  int score(string s) {
    if(s[1]=='.') {
      return max(score(s[0]),score(s[2]));
    } else {
      return score(s[0])+score(s[1])+score(s[2]);
    }
  }
  bool full(string s) {
    return count(s.begin(),s.end(),'.')==0;
  }
  int lscore(string s) {
    int x=0;
    for(int i=0; i<2&&s[i]!='.'; ++i) x+=score(s[i]);
    return x;
  }
  int rscore(string s) {
    int x=0;
    for(int i=2; i>=0&&s[i]!='.'; --i) x+=score(s[i]);
    return x;
  }
  int maxBeauty(vector<string> A) {
    int res=0;
    int N=SZ(A);
    FORR(s,A) SMAX(res,score(s));
    
//    dump(res);

    int lmax=0,rmax=0;
    int sum=0;
    vector<string> X;
    REP(i,N) {
      string s=A[i];
      if(full(s)) sum+=score(s);
      else X.push_back(s);
    }
    X.push_back("...");
    
    int smax=0;
    dumpAR(X);
    REP(i,SZ(X)) REP(j,SZ(X)) if(i!=j) {
      string L=X[i],R=X[j];
      int lmaxx=max(lmax,rscore(L));
      int rmaxx=max(rmax,lscore(R));
      SMAX(smax,lmaxx+rmaxx);
    }
    dump2(sum,smax);
    return max(res,sum+smax);
  }
};

// CUT begin
ifstream data("DengklekMakingChains.sample");

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

bool do_test(vector<string> chains, int __expected) {
    time_t startClock = clock();
    DengklekMakingChains *instance = new DengklekMakingChains();
    int __result = instance->maxBeauty(chains);
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
        vector<string> chains;
        from_stream(chains);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(chains, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1518453261;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DengklekMakingChains (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
