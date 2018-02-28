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
 
 2/26/2018
 
 22:07-22:55 ACC (394.49 pt)
 
 Finding A and B from C is expensive.
 I tried to iterate A and B.
 I also found convex downward property when A is fixed.
 Without proof, I iterated A in [1,10^6] with ternary search.
 
 2/27/2018
 
 18:20-20:22 read editorials
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+522
   - loose bound and tight bound
  - https://topcoder.g.hatena.ne.jp/namakemono_srm/20111027/1319681223
   - tight bound
  - http://d.hatena.ne.jp/kusano_prog/20111027/1319747239
   - loose and simple bound
  - http://area.hateblo.jp/entry/2013/09/14/203912
   - tight bound
  - https://topcoder.g.hatena.ne.jp/firewood/20111027/1319732512
 
 smallest (A,B,C) s.t. A*B=C is (1,1,1)
 Thus f(A,B,C) = abs(A-a)+abs(B-b)+abs(C-c) (s.t. A*B=C) is at most abs(1-a)+abs(1-b)+abs(1-c)= a+b+c-3<3e6-3
 
 Let's put M=a+b+c-3<=3e6-3
 We want to know upper bound of A.
 
 abs(A-a)<=abs(A-a)+abs(B-b)+abs(C-c)<=3e6-3
 abs(A-a)<=M
 A is largest when A-a>=0. A-a<=M => A<=a+M<=4e6-3
 
 Solution 1 (loose bound):
 
 We can iterate A in [1..a+M].
 
 f'(B,C)=abs(A-a)+abs(B-b)+abs(C-c)<=3e6-3
 => abs(B-b)+abs(C-c)<=3e6-3-abs(A-a)
 => abs(B-b)<=3e6-3-abs(A-a)
 => B<=M-abs(A-a)+b
 
 Now we know B's upperbound when A is fixed.
 We can iterate B in [1..M-abs(A-a)+b]. Also at the same time A*B=C should hold.
 C's upper-bound is M-abs(A-a)-abs(B-b)+c with the same analysis.
 If A*B>M-abs(A-a)-abs(B-b)+c, we can stop B's iteration.
 
 B<=(M-abs(A-a)-abs(B-b)+c)/A. This is upper-bounded by O(1/M)
 The total runtime is ∑ { M/k : k=1..M } = O(M*ln M) (Harmonic series) <5*10^7
 
 Solution 2 (tight bound):
 
 Actually more tight bound can be found.
 Suppose A is fixed as well by iterating in [1..a+M].
 
 Also f'(B,C)=abs(B-b)+abs(C-c)
 Let's put X=B-b, Y=C-c. Then f'(X,Y)=abs(X)+abs(Y)
 We want to minimize abs(X) and abs(Y)
 
 X=B-b <=> B=X+b
 Y=C-c <=> C=Y+c
 
 A*B=C <=> A*(X+b)=Y+c
 
 Let's take sample 0 to understand the behavior of X and Y
 a=19, b=28, c=522 in sample 0. Suppose A = 29 (arbitrary number works to research behavior).
 
 A*(X+b)=Y+c => 29*(X+28)=Y+522
 
 Let's try B=1,2,..
 
 (B,  X), ( C,   Y), abs(X)+abs(Y)
-------------------------------------
  1,-27    29,-493            520
  2,-26    58,-464            490
  ..
 18,-10    522,  0             10
  ..
 28,  0    812,290            290
 
 We want to minimize abs(X) and abs(Y). In what (X,Y), abs(X)+abs(Y) is minimal?
 For A=29, abs(X)+abs(Y) is minimal as seen above.
 
 Graph: http://www.wolframalpha.com/input/?i=abs(x-28)%2Babs(29*x-522)

 The point is that when B and X increases by 1, Y increases by 29 (=A).
 Moreover abs(X)+abs(Y) decreases by 30.
 Thus if we can find B s.t. Y is as close to 0 as possible, that should be optimal solution.
 If we see graph of f1(B)=abs(B-b) and f2(B)=abs(A*B-c), f2(B) contributes more in f1(B)+f2(B).
 So we can find B s.t. A*B-c=0 => B=c/A
 B could be a real number. We should try A/c+1 as well.
 
 Key:
  - A can be upper-bounded by finding extreme case (A,B,C)=(1,1,1)
  - Possible B can be limited by analyzing formula
 
 Summary:
  - No proof of range of A is evil 👎
  - Finding extreme exmaple which satisfies the constraint is nice to give some upper-bound
  - Put different variable name to find new property (X=B-b in this problem)
  - Try sample to figure out when value can be minimal
   - In this problem, it's when B=c/A
   - Show that necessary condition (special extreme case) is sufficient
 
 */

class CorrectMultiplicationTwo {
public:
  int getMinimum(int a, int b, int c) {
    int M=a+b+c;
    int res=M;
    FORE(A,1,a+M) {
      for(int B=c/A; B<=c/A+1; ++B) if(B>0) {
        SMIN(res,abs(A-a)+abs(B-b)+abs(A*B-c));
      }
    }
    return res;
  }
};

class CorrectMultiplicationTwo_loose {
public:
  int getMinimum(int a, int b, int c) {
    int M=a+b+c;
    int res=M;
    FORE(A,1,a+M) FORE(B,1,M-abs(A-a)+b) {
      LL C=A*B;
      if(C>M-abs(A-a)-abs(B-b)+c) break;
      SMIN(res,abs(A-a)+abs(B-b)+abs((int)C-c));
    }
    return res;
  }
};

class CorrectMultiplicationTwo_org {
  public:
  LL a,b,c;
  LL score(LL A, LL B) {
    LL C=A*B;
    return abs(C-c)+abs(B-b)+abs(A-a);
  }
  LL g(LL A) {
    int l=1,r=1e9;
    while(abs(r-l)>2) {
      int ll=l+(r-l)/3;
      int rr=r-(r-l)/3;
      if(score(A,ll)<score(A,rr)) r=rr;
      else l=ll;
    }
    if(A==18) {
//      dump(score(18,29));
//      dump4(l,score(A,l),r,score(A,r));
    }
    return min({score(A,l),score(A,l+1),score(A,r)});
  }
  LL f() {
    LL res=1e9;
    FORE(n,1,1e6) {
      if(res>g(n)) dump2(n,g(n));
      res=min(res,g(n));
    }
//    dump(g(18));
    return res;
  }
  int getMinimum(int a, int b, int c) {
    this->a=a,this->b=b,this->c=c;
    return f();
  }
};

// CUT begin
ifstream data("CorrectMultiplicationTwo.sample");

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

bool do_test(int a, int b, int c, int __expected) {
    time_t startClock = clock();
    CorrectMultiplicationTwo *instance = new CorrectMultiplicationTwo();
    int __result = instance->getMinimum(a, b, c);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, c, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519711664;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CorrectMultiplicationTwo (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
