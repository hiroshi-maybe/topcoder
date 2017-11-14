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
 
 11/13/2017
 
 8:30-8:51 system test passed (348.59 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+589
   - greedy
  - http://snuke.hatenablog.com/entry/2013/08/27/214629
   - greedy (problem writer)
  - http://kmjp.hatenablog.jp/entry/2013/08/28/1000
   - dp
  - http://torus711.hatenablog.com/entry/20130827/p3
   - we can keep at least one gear. we can brute force it
 
 First one is affected by tail. So resolving it first makes problem easier.
 
 We have two cases:
  1. head!=tail
   => leave head and tail
  2. head==tail
   => try both of below two cases and pick up minimal one
   i) remove head
   ii) remove tail
 
 After resolving head, we want to make optimal choice.
 
 Suppose we are solving f(i) where i is index of suffix that we are solving.
 
 1) remove i+1
  D[i..] = LLLR
            ^
 2) remove i
  D[i..] = LLLR
           ^
 
 In case 1) we can solve subproblem f(i+2) while f(i+1) needs to be solved in case 2).
 Thus choosing second one in conflict makes smaller subproblem which does not make worse choice.
 
 Key:
  - Head is dependent on tail. Trying possible cases gives us a problem with optimal substructure property
 
 Summary:
  - I thought there would be some greedy solution though, selected DP to go safely
  - Nice problem to practice greedy as well
 
 */

// greedy, O(N) time
class GearsDiv2 {
public:
  int N;
  int f(int i, string &S) {
    if(i>=SZ(S)-1) return 0;
    return S[i]==S[i+1]?1+f(i+2,S):f(i+1,S);
  }
  int getmin(string D) {
    this->N=SZ(D);
    if(D[0]!=D[N-1]) return f(0,D);
    string s1=D.substr(1),s2=D.substr(0,N-1);
    return 1+min(f(0,s1), f(0,s2));
  }
};

// dp, O(N) time
int memo[51][2];
class GearsDiv2_dp {
  public:
  string D;
  int st=0;
  int f(int i, int dir) {
    int &res=memo[i][dir];
    char c=dir?'L':'R';
    if(i==SZ(D)) return res=(dir==st?0:1);
    if(res>=0) return res;
    if(D[i]==c) return res=f(i+1,!dir);
    return res=1+min(f(i+1,0),f(i+1,1));
  }
  int getmin(string D) {
    this->D=D;
    int res=51;
    for(;st<2; st++) {
      MINUS(memo);
      res=min(res,f(0,st));
    }
    return res;
  }
};

// CUT begin
ifstream data("GearsDiv2.sample");

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

bool do_test(string Directions, int __expected) {
    time_t startClock = clock();
    GearsDiv2 *instance = new GearsDiv2();
    int __result = instance->getmin(Directions);
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
        string Directions;
        from_stream(Directions);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(Directions, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510590632;
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
        cout << "GearsDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
