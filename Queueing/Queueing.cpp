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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/27/2017
 
 8:38-9:57 time up
 18:20-18:30 give up

 18:40-20:00 read editorials
 - Beautiful DP reduced from equation
  - https://apps.topcoder.com/wiki/display/tc/SRM+687
  - http://kmjp.hatenablog.jp/entry/2016/04/11/1000
  - https://community.topcoder.com/stat?c=problem_solution&rm=328443&rd=16708&pm=14167&cr=40380443
  - https://community.topcoder.com/stat?c=problem_solution&rm=328446&rd=16708&pm=14167&cr=40227391
  - https://community.topcoder.com/stat?c=problem_solution&rm=328447&rd=16708&pm=14167&cr=22772938
 
 Suppose A = 1/p1, A'=1-A, B = 1/p2, B' = 1-B
 f(a,b) = f(a-1,b-1)*A*B + f(a,b-1)*A'*B + f(a-1,b)*A*B' + f(a,b)*A'*B'
 <=> (1-A'*B')*f(a,b) =
 <=> f(a,b) = ( f(a-1,b-1)*A*B + f(a,b-1)*A'*B + f(a-1,b)*A*B' ) / (1-A'*B')
 
 f(x,0) = 0, f(0,x) = 1
 
 - More math solutions
  - http://pekempey.hatenablog.com/entry/2016/04/08/185156
 
 1. Permutation solution
 
 res = ∑ {f(x) * ∑ {g(y), y=x+1..∞}, x=0..∞}
 where f(x): queue1 is completed by x secs, g(y): queue2 is completed by y secs
 
 f(k) = A*C(k-1,n-1)A^(n-1)*A'^(k-n)
 f(k+1) = A'*k/(k-n+1) * f(k)
 k⪅2020202 to meet expected precision
 
 2. DP with infinite geometric sequence
  - Infinite geometric sequence ∑r^k (k=0..∞) = 1/(1-r)
   - https://en.wikipedia.org/wiki/Geometric_progression
 
 f(a,b): probability where queue 1 processes a people, queue 2 processes b people
 
 f(a+1,b+1) = f(a,b)*A *B *X
 f(a  ,b+1) = f(a,b)*A'*B *X
 f(a+1,b  ) = f(a,b)*A *B'*X
 
 X = 1/(1-A'*B') = ∑(A'*B')^k, k=0..∞, sum of probability of k times "no-luck"
 
 22:50-23:30 add solution
  - index mistake - be careful about index border
  - formulat -> code conversion mistake - are you crazy?
 
 23:33-24:10 add another DP with infinite geometric sequence
 
 Key
 - Analysis of `q*(1-q)^(k-1)` formula
  - `q` for SUCCESS, (1-q) for FAILURE
 - Rather than compute probability for specific k (infinite cases), move time-line by one second like sweep line
  - there is corresponding probability `q` and `1-q` per second!
 - DP formula reduced from equation
 - There could be infinite number
  - ignore over error precision or mathematically compute infinite sequence
 
 Summary
 - counting seconds never meets expected precidion
  - how to figure out it? probably should compute?
    - in my wrong answer, I figured out that I cannot achieve probability 1.0 by 10000 iteration
  - now it's time of math. Infinite geometric sequence helps as shown by @pekempey's article
 
 */

// delivering DP inspired by @pekempey's article
double f[1001][1001];
class Queueing {
public:
  double probFirst(int len1, int len2, int p1, int p2) {
    memset(f, 0.0, sizeof f);
    double A=1.0/(double)p1, _A=1.0-A, B=1.0/(double)p2, _B=1.0-B, X=1.0-_A*_B;
    f[0][0]=1.0;
    
    REP(i,len1) REP(j,len2) {
      f[i+1][j+1] += f[i][j]* A* B/X;
      f[i+1][  j] += f[i][j]* A*_B/X;
      f[  i][j+1] += f[i][j]*_A* B/X;
    }
    
    double res=0;
    REP(i,len2) res += f[len1][i];
    return res;
  }
};

