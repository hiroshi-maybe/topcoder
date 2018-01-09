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
 
 1/7/2018
 
 15:47-16:49 analysis
 17:43-17:55 RE. implement iterative DP, sample 3 and 4 don't pass.
 19:20-19:33 fix MOD bug and convert to iterative DP
 19:35-19:52 After bunch of constant optimization, system test passed (1.94 S)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+555
   - O(N*M) time by keeping state of only segment length (mod 3)
  - http://kmjp.hatenablog.jp/entry/2013/11/09/0900
   - O(N^2*M) time, but simpler by computing all intermediate segment length as my original solution
 
 Some missing observation caused a lot of complexity.
 I spent a lot of time to get ACC.
 
 1. I computed length of segment with even number of steps by ∑ C(cnt1+cnt2,cnt1).
  However, it's possible to prove...
   - necessary step for segment length L can be computed by fibonacci sequence
   - MOD 555555555 messed up the mod arithmetic of 2
 
 2. Segmentation fault due to deep recursion
 
 3. O(N^2*M) is redundant. O(N*M) is possible by remembering only state of segment length `L (mod 3)`
 
 4. No need to compute number of tile pattern with "even" step.
 
 My computation was below:
 
  U: total number of tile pattern (= C(N-2,M))
  A: number of tile with at least one consecutive mud tile ✅ .##. (number of way of step is ALWAYS "even")
  B: number of tile with no consecutive mud tile ❌ .##.
   B1: number of tile with no consecutive mud tile AND number of way of step is "even"
   B2: number of tile with no consecutive mud tile AND number of way of step is "odd"
 
  U = A ∪ B (A ∩ B = ∅)
  B = B1 ∪ B2 (B1 ∩ B2 = ∅)
 
   res
 = |A| + |B1|
 = (|U| - |B|) + |B1|
 
 However below is simpler to compute as shown in editorial:
 
 res = |U| - |B2|

 @anta's solution is really impressive. It's incredibly simple and beautiful.
 It's checking if step is even. Once even step in a segment is found, it's ok. `ok` flag gets true.
 
 Key:
  - Number of sequence of steps for segment length L is fibonacci(L)
  - Number of sequence of steps (fibonacci) is even when L%3==0
  - When mud tile is consecutive, number of step sequence is always even
  - If mud tile is there, number of steps can be computed independently
  - Number of way of step is "odd" only when number of step sequence of all the composing segments is odd
 
 Summary:
  - Direction of analysis was not wrong though, I missed many important observations
  - Level of this problem was a bit higher than my capability
  - It may be useful to know that 1 or 2 step may form fibonacci sequence
 
 */

constexpr LL MOD = 555555555;

LL C[557][557];
void choose(LL N, LL MOD) {
  for(int i=0; i<=N; ++i) {
    C[i][0]=1;
    for(int j=1; j<=i; ++j) {
      // i chooses j
      C[i][j] = C[i-1][j]+C[i-1][j-1], C[i][j]%=MOD;
    }
  }
}

// O(N^2) time solution by @anta
LL memo[556][556][3][2];
class MuddyRoad2 {
public:
  int N;
  LL f(int i, int m, int l, bool ok) {
    LL &res=memo[i][m][l][ok];
    if(res>=0) return res;
    if(i==N) {
      // ok: even step check, l=0: ok at last
      return res=(ok||l==0)&&m==0;
    }
    
    // put `.` and increment segment length state
    res=f(i+1,m,(l+1)%3,ok);
    // put `#` and reset segment length state
    if(i!=0&&i!=N-1&&m>0) res+=f(i+1,m-1,0,ok||l==0),res%=MOD;
    return res;
  }
  
  int theCount(int N_, int M) {
    this->N=N_;
    MINUS(memo);
    return f(0,M,0,false);
  }
};

