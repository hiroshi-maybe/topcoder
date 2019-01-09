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
 
 12/25/2017
 
 16:51-17:07 system test passed (383.92 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+564
  - http://d.hatena.ne.jp/kusano_prog/20121212/1355329355
  - http://kmjp.hatenablog.jp/entry/2012/12/13/0930
  - http://pushl.hatenablog.com/entry/2012/12/13/035805
  - http://purple-jwl.hatenablog.com/entry/20130202/1359800609
 
 Summary:
  - Very straighforward problem
  - I was wondering if I may be missing some corner case though, I got ACC with no WA.
 
 */
class AlternateColors {
  public:
  string C0="RED",C1="GREEN",C2= "BLUE";
  string getColor(long long R, long long G, long long B, long long K) {
    --K;
    vector<string> CC={C0,C1,C2};
    vector<LL> ns={R,G,B};
    LL n3=*min_element(ns.begin(),ns.end());
    if(3LL*n3>K) return CC[K%3];
    REP(i,3) ns[i]-=n3; K-=3LL*n3;
    
    vector<string> CC1;
    vector<LL> ns1;
    REP(i,3) if(ns[i]>0) {
      CC1.push_back(CC[i]);
      ns1.push_back(ns[i]);
    }
    
    if(SZ(ns1)==1) return CC1.front();
    
    LL n2=*min_element(ns1.begin(),ns1.end());
    if(2LL*n2>K) return CC1[K%2];
    
    return ns1[0]>ns1[1]?CC1[0]:CC1[1];
  }
};

// CUT begin
ifstream data("AlternateColors.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(long long r, long long g, long long b, long long k, string __expected) {
    time_t startClock = clock();
    AlternateColors *instance = new AlternateColors();
    string __result = instance->getColor(r, g, b, k);
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
        long long r;
        from_stream(r);
        long long g;
        from_stream(g);
        long long b;
        from_stream(b);
        long long k;
        from_stream(k);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(r, g, b, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514249483;
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
        cout << "AlternateColors (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
