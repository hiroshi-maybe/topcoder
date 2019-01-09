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

constexpr int MOD = 1e9+7;

/*
 
 8/24/2017
 
 22:41-23:21 design
 23:22-24:00 samples don't pass and time up
 
 8/27/2017
 
 look at approach in editorial
  - http://kmjp.hatenablog.jp/entry/2015/06/15/1000
 
 10:10-11:55 solve K=2 case
 
 recurrence relation when K=2
 f(l,i) = (l+1)*(f(l,i-1)+f(i-l,i-1))
          0 if l>i
 f(l,0) = l==0
 
 res = ∑ { 2*f(l,N-1) : l=0..N-1 }
 
 Now we can expand this to K=3.
 We have another option to select in recurrence relation.
 
 f(a,b,i) = (a+b+1) * (f(i-a-b,b,i-1)+f(a,i-a-b,i-1)+f(a,b,i-1))
            0 if a<0||b<0||a+b>i
 f(a,b,0) = a==0&&b==0
 
 res = ∑ { 3*f(a,b,N-1) : a=0..N-1, b=0..N-1 }
 
 11:55-12:35 solve K=3 case and system test passed.
 
 read https://apps.topcoder.com/wiki/display/tc/SRM+661
 13:00-13:36 add simpler iterative DP solution inspired by @kmjp's solution and official editorial
 
 Key:
  - K is at most 3 (small) => K dimension DP is possible
  - if number of nodes of different colors in left is known, it's easy to count patterns.
  - problem statement follow order right to left though, left to right order is easier
    - because count at i is determined by colors at 0..i-1
 
 Summary:
  - I tried to make recurrence relation between K and K-1 though, it didn't work 👎
  - RTL vs LTR. In this case left determines right. easier to count from left to right.
 
 There is O(N) math solution 😳
 - https://community.topcoder.com/stat?c=problem_solution&rm=326486&rd=16464&pm=13842&cr=40166529
 - http://kmjp.hatenablog.jp/entry/2015/06/15/1030
 
 f(i) = K+(i-1)*(K-1)
 
 K for no edge case from i. we can select any color out of K
 Suppose color[j] == x (j<i). We can select color y ∈ Y = { color != x }. Also |Y| = K-1.
 We can select such j from i-1 positions.
 Thus if there is an edge, pattern of the case = (i-1)*(K-1).
 
 res = ∏ { f(i) : i=1..N }
 
 13:40-14:24 add O(N) solution
 
 */

class ColorfulLineGraphsDiv2 {
public:
  int countWays(int N, int K) {
    LL res=1LL;
    for(int i=1; i<=N; ++i) res*=K+(i-1)*(K-1),res%=MOD;
    return res;
  }
};

LL dp[101][101][101];
class ColorfulLineGraphsDiv2_dp {
public:
  int countWays(int N, int K) {
    ZERO(dp);
    dp[1][0][0]=1;
    if(K>1) dp[0][1][0]=1;
    if(K>2) dp[0][0][1]=1;
    
    REP(a,N+1) REP(b,N+1) REP(c,N+1) if(dp[a][b][c]>0) {
      if(a+1<=N) (dp[a+1][b][c]+=dp[a][b][c]*(1+b+c))%=MOD;
      if(K>1&&b+1<=N) (dp[a][b+1][c]+=dp[a][b][c]*(1+a+c))%=MOD;
      if(K>2&&c+1<=N) (dp[a][b][c+1]+=dp[a][b][c]*(1+a+b))%=MOD;
    }
    
    LL res=0;
    REP(x,N+1) REP(y,N+1) REP(z,N+1) if(x+y+z==N) {
      res+=dp[x][y][z],res%=MOD;
    }
    return res;
  }
};

LL memo[101][101][101];
class ColorfulLineGraphsDiv2_rec {
public:
  int K;
  LL f2(int l, int i) {
    if(l>i) return 0;
    if(i==0) return l==0;
    LL &res=memo[l][i][0];
    if(res>=0) return res;
    
    LL x=f2(l,i-1)+f2(i-l,i-1); x%=MOD;
    x*=l+1,x%=MOD;
    return res=x;
  }
  
  LL f3(int a, int b, int i) {
    if(a+b>i) return 0;
    if(i==0) return a==0&&b==0;
    if(a<0||b<0) return 0;
//    dump3(a,b,i);
    LL &res = memo[a][b][i];
    if(res>=0) return res;
    
    LL x=f3(i-a-b,b,i-1);
    x+=f3(a,i-a-b,i-1),x%=MOD;
    x+=f3(a,b,i-1),x%=MOD;
    x*=a+b+1,x%=MOD;
    return res=x;
  }
  
  int countWays(int N, int _K) {
    K=_K;
    if(K==1) return 1;
    MINUS(memo);
    LL res=0;
    if(K==2) {
      REP(l,N) res+=2*f2(l,N-1), res%=MOD;
      return res;
    }
    
    REP(a,N)REP(b,N) res+=3*f3(a,b,N-1), res%=MOD;
    return res;
  }
};

/*
class ColorfulLineGraphsDiv2_wrong {
  public:
  LL memo[4][101];
  int K;
  LL f(int c, int i) {
    if(i==0) return 1;
    if(l>i) return 1;
    if(memo[c][l][i]>=0) return memo[c][l][i];
    
    LL res=0;
    REP(k,K) res+=f(k,l,i-1),res%=MOD;
    
    REP(j,i) REP(k,K) if(k!=c) {
      LL x=f(k,l,j);
      LL y=0;
      REP(k2,K) y+=f(k2,j+1,i-1),y%=MOD;
      res += (x*y)%MOD, res%=MOD;
    }
    
    return memo[c][l][i]=res;
  }
  
  int countWays(int N, int _K) {
    K=_K;
    MINUS(memo);
    LL res=0;
    REP(k,K) res+=f(k,N-1), res%=MOD;
    return res;
  }
};*/

// CUT begin
ifstream data("ColorfulLineGraphsDiv2.sample");

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

bool do_test(int N, int K, int __expected) {
    time_t startClock = clock();
    ColorfulLineGraphsDiv2 *instance = new ColorfulLineGraphsDiv2();
    int __result = instance->countWays(N, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503639698;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ColorfulLineGraphsDiv2 (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
