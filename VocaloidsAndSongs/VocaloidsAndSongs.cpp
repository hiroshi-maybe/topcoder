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
 
 10/18/2017
 
 8:48-9:00 system test passed (812.90 pt)

 editorial:
  - http://kmjp.hatenablog.jp/entry/2014/02/16/1000
  - https://apps.topcoder.com/wiki/display/tc/SRM+609
 
 summary:
  - typical DP
 
 submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=320688&rd=15842&pm=12989&cr=23281422
  - https://community.topcoder.com/stat?c=problem_solution&rm=320698&rd=15842&pm=12989&cr=22718397
  - https://community.topcoder.com/stat?c=problem_solution&rm=320683&rd=15842&pm=12989&cr=22910860
  - https://community.topcoder.com/stat?c=problem_solution&rm=320721&rd=15842&pm=12989&cr=23027795
   - all DP
 
 */

// O(N^4) time
constexpr int MOD = 1e9+7;
LL memo[51][51][51][51];
class VocaloidsAndSongs {
  public:
  LL f(int i, int n0, int n1, int n2) {
    if(i==0) {
      if(n0==0&&n1==0&&n2==0) return 1;
      else return 0;
    }
    if(memo[i][n0][n1][n2]>=0) return memo[i][n0][n1][n2];
    
    LL res=0;
    FOR(mask,1,8) {
      int nn0=n0,nn1=n1,nn2=n2;
      if(mask&1) nn0-=1;
      if(mask&2) nn1-=1;
      if(mask&4) nn2-=1;
      if(nn0<0||nn1<0||nn2<0) continue;
      res+=f(i-1,nn0,nn1,nn2),res%=MOD;
    }
    return memo[i][n0][n1][n2]=res;
  }
  int count(int N, int n0, int n1, int n2) {
    MINUS(memo);
    return f(N,n0,n1,n2);
  }
};

// CUT begin
ifstream data("VocaloidsAndSongs.sample");

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

bool do_test(int S, int gumi, int ia, int mayu, int __expected) {
    time_t startClock = clock();
    VocaloidsAndSongs *instance = new VocaloidsAndSongs();
    int __result = instance->count(S, gumi, ia, mayu);
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
        int S;
        from_stream(S);
        int gumi;
        from_stream(gumi);
        int ia;
        from_stream(ia);
        int mayu;
        from_stream(mayu);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, gumi, ia, mayu, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508341682;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "VocaloidsAndSongs (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
