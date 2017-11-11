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
 
 11/10/2017
 
 8:28-8:38 analysis
 8:38-8:43 1WA (390.86 pt)
 9:45-9:49 ACC
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+591
  - http://kmjp.hatenablog.jp/entry/2013/09/22/0930
  - http://torus711.hatenablog.com/entry/20130917/p2
  - https://topcoder.g.hatena.ne.jp/firewood/20131130/1385828062
 
 Summary:
  - I forgot constraint of permutation and hit 1WA.
  - Analysis of div2 medium is getting faster though, sometimes missing some constraint
  - Pay more attention even when analysis is strightforward
 
 */
class ConvertibleStrings {
public:
  int leastRemovals(string A, string B) {
    int N=SZ(A);
    int res=100;
    vector<int> T(9,0);
    REP(i,9) T[i]=i;
    do {
      int x=0;
      REP(i,N) x+=T[A[i]-'A']!=B[i]-'A';
      res=min(x,res);
    } while(next_permutation(T.begin(),T.end()));
    return res;
  }
};

class ConvertibleStrings_wrong {
  public:
  int leastRemovals(string A, string B) {
    vector<VI> mx(9,VI(9,0));
    int N=SZ(A);
    REP(i,N) {
      mx[A[i]-'A'][B[i]-'A']++;
    }
    int res=0;
    REP(i,9) {
      int sum=accumulate(mx[i].begin(),mx[i].end(),0);
      int maxm=*max_element(mx[i].begin(),mx[i].end());
//      dumpAR(mx[i]);
//      dump3(i,sum,maxm);
      res+=sum-maxm;
    }
    return res;
  }
};

// CUT begin
ifstream data("ConvertibleStrings.sample");

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

bool do_test(string A, string B, int __expected) {
    time_t startClock = clock();
    ConvertibleStrings *instance = new ConvertibleStrings();
    int __result = instance->leastRemovals(A, B);
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
        string A;
        from_stream(A);
        string B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510331279;
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
        cout << "ConvertibleStrings (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
