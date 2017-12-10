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
 
 12/9/2017
 
 17:24-17:45 analysis
 17:45-17:59 implement and submit (no compile error, no sample error) (259.57 pt)

 Editorial:
  - http://kmjp.hatenablog.jp/entry/2017/11/30/0900
  - https://docs.google.com/document/d/1yFqC0B99vM8hXjzuFJTQYxY8-FF5KEBDWV3dKHkwB60/edit

 SUM - OR shows columns where carry happens. That is actually result of AND manipulation.
 Thus we can say below:
 
 SUM - OR = AND
 (A+B) - A|B = A&B
 
 1. O(1) solution
 
 If A&B<0, false
 If (A&B)|(A|B) != A|B, false // carry never happens if there is no 1 bit
 Otherwise true
 
 2. O(log10 N) solution
 
 We get A&B from A+B and A|B.
 A|B and A&B must be one of below combinations:
 
 A B A&B A|B
 0,0   0   0
 0,1   0   1
 1,0   0   1
 1,1   1   1
 
 If there is a bit which violates above, impossible
 
 Key:
  - DP or adhoc solution
  - In div1 easy, DP doesn't work.
 
 Summary:
  - solved by DP
 
 O(1) solution:
  - https://community.topcoder.com/stat?c=problem_solution&rm=330750&rd=17033&pm=14745&cr=267465
 
 I don't have a proof why this is sufficient and necessary
 
 Summary:
  - If it's hard to brute-force all the cases, it may be useful to reduce possible combinations to limited set
   - In this case we cannot try 2^61 binary patters
   - However we can analyze result of possible combinations (0,0),(1,0),(0,1),(1,1)
 
 */

// O(log10 N)
class OrAndSumEasy {
public:
  string yes="Possible",no="Impossible";
  string isPossible(long long O, long long S) {
    LL A=S-O;
    REP(i,61) {
      int o=(O>>i)&1,a=(A>>i)&1;
      if (o==0&&a==0) continue;
      if (o==1&&a==0) continue;
      if (o==1&&a==1) continue;
      
      return no;
    }
    return yes;
  }
};

// O(1)
class OrAndSumEasy_o1 {
public:
  string yes="Possible",no="Impossible";
  string isPossible(long long O, long long S) {
    LL A=S-O;
    if(A<0) return no;
    if((A|O)!=O) return no;
    return yes;
  }
};

int memo[64][2][2][2];
class OrAndSumEasy_dp {
  public:
  LL O,S;
  string yes="Possible",no="Impossible";
  int f(int i, int a, int b, int c) {
    int &res=memo[i][a][b][c];
    if(res>=0) return res;
    if(i==63) return res=(a==0&&b==0&&c==0);
    
    int orx=a|b,sumx=a+b+c;
    if(orx!=((O>>i)&1)) return res=false;
    if((sumx&1)!=((S>>i)&1)) return res=false;
    
    int cc=(sumx&2)>0;
    res=false;
    REP(aa,2)REP(bb,2) res|=f(i+1,aa,bb,cc);
    return res;
  }
  string isPossible(long long O, long long S) {
    this->O=O,this->S=S;
    bool res=false;
    MINUS(memo);
    REP(i,2)REP(j,2) res|=f(0,i,j,0);
    return res?yes:no;
  }
};

// CUT begin
ifstream data("OrAndSumEasy.sample");

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

bool do_test(long long pairOr, long long pairSum, string __expected) {
    time_t startClock = clock();
    OrAndSumEasy *instance = new OrAndSumEasy();
    string __result = instance->isPossible(pairOr, pairSum);
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
        long long pairOr;
        from_stream(pairOr);
        long long pairSum;
        from_stream(pairSum);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(pairOr, pairSum, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512869083;
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
        cout << "OrAndSumEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
