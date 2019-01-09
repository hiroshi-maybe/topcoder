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
 
 2/6/2018
 
 8:56-9:13 Analysis
 9:14-9:29 found some bugs during implementation thoguh, submit and got ACC (295.18 pt)
 
 p*A+q*B = s*X+t*Y must be satisfied
 
 1) What is necessary condition?
 
 s*X+t*Y needs to represent A(p=1,q=0) and B(p=0,p=q) as well.
 
 So at least a1*X+b1*Y = A AND a2*X+b2*Y = B need to be satisfied.
 This is "necessary" condition.
 
 2) Is necessary condition sufficient?
 
 As seen in necessary condition, A and B is necessarily represented as below:
 
 A = a1*X+b1*Y .. 👹
 B = a2*X+b2*Y .. 👺
 
 We want to show that this is sufficient to represent numbers { p*A+q*B : p>=0, q>=0 }
 
   p*A+q*B
 = p*(a1*X+b1*Y) + q*(a2*X+b2*Y)
 = (p*a1+q*a2)*X + (p*b1+q*b2)*Y
 
 => s=p*a1+q*a2, t=p*b1+q*b2
 
 This means that 👹 and 👺 are sufficient condition.
 
 3) Iterate possible Ys
 We can brute-force Y and test if A = a1*X+b1*Y AND B = a2*X+b2*Y hold
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+537
  - http://apps.topcoder.com/forums/?module=Thread&threadID=740074
  - http://mayokoex.hatenablog.com/entry/2016/03/28/122653
  - http://sk765.blogspot.com/2012/03/topcoder-srm-537.html
  - http://kg86.hatenablog.com/entry/20130413/1365870989
  - http://d.hatena.ne.jp/komiyam/20120318/1332077147
  - https://chngng.blogspot.jp/2015/05/srm-537-div1-easy-kingxnewcurrency.html?m=1
  - http://lepton.hatenablog.jp/entry/20120317/1332015428
  - http://topcoder.g.hatena.ne.jp/agw/20120318/1332137709
  - http://topcoder.g.hatena.ne.jp/jackpersel/20120317/1332010642
  - http://naoyat.hatenablog.jp/entry/SRM537
 
 Key:
  - Necessary condition A = a1*X+b1*Y and B = a2*X+b2*Y are sufficient
  - Brute-force possible `Y`
 
 Summary:
  - Proof described in the forum was great help to understand how to find valid analysis
   - Finding a special case may be a good start to find a necessary AND sufficient condition
   - Necessary condition is usually a special case of generic condition that we want to prove
   - If we can prove that the necessary condition satisfies generic case, it's sufficient
   - We are confident about the correctness
  - Upper-bound of A,B is small. I went through brute-force approach.
 
 */
class KingXNewCurrency {
  public:
  bool ok(int A, int X, int Y) {
    if(A%X==0) return true;
    if(A%Y==0) return true;

    int a=A;
    while(a>0) {
      if(a%Y==0) return true;
      a-=X;
    }
    a=A;
    while(a>0) {
      if(a%X==0) return true;
      a-=Y;
    }
    return false;
  }
  int howMany(int A, int B, int X) {
    if(A%X==0&&B%X==0) return -1;
    int res=0;
    FORE(Y,1,200) if(X!=Y) {
      bool good=true;
      good&=ok(A,X,Y);
      good&=ok(B,X,Y);
      res+=good;
      if(good) dump(Y);
    }
    return res;
  }
};

// CUT begin
ifstream data("KingXNewCurrency.sample");

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

bool do_test(int A, int B, int X, int __expected) {
    time_t startClock = clock();
    KingXNewCurrency *instance = new KingXNewCurrency();
    int __result = instance->howMany(A, B, X);
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        int X;
        from_stream(X);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517936155;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "KingXNewCurrency (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
