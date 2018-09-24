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
 
 9/24/2018
 
 12:46-13:30 give up
 14:50-15:36 read editorial and add solution
 
 http://apps.topcoder.com/wiki/display/tc/SRM+467
 
 Key:
  - Process cycle in one loop block
  - If interval matters in cycles, compute in global interval
  - Analyze interval carefully focusing on infinitesimal if real value is the scope
 
 Summary:
  - Transform to cycle local problem. This is second time to fail to solve such problem 😡😡
  - @yutaka1999's solution is beautiful in division summary
   - we can move time by only checking right most time
   - min/max check to compute start time and end time works in every interval
 
 */

class LateProfessor {
public:
  double getProbability(int A, int B, int C, int L, int R) {
    int D=A+B-C;
    if(D<=A) return 0.0;
    int t=0;
    if(L==R) {
      while(t<=R) {
        if(t+A<R&&R<=t+D) return 1.0;
        t+=A+B;
      }
      return 0;
    } else {
      int res=0;
      while(t<=R) {
        int l=max(t+A,L),r=min(t+D,R);
        res+=max(0,r-l);
        t+=A+B;
      }
      return 1.0*res/(R-L);
    }
  }
};

class LateProfessor_org {
public:
  double getProbability(int A, int B, int C, int L, int R) {
    int D=A+B-C;
    if(D<=A) return 0.0;
    int t=0;
    int res=0;
    if(L==R) {
      while(!(t<=L&&L<t+A+B)) t+=A+B;
      int tt=L-t;
      return A<tt&&tt<=D?1.0:0.0;
    } else {
      while(!(t<=L&&L<t+A+B)) t+=A+B;
      int LL=L-t,RR=R-t;
      res+=max(0,min(RR,D)-max(A,LL));
      if(t<=R&&R<t+A+B) return 1.0*res/(R-L);
      t+=A+B;
      while(!(t<=R&&R<t+A+B)) t+=A+B,res+=D-A;
      RR=R-t;
      res+=max(0,min(RR,D)-A);
      return 1.0*res/(R-L);
    }
  }
};

const int MAX_N=2e7;
bool T[MAX_N+10];
class LateProfessor_wrong {
  public:
  double getProbability(int A, int B, int C, int L, int R) {
    ZERO(T);
    for(int p=0; p*(A+B)<=2e7; ++p) {
      int t0=p*(A+B);
      for(int t=t0; t<=R&&t<=t0+A; ++t) T[t]=true;
      for(int t=t0; t0-t<C&&t>=0; --t) T[t]=true;
    }
    REPE(i,R) cout<<T[i];
    cout<<endl;
    
    int cnt=0;
    FORE(t,L,R) cnt+=T[t]==0;
    if(L==R) return cnt;
    return (double)cnt/(R-L);
  }
};

// CUT begin
ifstream data("LateProfessor.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int waitTime, int walkTime, int lateTime, int bestArrival, int worstArrival, double __expected) {
    time_t startClock = clock();
    LateProfessor *instance = new LateProfessor();
    double __result = instance->getProbability(waitTime, walkTime, lateTime, bestArrival, worstArrival);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int waitTime;
        from_stream(waitTime);
        int walkTime;
        from_stream(walkTime);
        int lateTime;
        from_stream(lateTime);
        int bestArrival;
        from_stream(bestArrival);
        int worstArrival;
        from_stream(worstArrival);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(waitTime, walkTime, lateTime, bestArrival, worstArrival, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1537818384;
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
        cout << "LateProfessor (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