// O(N^2*M) time solution inspired by @kmjp
LL dp[556][556];
class MuddyRoad2_kmjp {
public:
  int theCount(int N, int M) {
    ZERO(dp);
    choose(N+1,MOD);
    LL tot = C[N-2][M];
    
    dp[0][0]=1;
    REP(i,N+1) REP(m,M+1) if(dp[i][m]>0) {
      for(int x=0; x<=N-m-i; ++x) if(x%3!=0) {
        (dp[i+x][m+1]+=dp[i][m])%=MOD;
      }
    }
    
    LL res=(tot+MOD-dp[N-M][M+1])%MOD;
    return res;
  }
};

// O(N^2*M) time
int EV[556];
class MuddyRoad2_org {
  public:
  int N,M;
  LL dp[556][556][3];

  /*
  LL f1(int i, int m) {
    if(m<0) return 0;
    LL &res=memo1[i][m];
    if(res>=0) return res;
    if(i>=N) return res=0;
    if(i==N-1) return res=(m==0);
    
    res=f1(N-1,m);
    REP(x,N) res+=f1(i+2+x,m-1),res%=MOD;
//    dump3(i,m,res);

    return res;
  }
  
  LL f2(int i, int m, bool ok) {
    if(m<0) return 0;
    LL &res=memo2[i][m][ok];
    if(res>=0) return res;
    if(i>=N) return res=0;
    if(i==N-1) return res=(m==0)&&ok;
    
    res=f2(N-1,m,ok|EV[N-1-i]);
    REP(x,N) res+=f2(i+x+2,m-1,ok|EV[x]),res%=MOD;
    
//    dump4(i,m,ok,res);
    return res;
  }*/
  
  int theCount(int NN, int MM) {
    this->N=NN,this->M=MM;
    //MINUS(memo1),MINUS(memo2)
    ZERO(dp);//,ZERO(dp0);
    
//    if(N-2==M) return 1LL;
    choose(N+1,2);
    
    // Mathematically proved that EV[n]=1 for n s.t. n%3==0
    REP(n,N+1) {
      LL sum=0;
      for(int cnt2=0; cnt2*2<=n; cnt2+=1) {
        int cnt1=n-cnt2*2;
//        assert(cnt1+2*cnt2==n);
//        dump4(n,cnt2,cnt1,C[cnt1+cnt2][cnt1]);
        sum+=C[cnt1+cnt2][cnt1];
      }
//      assert(sum<2);
      EV[n]=((sum%2)==0);
    }
    
    choose(N+1,MOD);
    
//    dump2(N-2,M);
    
    LL tot = C[N-2][M];
//    LL a = f1(0,M);
//    dump(a);
    //LL b=0;
//    LL b = N!=314?f2(0,M,0):0;
//    dump(b);
    
    dp[N-1][0][1]=1LL,dp[N-1][0][2]=1LL;
    for(int i=N-2; i>=0; --i) REP(m,M+1) for(int ok=1; ok>=0; --ok) {
      dp[i][m][ok]=dp[N-1][m][ok|EV[N-i-1]];
      if(ok==0) dp[i][m][2]=dp[N-1][m][2];
      for(int x=0; x<=N-i-2; ++x) if(m>0) {
        dp[i][m][ok]+=dp[i+x+2][m-1][ok|EV[x]],dp[i][m][ok]%=MOD;
        
        if(ok==0) dp[i][m][2]+=dp[i+x+2][m-1][2],dp[i][m][2]%=MOD;;
      }
    }
    
    LL a=dp[0][M][2],b=dp[0][M][0];
//    dump3(tot,a,b);
    
    LL res=(tot+MOD-a)%MOD;
    res+=b,res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("MuddyRoad2.sample");

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

bool do_test(int N, int muddyCount, int __expected) {
    time_t startClock = clock();
    MuddyRoad2 *instance = new MuddyRoad2();
    int __result = instance->theCount(N, muddyCount);
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
        int muddyCount;
        from_stream(muddyCount);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, muddyCount, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515368832;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 955 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MuddyRoad2 (955 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
