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
 
 8/20/2017
 
 15:57-16:57 time up

 19:08-20:03 read editorial and add brute-force solution
 - https://apps.topcoder.com/wiki/display/tc/SRM+665
 
 f(p,n) = f(p+1,n') ∪ g(p+1,n'), n'=n+x*10^p, x={8,11,14}
 g(p,n) = g(p+1,n'), n'=n+y*10^p, y={4,7}
 
 f(N,_) = 𝜙
 g(N,_) = 𝜙
 
 res = min { n : n ∈ f(*,*) }
 
 T(n) = 3*T(n-1)+3*T'(n-1)
 T'(n) = 2*T'(n-1)
 
 => T(n) = 3^n + 3*2^(n-1) = O(3^n)
 
 Key:
  - find 3^n cases focusing on sum instead of 4^n
 
 Summary:
  - 4^14 is too large ✅
  - tried brute force though, my idea was pinning l1 and serach l2. It didn't work ❌
   - no need to differentiate l1 or l2. We are interested in only sum of them
   - should have come up with 3^N by focusing sum of pairs {8,11,14} or {4,7}
 
 Column DP editorials:
  - http://topcoder.g.hatena.ne.jp/kuuso1/20150820/1440073415
  - https://topcoder.g.hatena.ne.jp/firewood/20160405/1459873069
  - http://mayokoex.hatenablog.com/entry/2015/08/12/000024
  - http://hamko.hatenadiary.jp/entry/2017/02/28/133227
  - http://kmjp.hatenablog.jp/entry/2015/08/13/0900
 
 22:54-23:13 add column DP solution
 
  dp[i][carry]: result at i-th column without leading 0s in lucky number
 dp2[i][carry]: result at i-th column with leading 0s in lucky number
 
 dp[0][0]=0, dp2[0][0]=Inf
 
  dp[i+1][c'] = min(_, dp[i][c]+x'*10^i) if match(x',S)
 dp2[i+1][c'] = min(_, dp[i][c]+x'*10^i) if match(x',S)
  where x'=(x+c)%10, c'=(x+c)/10, x=8,11,14

 dp2[i+1][c'] = min(_, dp2[i][c]+y'*10^i) if match(y',S)
  where y'=(y+c)%10, c'=(y+c)/10, y=4,7

 dp[N][0] = min(_,dp[N-1][1]+10^(N-1)) if match(1,S)
 
 res=min(dp[N][0],dp2[N][0])
 
 */

LL POW[15];
LL dp[15][2];
LL dp2[15][2];
class LuckySum {
public:
  const LL Inf=1e18;
  long long construct(string S) {
    int N=SZ(S);
    REP(n,15) POW[n]=(LL)pow(10LL,(LL)n);
    REP(i,N+1) dp[i][0]=dp[i][1]=dp2[i][0]=dp2[i][1]=Inf;
    
    dp[0][0]=0;
    REP(i,N) REP(c,2) {
      if(dp[i][c]<Inf) {
        for(LL x : {8,11,14}) {
          LL x2=x+c;
          LL c2=x2/10;
          x2%=10;
          
          if(S[N-1-i]!='?'&&(S[N-1-i]-'0')!=x2) continue;
          
          LL n=dp[i][c]+POW[i]*x2;
          dp[i+1][c2]=min(dp[i+1][c2], n);
          dp2[i+1][c2]=min(dp2[i+1][c2], n);
        }
      }
      if(dp2[i][c]<Inf) {
        for(LL y : {4,7}) {
          LL x2=y+c;
          LL c2=x2/10;
          x2%=10;
          
          if(S[N-1-i]!='?'&&(S[N-1-i]-'0')!=x2) continue;
          
          LL n=dp2[i][c]+POW[i]*x2;
          dp2[i+1][c2]=min(dp2[i+1][c2], n);
        }
      }
      if(i==N-1&&c==1) {
        if(S[0]=='?'||(S[0]-'0')==c) dp[i+1][0]=min(dp[i+1][0],dp[i][c]+POW[i]);
      }
    }
    
    LL res=Inf;
    res=min(res, dp[N][0]);
    res=min(res, dp2[N][0]);
    
    return res==Inf?-1:res;
  }
};

class LuckySum_bruteForce {
  public:
  const LL Inf=1e18;
  LL res=Inf;
  string S;
  LL POW[15];
  long long construct(string s) {
    S=s;
    REP(n,15) POW[n]=(LL)pow(10LL,(LL)n);
    f(0,0);
    
    return res==Inf?-1:res;
  }
  
  void f(int p, LL n) {
    if(p>=SZ(S)) return;
    for(LL x : {8LL,11LL,14LL}) {
      LL n2=x*POW[p]+n;
      if(match(n2)) res=min(res,n2);
      f(p+1,n2);
      g(p+1,n2);
    }
  }
  
  void g(int p, LL n) {
    if(p>=SZ(S)) return;
    for(LL y : {4LL,7LL}) {
      LL n2=y*POW[p]+n;
      if(match(n2)) res=min(res,n2);
      g(p+1,n2);
    }
  }
  
  bool match(LL sum) {
    for(int i=SZ(S)-1; i>=0; --i) {
      int n=sum%10; sum/=10;
      if(n==0) return false;
      if(S[i]=='?') continue;
      if((S[i]-'0')!=n) return false;
    }
    return sum==0;
    
    /*
     // string manipulation was slow and hit TLE
    string t=to_string(sum);
    if(SZ(t)!=SZ(S)) return false;
    REP(i,SZ(S)) {
      if(S[i]=='?') continue;
      if(S[i]!=t[i]) return false;
    }
    return true;*/
  }
/*
  void make() {
    LL L[250000];
    ZERO(L);
    int i=0;
    FOR(l,1,15) REP(mask,1<<l) {
      int n=0;
      REP(j,l) {
        int x=0;
        if(mask&(1<<j)) x=7;
        else x=4;
        n=10*n+x;
      }
      L[i++]=n;
    }
  }*/
};

// CUT begin
ifstream data("LuckySum.sample");

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

bool do_test(string note, long long __expected) {
    time_t startClock = clock();
    LuckySum *instance = new LuckySum();
    long long __result = instance->construct(note);
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
        string note;
        from_stream(note);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(note, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503269830;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "LuckySum (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
