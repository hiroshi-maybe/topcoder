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
 
 12/15/2017
 
 9:29-10:00 pause
 10:35-10:48 analysis
 10:49-11:22 submit and 1WA
 11:22-11:26 bug fix (boundary bug 50->51) and system test passed
 
 Possible meeting point is 150*150.
 If we can compute total number of paths f(i,tx,ty) for sheep i to meet at (tx,ty), result can be computed as below:
 res = ∑ { ∏ { f(i,tx,ty) : i=0..N-1 } : tx=-50..100, ty=-50..100 }
 
 If we can compute f(i,tx,ty) in reasonable time, we checkmate this problem.
 
 There are four directions { U,D,R,L } to move.
 If sheep can go from (X[i],Y[i]) to (tx,ty) by moves 'U'x`up`, 'D'x`dw`, 'R'x`ri`, 'L'x`lf`...
 Total number of path t(up,dw,ri,lf)=C(M,up)*C(M-up,dw)*C(M-up-dw,ri).
 => f(i,tx,ty) = ∑ { t(up,dw,ri,lf), up-dw=tx-X[i], ri-lf=ty-Y[i] }
 Such tuples (up,dw,ri,lf) can be computed in O(d2), d2 = M-(abs(tx-X[i])+abs(ty-Y[i])).
 t(a,b,c,d) also can be pre-computed in 50^4.
 
 Total runtime is M^4+150^2*N*150/2≈9*10^7
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+573
   - Solving without binomial coefficient
   - Total step is upperbounded by M
     - If state f(dx,dy,m) is defined, it forms DAG beause of decreasing m
     - DP works
  - http://kmjp.hatenablog.jp/entry/2013/03/23/1130
  - http://mayokoex.hatenablog.com/entry/2016/02/16/001410
 
 12/15/2017
 
 24:17-24:30 Add more efficient solution by simple DP
 
 */

// O(M^4) time
constexpr int MOD = 1e9+7;
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };
LL memo[151][151][51];
class WolfPackDivTwo {
public:
  LL f(int dx, int dy, int m) {
    LL &res=memo[dx][dy][m];
    if(res>=0) return res;
    if(m==0) return res=(dx==0&&dy==0);
    res=0;
    FORR(mv,moves) {
      int dx2=abs(dx-mv.first),dy2=abs(dy-mv.second);
      res+=f(dx2,dy2,m-1),res%=MOD;
    }
    return res;
  }
  int calc(vector<int> X, vector<int> Y, int M) {
    int N=SZ(X);
    MINUS(memo);
    LL res=0;
    for(int tx=-50; tx<=100; ++tx) {
      for(int ty=-50; ty<=100; ++ty) {
        LL s=1;
        REP(i,N) {
          int x=X[i],y=Y[i];
          int dx=abs(tx-x),dy=abs(ty-y);
          if(dx+dy>M) {
            s=0;
            break;
          }
          s*=f(dx,dy,M),s%=MOD;
        }
        res+=s,res%=MOD;
      }
    }
    
    return res;
  }
};

class WolfPackDivTwo_org {
  public:
  LL C[51][51];
  LL CC[51][51][51][51];
  int calc(vector<int> X, vector<int> Y, int M) {
    REP(i,51) {
      C[i][0]=1;
      FOR(j,1,i+1) (C[i][j]=C[i-1][j]+C[i-1][j-1])%=MOD;
    }
    REP(a,51)REP(b,51)REP(c,51)REP(d,51) if(a+b+c+d==M) {
      LL x=C[M][a];
      x*=C[M-a][b],x%=MOD;
      x*=C[M-a-b][c],x%=MOD;
      CC[a][b][c][d]=x;
    }
    
    int N=SZ(X);
    LL res=0;
    for(int tx=-50; tx<=100; ++tx) {
      for(int ty=-50; ty<=100; ++ty) {
        LL s=1;
        REP(i,N) {
          int x=X[i],y=Y[i];
          int dx=tx-x,dy=ty-y;
          int d1=abs(dx)+abs(dy),d2=M-d1;
          if(d1>M||d2%2==1) { s=0; break; }
          assert(d2>=0&&d2%2==0);
          int a=dy>0?dy:0,b=dx>0?dx:0,c=dy<0?-dy:0,d=dx<0?-dx:0;
          LL t=0;
          for(int aa=0; aa<=d2/2; ++aa) {
            int bb=d2/2-aa;
            int cc=aa,dd=bb;
            int up=a+aa,ri=b+bb,dw=c+cc,lf=d+dd;
            assert(up+ri+dw+lf==M);
            t+=CC[up][ri][dw][lf],t%=MOD;
          }
          s*=t,s%=MOD;
        }
        res+=s,res%=MOD;
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("WolfPackDivTwo.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool do_test(vector<int> x, vector<int> y, int m, int __expected) {
    time_t startClock = clock();
    WolfPackDivTwo *instance = new WolfPackDivTwo();
    int __result = instance->calc(x, y, m);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        int m;
        from_stream(m);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513186136;
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
        cout << "WolfPackDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
