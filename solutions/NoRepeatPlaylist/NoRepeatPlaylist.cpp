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
 
 2/13/2018
 
 8:34-9:10 analysis
 9:13-9:18 debug and submit (275.94 pt)
 
 I computed possible orders without differentiating each song and multiplied with N! at last.
 
 dp[i+1][p+1]+=dp[i][p]
 dp[i+1][p]+=dp[i][p]*max(p-M,0)
 
 Or...
 
 dp[i][j] = dp[i-1][j-1]*(N-j+1) + dp[i-1][j]*max(j-M,0)
 
 - N-j+1 candidate of unplayed songs
 - max(j-M,0) candidate of already played songs
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+531
   - dp and inclusion exclusion principle
  - http://d.hatena.ne.jp/kusano_prog/20120131/1328019165
   - dp
  - http://d.hatena.ne.jp/simezi_tan/20120201/1328089328
   - dp with combinatorics
  - http://naoyat.hatenablog.jp/entry/2012/01/31/235459
   - inclusion exclusion principle
  - http://mayokoex.hatenablog.com/entry/2016/02/09/185006
   - inclusion exclusion principle

 It took a lot of time to understand how IEP (inclusion exclusion principle) is applied in the official editorial.
 
 - Counting intersection by inclusion exclusion principle
 -  https://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle#Statement
    > In applications it is common to see the principle expressed in its complementary form.
  - https://yukicoder.me/wiki/algorithm_summary
    - Very impressive article. From this article, I understood that editorial is counting cardinality of intersection set!
 
 2/14/2018 Add solution with inclusion-exclusion principle
 
 Popular IEP use case: compute cardinality of set which does NOT belong to any of sets A[i], i=0..N-1.
 
   res
 = |∩ { Ā[i] : i=0..N-1 }|
 = |Ū { A[i] : i=0..N-1 }| // De Morgan's laws
 = |U| - |∪ { A[i] : i=0..N-1 }| // U is universal set
 = ∑ { (-1)^|X| * |∩ { A[i] : i∈X }| : X ⊆ {0..N-1} } // IEP
 
 Note that universal set corresponds to a case where X = 𝜙.
 This is computing cardinality of sets which satisfies some of conditions that our problem does not want to hold.
 
 It takes 2^N to enumerating all the subsets, which is not polynomial time.
 IEP is powerful when...
 
 > the size of the intersection sets appearing in the formulas for the principle of inclusion–exclusion depend only on the number of sets in the intersections and not on which sets appear.
 from https://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle#A_special_case

 In such a case...
 
 If f(k) = |∩ { A[i] : i∈X, X⊆{0..N-1}, |X|=k }|
 
 res = ∑ { (-1)^|k| * C(N,k) * f(k) : k = 0..N } // Choosing k sets out of N sets A[0],..,A[N-1]
 
 In this problem, A[i] = { list of songs when song `i` is NOT played }
 What we want is obviously ∩ { Ā[i] : i=0..N-1 }
 
 f(k)
 = 0                      if k>N-M
   P(N-k,M)*(N-k-M)^(P-M) otherwise
 
   res
 = ∑ { (-1)^|k| * C(N,k) * f(k) : k = 0..N }
 = ∑ { (-1)^|k| * C(N,k) * P(N-k,M)*(N-k-M)^(P-M) : k = 0..N-M }
 
 Or based on symmetric property, we can put k' = N-k.
 Then we can define sets A'[k'] = { list of songs when song `i` is played }
 Most of submit solutions are taking this way.
 
 IEP solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=311324&rd=14724&pm=11774&cr=22689544
  - https://community.topcoder.com/stat?c=problem_solution&rm=311370&rd=14724&pm=11774&cr=22692058
 
 Key:
  - No need to remember used songs. We can remember number of used songs at i-th song to be played
  - In the last M songs are distinct
 
 Summary:
  - Only 26 people solved during the contest. It took a while though, I solved by myself 👍
  - Analysis to define state without remembering used specific song was not straighforward for me
  - Mention to distinct M songs in official editorial is cool and easy to understand
  - I understood that I was not familiar with IEP. Great chance to understand it!
 
 */

const LL MOD=1000000007;

int M,P;
#define MAX_N 300
struct IEP_comp {
public:
  IEP_comp(int N, long long MOD=1000000007): N(N), MOD(MOD) {
    for(int i=0; i<=N; ++i) {
      C[i][0]=1;
      for(int j=1; j<=i; ++j) {
        C[i][j] = C[i-1][j]+C[i-1][j-1], C[i][j]%=MOD;
      }
    }
  }
  long long solve() {
    long long res=0;
    for(int k=0; k<=N; ++k) {
      long long sign=k%2==0?1:-1;
      long long x=sign;
      x*=C[N][k],x%=MOD;
      x*=f(k),x%=MOD;
      x+=MOD,x%=MOD;
      res+=x,res%=MOD;
    }
    return res;
  }
  
  // ⚠️ Implement this function
  // Compute f(k) = |∩ { A[i] : i∈X, X⊆{0..N-1}, |X|=k }|
  // Return size of intersection of `k` sets out of A[i], i=0..N-1
  long long f(int k) {
    LL c=1;
    REP(m,M) (c*=N-k-m)%=MOD;
    LL d=1;
    REP(_,P-M) (d*=(N-k-M))%=MOD;
    return (c*d)%MOD;
  }
private:
  int N;
  long long MOD;
  long long C[MAX_N][MAX_N];
};

class NoRepeatPlaylist {
public:
  int numPlaylists(int N, int M_, int P_) {
    M=M_,P=P_;
    IEP_comp ie(N);
    return ie.solve();
  }
};

// IEP, O(N*P) time
LL C[101][101];
class NoRepeatPlaylist_simple {
public:
  int numPlaylists(int N, int M, int P) {
    REPE(i,N) {
      C[i][0]=1;
      FORE(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
    }
    
    LL res=0;
    REPE(k,N-M) {
      LL a=k%2==0?1:-1;
      LL b=C[N][k];
      LL c=1;
      REP(m,M) (c*=N-k-m)%=MOD;
      LL d=1;
      REP(_,P-M) (d*=(N-k-M))%=MOD;
      res+=a*b%MOD*c%MOD*d%MOD+MOD,res%=MOD;
    }
    
    return res;
  }
};

// dp, O(N*P) time
LL dp[101][101];
class NoRepeatPlaylist_org {
  public:
  int numPlaylists(int N, int M, int P) {
    LL perm=1;
    FORE(i,1,N) (perm*=i)%=MOD;
    ZERO(dp);
    dp[0][0]=1;
    REP(i,P) REPE(p,N) if(dp[i][p]) {
      (dp[i+1][p+1]+=dp[i][p])%=MOD;
      (dp[i+1][p]+=dp[i][p]*max(p-M,0)%MOD)%=MOD;
//      dump4(i,p,dp[i][p],dp[i+1][p+1]);
    }
    return dp[P][N]*perm%MOD;
  }
};

// CUT begin
ifstream data("NoRepeatPlaylist.sample");

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

bool do_test(int N, int M, int P, int __expected) {
    time_t startClock = clock();
    NoRepeatPlaylist *instance = new NoRepeatPlaylist();
    int __result = instance->numPlaylists(N, M, P);
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
        int M;
        from_stream(M);
        int P;
        from_stream(P);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, P, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1518539666;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "NoRepeatPlaylist (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
