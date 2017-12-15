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
LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}
LL factmod(LL n) {
  static vector<LL> memo(1,1);
  if(memo.size()<=n) {
    LL l=memo.size();
    memo.resize(n+1);
    for(LL i=l; i<=n; ++i) memo[i]=memo[i-1]*i, memo[i]%=MOD;
  }
  return memo[n];
}
LL choose(LL n, LL k) {
  if(n<k) return 0;
  k = min(n-k,k);
  LL res=modinv(factmod(k));
  REP(i,k) res*=(n-i)%MOD,res%=MOD;
  return res;
}*/

LL choose(LL n, LL k) {
  if(n<k) return 0;
  k = min(n-k,k);
  
  const int MAXK = 200;
  assert(k<=MAXK);
  static LL inv[MAXK+1],invfact[MAXK+1];
  
  if(inv[1]==0) {
    inv[1]=1;
    for(int i=2;i<=MAXK;i++) inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
    invfact[0]=1;
    for(int i=1;i<=MAXK;i++) invfact[i]=invfact[i-1]*inv[i]%MOD;
  }
  LL res=invfact[k];
  for(int i=0;i<k;++i) res*=(n-i)%MOD,res%=MOD;
  return res;
}

LL multichoose(LL n, LL k) {
  if(n==0&&k==0) return 1;
//  dump(n+k-1);
  return choose(n+k-1,k);
}

/*
 
 12/14/2017
 
 9:43-10:05 pause
 10:30-10:47 analysis
 10:48-11:44 implementation and debug (figured out my DP is not satisfying ∑s[i]==N)
 16:00-16:55 analyzed and reduced to a problem to count ∑ {s[i]' } = (N-sum)/cnt though, I couldn't solve this auxiliary problem (=> read editorial and figued out that multichoose works)
 17:20-18:13 add solution

 If we define unordered set S = { S[i] } and S' = { S[i]%M }, below two conditions need to be satisfied
  1. S'[i] is distinct
  2. ∑ S[i] = N
 
 Which is easier to search? It's clearly #1, because S'[i] ∈ {0..49} while S[i] ∈ {1..10^18}
 So let's compute number of S' first. S' is unordered set.
 So we can compute possible sequence by multiplying with |S|! later.
 
 S' for `cnt` = size of set and `sum` = ∑ S'[i] can be counted by DP as below:
 
 dp[0][0][0] = 1
 dp[sum+x][cnt+1][x+1] += dp[sum][cnt][x] // take x (x=0..50)
 dp[sum  ][cnt  ][x+1] += dp[sum][cnt][x] // skip x
 
 For `sum` and `cnt`, below should be satisfied:
 
 sum = ∑ { S'[i] : i=0..cnt-1 }
 S[i] = X[i] * M + S'[i]
 
    N
  = ∑ { S[i] : i=0..cnt-1 }
  = ∑ { X[i] * M + S'[i] : i=0..cnt-1 }
  = M * ∑ { X[i] : i=0..cnt-1 } + ∑ { S'[i] : i=0..cnt-1 }
  = M * ∑ { X[i] : i=0..cnt-1, X[i]>=0 } + sum
 
 ∑ { X[i] : i=0..cnt-1, X[i]>=0 } = Y (Y = (N - sum) / M)
 
 If (N - sum) % M == 0, computed S' with `sum` and `cnt` is valid.
 Problem is reduced to subproblem to count possible X s.t. ∑{x:x>=0,x∈X}=Y and |X|=cnt
 This can be computed by H(cnt,Y), where H(n,k)=C(n+k-1,k) (n multichooses k)
 
 We can compute ordered set from unordered set with distinct elements by multiplying |S|!
 res = ∑ { H(cnt,Y)*cnt!*dp[sum][cnt][M] : (N-sum)%M==0 }
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+573
  - http://kenkoooo.hatenablog.com/entry/2016/05/21/031423
 
 Key:
  - Count number of set S[i]%M by DP
  - Multiply with |S|! to count S where order is different
  - Count how to distribute (N-sum)/M by multichoose
  - Computing H(n,k) in O(k) is possible
 
 Summary:
  - This was tough problem. I could not solve by myself
  - First solution was not counting sequence where ∑s[i]==N is satisfied
   - Computation to count combination of x%M was almost correct
   - Only samples 0,1,2 where M is small passed
  - I reduced to problem to count ∑ {s[i]' } = (N-sum)/cnt
   - This was correct though, I misunderstood that this problem is subset sum
   - However that's not the case because possible number set is given in subset sum
   - It's actually solved by multichoose in O(K) time
  - Computing H(n,k) for large n was also a challenge
   - I added a new algorithm in combinatorics library
 
 */

