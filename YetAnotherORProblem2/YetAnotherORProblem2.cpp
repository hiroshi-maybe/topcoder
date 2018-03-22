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
 
 3/20/2018
 
 8:43-9:30 pause
 18:30-19:29 submit and ACC
 
 It took more than 30 mins to figure out disjoint property of ON bits.
 ∑ A[i] = | A[i] => ON bits in A[i] should be disjoint because carry would break the equality
 
 On top of this most important property, there were some steps to get it solved
 1. Possible maximum number of ∑ A[i] != R
 2. We need to satisfy A[i]<=R
 3. How to enumerate A[i]
 
 Even after figuring out that, I was misunderstanding complexity of submask enumeration 👎
 I was thinking somehow it's 3^R. However obviously it's at most 3^14 👎👎
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+508
   - column dp
  - http://d.hatena.ne.jp/kusano_prog/20110603/1307088751
   - submask enumeration
  - http://area.hateblo.jp/entry/2013/08/19/230903
   - submask enumeration
  - https://topcoder.g.hatena.ne.jp/shnya_m/20110607/1307380563
   - submask enumeration
  - http://topcoder.g.hatena.ne.jp/firewood/20110612/1307897928
   - submask enumeration
  - http://topcoder.g.hatena.ne.jp/jackpersel/20100804/1281196966
 
 23:00-23:50 add column dp solution with simpler recurrence relation than official editorial
 
 Summary:
  - In either way submask enumeration or column dp, Observation of disjoint bit set is crucial
   - I should be more familiar with relation between bit operation and arithmetic operation
  - Column dp is also typical solution to keep bit-wise property in range x<=N
 
 */

constexpr LL MOD=1000000009;
LL memo2[22][11];
class YetAnotherORProblem2 {
public:
  int R,N;
  LL f(int i, int n) {
    if(n<0) return 0;
    if(i==-1) return 1;
    LL &res=memo2[i][n];
    if(res>=0) return res;
    res=0;
    if((R>>i)&1) {
      // 1 from n
      res+=n*f(i-1,1),res%=MOD;
      // 1 from N-n
      res+=(N-n)*f(i-1,0),res%=MOD;
      // 0
      res+=f(i-1,0),res%=MOD;
    } else {
      // 1 from N-n
      res+=(N-n)*f(i-1,n),res%=MOD;
      // 0
      res+=f(i-1,n),res%=MOD;
    }
//    dump3(i,n,res);
    return res;
  }
  int countSequences(int N, int R) {
    this->N=N,this->R=R;
    MINUS(memo2);
    return f(20,N);
  }
};

// O(N*lg R*3^(lg R)) time
LL memo[11][1<<14];
class YetAnotherORProblem2_org {
public:
  int R,N;
  LL f(int i, int n) {
    if(i==N) return n==0;
    LL &res=memo[i][n];
    if(res>=0) return res;
    res=f(i+1,n);
    for(int s=n; s>0; s=(s-1)&n) {
      int s2=n-s;
      if(s>R) continue;
      dump4(i,n,s,s2);
      res+=f(i+1,s2),res%=MOD;
    }
    return res;
  }
  int countSequences(int N, int R) {
    this->N=N,this->R=R;
    MINUS(memo);
    LL res=0;
    int fmask=0;
    REPE(n,R) fmask|=n;
    dump(fmask);
    REPE(n,fmask) {
      LL x=f(0,n);
      dump2(n,x);
      res+=f(0,n),res%=MOD;
    }
    return res;
  }
};

class YetAnotherORProblem2_wrong {
  public:
  int countSequences(int N, int R) {
    LL pow[21]={0};
    pow[0]=1LL;
    REP(i,20) pow[i+1]=pow[i]*N%MOD;
    REP(i,20) dump2(i,pow[i]);
    LL res=0;
    int fmask=0;
    REPE(n,R) fmask|=n;
    dump(fmask);
    REPE(n,fmask) {
      int pc=__builtin_popcount(n);
      dump3(n,pc,pow[pc]);
      res+=pow[pc],res%=MOD;
    }
    return (int)res;
  }
};

// CUT begin
ifstream data("YetAnotherORProblem2.sample");

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

bool do_test(int N, int R, int __expected) {
    time_t startClock = clock();
    YetAnotherORProblem2 *instance = new YetAnotherORProblem2();
    int __result = instance->countSequences(N, R);
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
        int N;
        from_stream(N);
        int R;
        from_stream(R);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521560589;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "YetAnotherORProblem2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
