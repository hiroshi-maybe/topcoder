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
 
 9/15/2018
 
 16:20-16:49 AC (144.27 pt)
 
 http://apps.topcoder.com/wiki/display/tc/SRM+459
 Coordinate expansion and brute-force possible positions in editorial.
 I've figured out that brute-force works before starting imos.
 I should have compared those approaches to choose more appropriate one.
 Also I didn't come up with coordinate expansion. That's bad point.
 
 */

class Inequalities {
public:
  int maximumSubset(vector<string> X) {
    int N=SZ(X);
    vector<pair<int,string>> XX(N);
    REP(i,N) {
      string s=X[i];
      stringstream ss(s);
      string _,ie; int n; ss>>_>>ie>>n;
      XX[i]={2*n,ie};
    }
    int res=0;
    FORE(p,-1,2002) {
      int cnt=0;
      REP(i,N) {
        string ie; int n; tie(n,ie)=XX[i];
        if(ie=="=") cnt+=n==p;
        if(ie==">") cnt+=p>n;
        if(ie=="<") cnt+=p<n;
        if(ie==">=") cnt+=p>=n;
        if(ie=="<=") cnt+=p<=n;
      }
      SMAX(res,cnt);
    }
    
    return res;
  }
};

class Inequalities_org {
  public:
  int maximumSubset(vector<string> X) {
    int N=SZ(X);
    map<double,int> imos;
    REP(i,N) {
      string s=X[i];
      stringstream ss(s);
      string _,ie; int n; ss>>_>>ie>>n;
      double l=-1,r=1e4;
      if(ie=="=") l=n,r=n+0.1;
      if(ie==">=") l=n;
      if(ie==">") l=n+0.2;
      if(ie=="<=") r=n+0.1;
      if(ie=="<") r=n;
      imos[l]++;
      imos[r]--;
//      dump2(l,r);
    }
    int res=0;
    int cnt=0;
    FORR(kvp,imos) {
      cnt+=kvp.second,SMAX(res,cnt);
//      dump3(kvp.first,kvp.second,cnt);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("Inequalities.sample");

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

bool do_test(vector<string> inequalities, int __expected) {
    time_t startClock = clock();
    Inequalities *instance = new Inequalities();
    int __result = instance->maximumSubset(inequalities);
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
        vector<string> inequalities;
        from_stream(inequalities);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(inequalities, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1537053595;
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
        cout << "Inequalities (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
