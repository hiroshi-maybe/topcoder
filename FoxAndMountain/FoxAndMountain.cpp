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
 
 1/5/2018
 
 8:39-9:00 pause
 9:00-9:04 analysis
 9:05-9:15 Implemented but sample 4,5,6 don't work
 9:15-9:25 pause
 
 17:40-17:45 redesign
 17:45-17:50 sample 4 and 5 don't pass.
 18:21 Ok, I figured out. I need KMP.
 18:36 Implement prefix function and system test passed.

 It was straighforward to reduce to parenthesis balance problem.
 However It took a long time to solve due to two major mistakes in analysis
 
 1. I tried to build L+H+R by brute-forcing L and R
  => Duplicated patterns happens. This is not right approach (Same mistake as described in @kmjp's editorial)
 
 2. Missing string match transition table
  => It was right to add additional state that shows if how many strings in `H` matched.
     However, transition was always the head of `H` in my first analysis

 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+557
   - Aho-Corasick
  - http://kmjp.hatenablog.jp/entry/2012/10/13/0900
  - http://d.hatena.ne.jp/rintpsy/20121021/1350793085
 
 Other submit solutions
 
 @rejudge's solution in practice room is beautiful.
 It's building generic transition automaton not for only unmatched case.
 It simplifies dp transition computation a lot.
 
 @uwi's solution is building transition table from KMP explicitly.
 
 Key:
  - Design recurrece transition with string matching state following parenthesis building problem
  - Use KMP or Aho-Corasick automation to pre-compute transition table
 
 Summary:
  - This was hard problem that only 3 participants solved though, I solved by myself 👍
  - Two major issues in analysis is critical 👎
  - Even if one of keys is found, keep focusing on the problem by paying attention
   - I was too much concerned about parenthesis analysis
   - However this problem had also a factor of string matching
   - Missing this perspective brought wrong analysis
 
 */
constexpr int MOD = 1e9+9;

bool match(string s, string t) {
  REP(i,SZ(t)) if(s[i]!=t[i]) return false;
  return true;
}

// Method 1: O(M^2) simple transition builder
// from @rejudge's solution in practice room
int T[51][2];
void makeT(string P) {
  int M=SZ(P);
  ZERO(T);
  string S="UD";
  REP(i,M) REP(j,2) {
    char c=S[j];
    string suf=P.substr(0,i)+c;
    while(SZ(suf)&&!match(P,suf)) suf=suf.substr(1);
    T[i][j]=SZ(suf);
  }
  T[M][0]=T[M][1]=M;
//  REP(i,M+1)REP(j,2) dump3(i,j,T[i][j]);
}

vector<int> buildPrefixFunction(const string P) {
  int L = P.size();
  vector<int> pi(L+1, 0);
  
  // ⚠️ customization for this problem
  pi[0]=-1,pi[1]=0;
  
  if (L==0) return pi;
  
  int j=0;
  for(int i=2; i<L; ++i) {
    j = pi[i-1];
    while(true) {
      if (P[j]==P[i-1]) {
        // matched
        pi[i] = j+1; break;
      }
      // unmatced below
      
      // reached to head
      if (j==0) {
        pi[i] = 0; break;
      }
      j = pi[j];
    }
  }
  
  return pi;
}

// Method 2: O(N) KMP-based transition builder
// from @uwi's solution in practice room
void makeT_kmp(string P) {
  int M=SZ(P);
  VI pi=buildPrefixFunction(P);
  dumpAR(pi);
  ZERO(T);
  string S="UD";
  REP(i,M) REP(j,2) {
    int p=i;
    char c=S[j];
    while(p>=0&&P[p]!=c) p=pi[p];
    T[i][j]=p+1;
  }
  T[M][0]=T[M][1]=M;
//    REP(i,M+1)REP(j,2) dump3(i,j,T[i][j]);
}

// Method 3: O(M^3*26) generic transition builder
// from https://github.com/k-ori/topcoder/blob/master/lib/string-matching.cpp
int SMT[1024][26];
void buildSMT(string P) {
  memset(SMT, 0, sizeof SMT);
  int L=P.size();
  for(int i=0; i<=L; ++i) {
    for(int j=0; j<26; ++j) {
      char c = 'A'+j;
      if (i<L&&c==P[i]) {
        // matched
        SMT[i][j]=i+1;
      } else if (i==L) {
        // ⚠️ customization for this problem
        SMT[L][j]=L;
      } else {
        // unmatched
        string suf = P.substr(0,i)+c;
        int SL=(int)suf.size();
        // find longest prefix P[0..<k]
        for(int k=1; k<=i; ++k) if(P.substr(0,k)==suf.substr(SL-k)) SMT[i][j]=k;
      }
    }
  }
//  REP(i,L+1) dump3(i,SMT[i]['U'-'A'],SMT[i]['D'-'A']);
}

// O(N^3) time
LL dp[55][55][55];
class FoxAndMountain {
public:
  string H;
  int M,N;
  int count(int N, string H) {
    this->M=SZ(H),this->N=N,this->H=H;
    makeT(H);
//    buildSMT(H);
    
    ZERO(dp);
    dp[0][0][0]=1;
    REP(i,N+1) REP(b,N+1) REP(k,M+1) if(dp[i][b][k]>0) {
//      dump4(i,b,k,dp[i][b][k]);
      (dp[i+1][b+1][T[k][0]]+=dp[i][b][k])%=MOD; // U
      if(b-1>=0) (dp[i+1][b-1][T[k][1]]+=dp[i][b][k])%=MOD; // D
//      (dp[i+1][b+1][SMT[k]['U'-'A']]+=dp[i][b][k])%=MOD; // U
//      if(b-1>=0) (dp[i+1][b-1][SMT[k]['D'-'A']]+=dp[i][b][k])%=MOD; // D
    }
    return dp[N][0][M];
  }
};

vector<int> buildTr(const string P) {
  int L = P.size();
  vector<int> pi(L, 0);
  FOR(i,1,L) {
    string suf=P.substr(0,i)+(P[i]=='U'?"D":"U");
    while(SZ(suf)&&!match(P,suf)) suf=suf.substr(1);
    pi[i]=SZ(suf);
  }
  return pi;
}

class FoxAndMountain_org {
public:
  string H;
  int M,N;
  int count(int N, string H) {
    this->M=SZ(H),this->N=N,this->H=H;
    //MINUS(memo);
    
    ZERO(dp);
    VI T = buildTr(H);
//    dumpAR(T);
    dp[0][0][0]=1;
    REP(i,N+1) REP(b,N+1) REP(k,M+1) if(dp[i][b][k]>0) {
//      dump4(i,b,k,dp[i][b][k]);
      if(k==M) {
        (dp[i+1][b+1][k]+=dp[i][b][k])%=MOD;
        if(b-1>=0) (dp[i+1][b-1][k]+=dp[i][b][k])%=MOD;
      } else {
        if(H[k]=='U') {
          // 'U'
          (dp[i+1][b+1][k+1]+=dp[i][b][k])%=MOD;
          if(b-1>=0) (dp[i+1][b-1][T[k]]+=dp[i][b][k])%=MOD;
        } else {
          // 'D'
          (dp[i+1][b+1][T[k]]+=dp[i][b][k])%=MOD;
          if(b-1>=0) (dp[i+1][b-1][k+1]+=dp[i][b][k])%=MOD;
        }
      }
    }
  
    return dp[N][0][M];
  }
};

class FoxAndMountain_wrong {
  public:
  int count(int N, string H) {
    LL dp[55][55];
    ZERO(dp);
    dp[0][0]=1;
    REP(i,N+1) REP(b,N+1) {
      (dp[i+1][b+1]+=dp[i][b])%=MOD;
      if(b-1>=0) (dp[i+1][b-1]+=dp[i][b])%=MOD;
    }
    dump(dp[N][0]);
    
    int M=SZ(H);
    int K=0,Kmin=0;
    REP(i,M) K+=(H[i]=='U'?1:-1),Kmin=min(Kmin,K);
    dump3(M,K,Kmin);
    LL res=0;
    REP(b,N+1) if(b>=(-Kmin)) {
      REP(x,N-M+1) {
        int y=N-M-x;
        assert(y>=0&&b+K>=0);
        LL p=dp[x][b],q=dp[y][b+K];
        LL r=p*q%MOD;
/*        if(N==20&&r>0) {
          dump4(x,b,y,b+K);
          dump3(p,q,r);
        }*/
        res+=r,res%=MOD;
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("FoxAndMountain.sample");

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

bool do_test(int n, string history, int __expected) {
    time_t startClock = clock();
    FoxAndMountain *instance = new FoxAndMountain();
    int __result = instance->count(n, history);
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
        int n;
        from_stream(n);
        string history;
        from_stream(history);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, history, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515170360;
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
        cout << "FoxAndMountain (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
