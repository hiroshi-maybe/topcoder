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
 
 10/5/2017
 
 8:35-10:00 pause
 19:25-19:35 give up
 
 19:36-19:45 read editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+620
  - http://kmjp.hatenablog.jp/entry/2014/05/11/0930
 
 19:46-20:13 build recurrence relation
 
 p = _p/1000, q = 1.0-p
 
 n: number of remaining vertices
 a: number of connected component with 1 vertex
 b: number of connected component with 2 vertices
 c: number of connected component with 3 vertices

 f(n,a,b,c) =
   q^(a+2b+3c)                   *f(n-1,a+1,  b,  c) // x
 + q^(  2b+3c)    *a  *p         *f(n-1,a-1,b+1,  c) // o--x
 + q^(  2b+3c)  *aC2*p^2*q^(a-2) *f(n-1,a-2,  b,c+1) // o--x--o
 + q^(a   +3c)   *2b  *p*q^(2b-1)*f(n-1,  a,b-1,c+1) // o--o--x
 + q^(a   +3c)    *b*p^2*q^(2b-2)*f(n-1,  a,b-1,c+1) // o--x
                                                        | /
                                                        o/
 f(N,_,_,_) = 1.0
 res = 1.0 - f(N,0,0,0)

 note that n is not part of memo because n can be determined by (a,b,c)
 
 20:13-20:30 add solution
 
 key:
  - inclusion-exclusion principle
    - count probability to build graph with connected components of only 1, 2 and 3 vertices
  - probability DP
 
 summary:
  - totally messed up to figure out 38 graphs with 4 vertices (example 2)
  - idea of inclusive-exclusive principle with 1,2,3 connected components came up though, I couldn't desgin recurrence relation by myself
 
 solutions in contest
  - bottom-up DP
   - https://community.topcoder.com/stat?c=problem_solution&rm=322143&rd=15853&pm=13143&cr=23141356
     - very simple
   - https://community.topcoder.com/stat?c=problem_solution&rm=322145&rd=15853&pm=13143&cr=23187012
   - https://community.topcoder.com/stat?c=problem_solution&rm=322135&rd=15853&pm=13143&cr=23018719
   - https://community.topcoder.com/stat?c=problem_solution&rm=322122&rd=15853&pm=13143&cr=23147569
 
 */

// O(N^3) time
double memo[51][51][51];
class RandomGraph {
public:
  double p,q;
  double f(int n, int a, int b, int c) {
    if(memo[a][b][c]>=0) return memo[a][b][c];
    if(n==0) return 1.0;
    double res=0;
    
             res+=pow(q,a+2*b+3*c)                               *f(n-1,a+1,  b,  c);
    if(a>=1) res+=pow(q,  2*b+3*c)            *a  *p*pow(q,  a-1)*f(n-1,a-1,b+1,  c);
    if(a>=2) res+=pow(q,  2*b+3*c)*(a*(a-1)/2.0)*p*p*pow(q,  a-2)*f(n-1,a-2,  b,c+1);
    if(b>0)  res+=pow(q,a    +3*c)          *2*b  *p*pow(q,2*b-1)*f(n-1,  a,b-1,c+1);
    if(b>0)  res+=pow(q,a    +3*c)            *b*p*p*pow(q,2*b-2)*f(n-1,  a,b-1,c+1);
    
    return memo[a][b][c]=res;
  }
  
  double probability(int N, int _p) {
    MINUS(memo);
    this->p=_p/1000.0,this->q=1.0-p;
    
    return 1.0-f(N,0,0,0);
  }
};

class RandomGraph_wrong {
  public:
  int C(int n, int k) {
    int x=1;
    REP(i,k) x*=n-i;
    int y=1;
    REP(i,k) y*=i+1;
//    dump3(x,y,x/y);
    return x/y;
  }
  double pow(double x, int n) {
    double res=1;
    REP(_,n)res*=x;
    return res;
  }
  double probability(int n, int _p) {
    if(n<4) return 0.0;
    int cnt=C(n,4);
    double p=1.0*_p/1000,q=1.0-p;
//    dump3(p,q,cnt);
    double p3=(C(6,3)-C(4,1))*pow(p,3)*pow(q,3);
    double p4=C(6,4)*pow(p,4)*pow(q,2);
    double p5=C(6,5)*pow(p,5)*pow(q,1);
    double p6=C(6,6)*pow(p,6)*pow(q,0);
//    dump4(p3,p4,p5,p6);
    return cnt*(p3+p4+p5+p6);
  }
};

// CUT begin
ifstream data("RandomGraph.sample");

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

bool do_test(int n, int p, double __expected) {
    time_t startClock = clock();
    RandomGraph *instance = new RandomGraph();
    double __result = instance->probability(n, p);
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
        int n;
        from_stream(n);
        int p;
        from_stream(p);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, p, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507217728;
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
        cout << "RandomGraph (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
