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
 
 1/29/2018
 
 8:51-8:57 analysis
 8:58-9:33 implement and submit (234.18 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+543
    - math
  - http://d.hatena.ne.jp/komiyam/20120520/1337454736
    - math
  - https://topcoder.g.hatena.ne.jp/firewood/20120526/1338037995
    - math
  - http://www.vexorian.com/2012/05/topcoder-srm-543.html
    - bit-wise count
  - http://d.hatena.ne.jp/kusano_prog/20120519/1337457937
    - bit-wise count
  - http://mayokoex.hatenablog.com/entry/2016/04/22/235235
    - bit-wise count
  - http://topcoder.g.hatena.ne.jp/jackpersel/20120520/1337509799
    - bit-wise count
  - http://topcoder.g.hatena.ne.jp/kojingharang/20120519#1337452838
  - http://topcoder.g.hatena.ne.jp/agw/20120524/1337835652
 
 Property of XOR of continuous numbers
 
 Suppose we want to xor 2*n, 2*n+1, 2*n+2, 2*n+3.
 
 2*n   = *****0
 2*n+1 = *****1
 
 (2*n)^(2*n+1) = 000001
 // Same numbers are set to 0 in xor operation like 0^0=0, 1^1=0

 Similarly...
 
 2*n+2 = #####0
 2*n+3 = #####1

 (2*n+2)^(2*n+3) = 000001

   (2*n)^(2*n+1)^(2*n+2)^(2*n+3)
 = 000001^000001
 = 000000
 
 Thus we can focus on N mod 4 to figure out 0^1^...^N
 
 a) N%4==0
  => f(N) = 0^N=N
 b) N%4==1
  => f(N) = (N-1)^N=1
 c) N%4==2
  => f(N) = (N-2)^(N-1)^N=N+1 // because N is even
 3) N%4==3
  => f(N) = (N-3)^(N-2)^(N-1)^N=N^N=0
 
 Summary:
  - Too slow implementation 👎
    - it took long time to debug and fix counter helper 👎👎
  - Editorial O(1) solution is impressive!
    - I learned something new about XOR again
 
 */

class EllysXors {
public:
  LL f(LL N) {
    if(N%4==0) return N;
    if(N%4==1) return 1;
    if(N%4==2) return N+1;
    return 0;
  }
  long long getXor(long long L, long long R) {
    return f(L-1)^f(R);
  }
};

class EllysXors_org {
  public:
  LL count(LL A, int i) {
//    if(i==32) return (A&(1LL<<32))!=0;
    ++A;
    LL cycle=A/(1LL<<(i+1));
    dump3(A,i,cycle);
    LL res=cycle*(1LL<<i);
    A-=cycle*(1LL<<(i+1));
    dump2(res,A);
    res+=max(0LL,A-(1LL<<i));
    return res;
  }
  long long getXor(long long L, long long R) {
    --L;
    LL res=0;
    REPE(i,31) {
//      count(R,i);
      int c1=count(L,i),c2=count(R,i);
//      int c1=1,c2=2;
      LL x=(c2-c1)&1; // or c1^c2 (`xor` takes diff)
      dump4(i,c1,c2,x);
      res|=x<<i;
      dump(res);
    }
    return res;
  }
};

// CUT begin
ifstream data("EllysXors.sample");

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

bool do_test(long long L, long long R, long long __expected) {
    time_t startClock = clock();
    EllysXors *instance = new EllysXors();
    long long __result = instance->getXor(L, R);
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
        long long L;
        from_stream(L);
        long long R;
        from_stream(R);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517244689;
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
        cout << "EllysXors (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