// O(N^4) time
LL dp[1226][51][51];
class DistinctRemainders {
public:
  int howMany(long long N, int M) {
    ZERO(dp);
    
    LL F[51]={};
    F[1]=1LL;
    FOR(i,2,51) F[i]=F[i-1]*i,F[i]%=MOD;
    
    dp[0][0][0]=1;
    REP(sum,1226)REP(cnt,M)REP(p,M) if(dp[sum][p][cnt]>0) {
      (dp[sum+p][p+1][cnt+1]+=dp[sum][p][cnt])%=MOD;
      (dp[sum  ][p+1][cnt  ]+=dp[sum][p][cnt])%=MOD;
    }

    LL res=0;
    REP(sum,1226) FOR(cnt,1,M+1) if(N-sum>=0&&(N-sum)%M==0) {
      LL Y=(N-sum)/M;
      LL a=dp[sum][M][cnt];
      a*=multichoose(cnt,Y),a%=MOD;
      a*=F[cnt],a%=MOD;
      res+=a,res%=MOD;
    }
    
    return res;
  }
};

// O(N^5) time
class DistinctRemainders_org {
public:
  LL dp[1226][51][51];
  int howMany(long long N, int M) {
    ZERO(dp);
    
    LL F[51]={};
    F[1]=1LL;
    FOR(i,2,51) F[i]=F[i-1]*i,F[i]%=MOD;
    
    dp[0][0][0]=1;
    REP(sum,1226)REP(p,M)REP(cnt,M) if(dp[sum][p][cnt]>0) {
      FOR(i,p,M) {
        int sum2=sum+i;
        assert(sum2<1226);
        (dp[sum2][i+1][cnt+1]+=dp[sum][p][cnt])%=MOD;
      }
    }
    
    LL res=0;
    REP(sum,1226) FOR(cnt,1,M+1) if(N-sum>=0&&(N-sum)%M==0) {
      LL H=(N-sum)/M;
      LL a=0;
      REP(p,51) a+=dp[sum][p][cnt],a%=MOD;
      a*=multichoose(cnt,H),a%=MOD;
      a*=F[cnt],a%=MOD;
      res+=a,res%=MOD;
    }
    
    return res;
  }
};

class DistinctRemainders_wrong {
  public:
  int howMany(long long N, int M) {
    ZERO(dp);
    
    LL F[51]={};
    F[1]=1LL;
    FOR(i,2,51) F[i]=F[i-1]*i,F[i]%=MOD;
    
    LL NN=N%M;
    dump(NN);
    LL res=0;
    dp[0][0][0]=1;
    REP(sum,M)REP(p,M)REP(cnt,M) if(dp[sum][p][cnt]>0) {
      dump4(sum,p,cnt,dp[sum][p][cnt]);
      FOR(i,p,M) {
        int sum2=(sum+i)%M;
        if(sum2==NN) {
          LL a=dp[sum][p][cnt]*F[cnt+1]; a%=MOD;
          dump4(p,i,cnt+1,a);
          res+=a,res%=MOD;
        }
//        LL b=(N-(LL)i)/M+1;
        LL b=N/M+(i<=(N%M));
        LL a=dp[sum][p][cnt]*b; a%=MOD;
        
        if (sum2==1&&i+1==2&&cnt+1==2) {
          dump4(sum,sum2,p,i+1);
          dump3(cnt,cnt+1,a);
        }
        
        
        (dp[sum2][i+1][cnt+1]+=a)%=MOD;
//        dump4(sum2,i+1,cnt+1,dp[sum2][i+1][cnt+1]);
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("DistinctRemainders.sample");

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

bool do_test(long long N, int M, int __expected) {
    time_t startClock = clock();
    DistinctRemainders *instance = new DistinctRemainders();
    int __result = instance->howMany(N, M);
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
        long long N;
        from_stream(N);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513273385;
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
        cout << "DistinctRemainders (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
