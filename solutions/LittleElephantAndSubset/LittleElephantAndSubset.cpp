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
 
 11/4/2017
 
 21:29-22:00 pause
 22:55-23:12 duplicated sets should not be counted.
 23:30 ok bit DP.
 24:20-24:30 give up
 
 13:20-14:25 read editorials
 14:26-15:18 add solution
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+597
  - http://kmjp.hatenablog.jp/entry/2013/11/21/1000
  - http://emkcsharp.hatenablog.com/entry/SRM597/LittleElephantAndSubset
 
 We use at most 10 digits. So we can brute force (2^10) cases of used digits.
 In a set of digits, we need to count possible sets without duplication.
 This is a problem P = ∪ { P1(mask) : mask=1..<2^10 }.
 
 Suppose we have {1,2,3,4}. We want to build following sets:
 {1},{2},{3},{4}
 {12},{3},{4}
 {21},{3},{4}
 {13},{2},{4}
 ...
 
 This is possible by DP to solve two different problems.
 P2(mask2) = how many single numbers can be built by given digits {1,2} => {12,21} ({1},{2} should not be involved)
 P1(mask^mask2) = how many patterns can be built with rest of digits. This is actually subproblem of P1(mask)
                = P1(mask^mask2)
 Note that we should compute only when mask2 < (mask^mask2) to avoid duplicated count (symmetry)
 
 It's easy to solve P2. we can precompute it by enumerating 10 digits and reuse it.
 My second wrong solution was not differentiating P1 and original P. So it counted duplicated sets. Sigh...
 
 Thus f(mask) = ∑ { g(mask2)*f(mask3) : mask2=1..<mask, mask3=mask^mask2, mask2<mask3 }
 res = ∑ { f(mask) : mask=0..2^10 }
 
 Thus this is subproblem structure:
 P = ∪ { P1(mask) : mask=0..<2^10 } + P2(mask)
 P1(mask) = P2(mask2) x P1(mask3), mask2=1..<mask, mask3=mask^mask2, mask2<mask3 }
 
 T(P2) = 10! ≈ 4*10^6
 T(P) = 2^10 * T(P1) + T(P2)
      < 2^10*2^10 + 4*10^6, T(P1)<2^10
      < 10^6 + 4*10^6
      < 10^7
 
 Key:
  - Search space is at most 2^10
  - Combine two sub problems to avoid duplicated count
  - take either submask to avoid duplicated count
 
 Summary:
  - Wrong analysis over wrong analysis. very stupid 👎👎👎👎👎👎👎👎👎👎👎👎👎👎
   - First analysis brute force 10! patterns and count possible sets
    - duplicated count 👎
    - {1} is counted many times in {1,2,3,4,5,..}, {1,9,3,...}
   - Second brute force 2^10*x!
    - duplicated count 👎
   - Bitmask DP
    - duplicated count 👎
    - duplicated count for {1},{2},{3} in {{1,2},{3}} and {{1},{2,3}}
  - Refresh mind when switching to different strategy
  - Submask enumeration and taking always either one is important technique in counting problem to avoid duplication
 
 */
constexpr int MOD = 1e9+7;

LL g[1<<10];
LL memo[1<<10];
class LittleElephantAndSubset {
public:
  int N;
  LL f(int mask) {
    LL &res=memo[mask];
    if(mask==0) return 1;
    if(res>=0) return res;
    res=0;
    // submask enumeration
    for (int mask2=mask; mask2; mask2=(mask2-1)&mask) {
      int mask3=mask^mask2;
      if(mask2<mask3) continue;
      LL a=g[mask2],b=f(mask3);
      a*=b,a%=MOD;
      res+=a,res+=MOD;
    }
    return res;
  }
  
  void dfs(LL n, int mask) {
    if(n<=N) g[mask]++;
    REP(i,10) if((mask&(1<<i))==0) dfs(10*n+i,mask|1<<i);
  }
  int getNumber(int N) {
    this->N=N;
    ZERO(g);
    FOR(i,1,10) dfs(i,1<<i);
    MINUS(memo);
    
    LL res=0;
    FOR(mask,1,1<<10) res+=f(mask),res%=MOD;
    return res;
  }
};

LL dp[11];
class LittleElephantAndSubset_wrong2 {
public:
  int N;
  LL memo[1<<10];
  LL f(int mask) {
    LL &res = memo[mask];
    if(res>=0) return res;
    if(mask==0) return 0;
    res=0;
//    dump(mask);
    VI ds;
    REP(i,10) if(mask&(1<<i)) ds.push_back(i);
    int M=SZ(ds);
//    if(M==1) return res=(0<ds.front()&&ds.front()<=N);
//    dumpAR(ds);
    
    FOR(x,1,1<<M) {
      int mask2=0,mask3=0;
      REP(i,M) ((x&(1<<i))?mask2:mask3)|=1<<ds[i];
      if(mask3>mask2) continue;
      LL a=f(mask2),b=f(mask3);
      a*=b,a%=MOD;
      if(a!=0) dump4(mask,mask2,mask3,a);
      res+=a;
    }
    do {
      if(ds.front()==0) continue;
      LL n=0;
      REP(i,M) n=n*10+ds[i];
      if(n<=N) ++res;
    } while(next_permutation(ds.begin(),ds.end()));
    
    if(res>0) {
      FORR(n,ds) cout<<n<<",";
      cout <<endl;
      dump2(mask,res);
    }
    //    assert(res<=3);
    return res;
  }
  int getNumber(int N) {
    MINUS(memo);
    this->N=N;
    LL res=0;
    //    f({5,4,3,2,1});
    FOR(mask,1,1<<10) {
      res+=f(mask),res%=MOD;
    }
    
    return res;
  }
};

class LittleElephantAndSubset_wrong1 {
  public:
  int N;
  LL f(VI ds) {
    int M=SZ(ds);
    ZERO(dp);
    dp[0]=1;
    REP(i,M) if(dp[i]) {
      LL n=ds[i];
      if(n==0) continue;
      for(int k=1; i+k<=M&&n<=N; ++k) {
        if(1<=n&&n<=N) {
//          dump(n);
          dp[i+k]+=dp[i],dp[i+k]%=MOD;
        }
        if(i+k<M) n=10*n+ds[i+k];
      }
    }
//    dumpAR(dp);
//    FOR(i,1,11) res+=dp[i],res%=MOD;
//    dump(res);
//    if(res>0) dumpAR(ds);
//    assert(res<=3);
    return dp[M];
  }
  int getNumber(int N) {
    this->N=N;
    LL res=0;
//    f({5,4,3,2,1});
    FOR(mask,1,1<<10) {
      VI ds;
      REP(i,10) if(mask&(1<<i)) ds.push_back(i);
      do {
        LL x=f(ds);
        /*
        if(x>0) {
          FORR(n,ds) cout<<n<<",";
          cout <<endl;
          dump(x);
        }*/
        res+=x,res%=MOD;
      } while(next_permutation(ds.begin(),ds.end()));
    }
    
    return res;
  }
};

// CUT begin
ifstream data("LittleElephantAndSubset.sample");

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

bool do_test(int N, int __expected) {
    time_t startClock = clock();
    LittleElephantAndSubset *instance = new LittleElephantAndSubset();
    int __result = instance->getNumber(N);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509856129;
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
        cout << "LittleElephantAndSubset (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