// collecting DP
double g[1001][1001];
class Queueing_dp2_collect {
public:
  double probFirst(int len1, int len2, int p1, int p2) {
    memset(g, 0.0, sizeof g);
    double A=1.0/(double)p1, _A=1.0-A, B=1.0/(double)p2, _B=1.0-B, X=1.0-_A*_B;
    g[0][0]=1.0;
    
    REP(i,len1) g[i+1][0] = g[i][0]* A*_B/X;
    REP(j,len2) g[0][j+1] = g[0][j]*_A* B/X;
    REP(i,len1) REP(j,len2) {
      g[i+1][j+1] = g[i][j]*A*B;
      if(i+1<len1) g[i+1][j+1] += g[i+1][j]*_A*B; // state should not move from g[len1][*]
      if(j+1<len2) g[i+1][j+1] += g[i][j+1]*A*_B; // state should not move from g[*][len2]
      g[i+1][j+1] /= X;
    }
    
    double res=0;
    REP(i,len2) res += g[len1][i];
    return res;
  }
};

class Queueing_dp1 {
public:
  double probFirst(int len1, int len2, int p1, int p2) {
    memset(f, 0.0, sizeof f);
    double A=1.0/(double)p1, _A=1.0-A, B=1.0/(double)p2, _B=1.0-B;
    
    REP(i,len2) f[0][i+1]=1.0;
    
    REP(i,len1) REP(j,len2) {
      f[i+1][j+1] = f[i][j]*A*B + f[i+1][j]*_A*B + f[i][j+1]*A*_B;
      f[i+1][j+1] /= 1.0-_A*_B;
    }
    
    return f[len1][len2];
  }
};

#define INV 10000
class Queueing_org {
  public:
  double pr1[1001][INV];
  double pr2[1001][INV];

  double pr(int k, int p) {
    double kk=(double)k, pp=(double)p;
    return (1.0/pp)*pow(1.0-1.0/pp, kk-1.0);
  }
  double probFirst(int len1, int len2, int p1, int p2) {
//    dump2(len1,len2); dump2(p1,p2);
    REP(i,len1+1) REP(j,INV) pr1[i][j]=0.0;
    REP(i,len2+1) REP(j,INV) pr2[i][j]=0.0;
    
    FOR(k,1,INV) pr1[1][k]=pr(k,p1), pr2[1][k]=pr(k,p2);
    FOR(l,1,len1) FOR(k,1,INV) FOR(x,1,50) {
//      dump4(k,x,k+x,INV);
      if(k+x<INV) pr1[l+1][k+x]+=pr1[l][k]*pr(x,p1);
    }
    FOR(l,1,len2) FOR(k,1,INV) FOR(x,1,50) {
      if(k+x<INV) pr2[l+1][k+x]+=pr2[l][k]*pr(x,p2);
    }
    
    double tot1=0,tot2=0;
    REP(i,INV) tot1+=pr1[len1][i];
    REP(i,INV) tot2+=pr2[len2][i];
    //dump2(tot1,tot2);
    
    //dump2(pr2[len2][len2],pr2[len2][len2+1]);
    FOR(i,1,INV) pr2[len2][i]+=pr2[len2][i-1];
    assert(pr2[len2][INV-1]<=1.0);
    
    double res=0.0;
    FOR(j,len1,INV) {
//      dump4(i,j,pr1[len1][j],pr2[len2][i]);
      res+=pr1[len1][j]*pr2[len2][j-1];
      if(j%100==0) dump2(j,res);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("Queueing.sample");

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

bool do_test(int len1, int len2, int p1, int p2, double __expected) {
    time_t startClock = clock();
    Queueing *instance = new Queueing();
    double __result = instance->probFirst(len1, len2, p1, p2);
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
        int len1;
        from_stream(len1);
        int len2;
        from_stream(len2);
        int p1;
        from_stream(p1);
        int p2;
        from_stream(p2);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(len1, len2, p1, p2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501169880;
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
        cout << "Queueing (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
