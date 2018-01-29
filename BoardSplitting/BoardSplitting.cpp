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
 
 1/28/2018
 
 15:43-16:43 Submit (197.37 pt) but 1WA
 16:44-17:20 Implement just simulation and system test passed.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+544
   - brute-force alignment
   - fixed alignment (my solution) with proof 👍
   - lcm
  - http://kg86.hatenablog.com/entry/20130813/1376369706
   - fixed alighment
  - http://topcoder.g.hatena.ne.jp/agw/20120531/1338442369
   - fixed alighment
 
 Solution by gcd:
  - https://community.topcoder.com/stat?c=problem_solution&rm=313151&rd=14736&pm=11951&cr=23050704
 Solution by lcm:
  - https://community.topcoder.com/stat?c=problem_solution&rm=313116&rd=14736&pm=11951&cr=22831394
 
 Summary:
  - I had no proof about my simulation
  - This was much harder than div2 hard AliceBobShuffle
  - If `C` items of length `L` is needed, reducing problem to fill single large `L`*`C` bar may be a good start to solve
  - I missed this description "The construction company wants to use as few boards as possible" 😡😡😡😡
   - I was solving more difficult problem 😵
 
 */

class BoardSplitting {
public:
  int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }
  int lcm(int a, int b) { return a*b/gcd(a,b); }
  int minimumCuts(int L1, int C, int L2) {
    int l=lcm(L1,L2);
    int n=L1*C/l;
    int a=n*(l/L1-1);
    int b=(L1*C-n*l)/L1;
    return a+b;
  }
};

// brute-force alighment, O(L1*C) time
class BoardSplitting_bruteforce {
public:
  int minimumCuts(int L1, int C, int L2) {
    int cnt=(L1*C+L2-1)/L2;
    
    int res=1e4;
    for(int offset=0; offset<L2&&cnt*L2-offset>=L1*C; ++offset) {
      int x=offset==0?0:1;
      int rem=offset;
      int c=0;
      while(c++<C) {
        while(rem<L1) rem+=L2;
        rem-=L1;
        if(rem!=0) ++x;
      }
      res=min(res,x);
    }
    return res;
  }
};

class BoardSplitting_org {
  public:
  int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }
  int minimumCuts(int L1, int C, int L2) {
    int LL=L1%L2;
    if(LL==0) return 0;
    if(L2%LL==0) {
      int p=L2/LL;
      int a=C/p,b=C%p;
      return a*(p-1)+b;
    }
    int res=0;
    int cur=0;
    while(C--) {
      while(cur<L1) cur+=L2;
      cur-=L1;
      if(cur!=0) ++res;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("BoardSplitting.sample");

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

bool do_test(int desiredLength, int desiredCount, int actualLength, int __expected) {
    time_t startClock = clock();
    BoardSplitting *instance = new BoardSplitting();
    int __result = instance->minimumCuts(desiredLength, desiredCount, actualLength);
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
        int desiredLength;
        from_stream(desiredLength);
        int desiredCount;
        from_stream(desiredCount);
        int actualLength;
        from_stream(actualLength);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(desiredLength, desiredCount, actualLength, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517182998;
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
        cout << "BoardSplitting (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
