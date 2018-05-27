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
 
 5/17/2018 SRM 734
 
 10:05-11:00 time up
 
 I tried to solve by Euler's phi function and brute-force. However samples didn't pass
 
 15:30-16:50 Read code
 
 5/26/2018
 
 Editorials:
  - http://kmjp.hatenablog.jp/entry/2018/05/20/1030
  - http://hamko.hatenadiary.jp/entry/2018/05/17/114107
 
 Tweets:
  - https://togetter.com/li/1228213
  - https://twitter.com/beet_aizu/status/996943437025837058
  - https://twitter.com/beet_aizu/status/996947005292228608
 
 Prime factorization with sieve of Eratosthenes:
  - http://d.hatena.ne.jp/inamori/20091019/p1
  - http://sucrose.hatenablog.com/entry/2014/10/10/235805
  - http://www.osak.jp/diary/diary_201310.html#20131017
 
 16:00-18:42 read editorials and add solution
 
 We can compute result for quarter of the plain field and multiply with 4.
 What we want to know is number of unique slope which goes through the origin.
 That is number of unique co-prime pairs.
 
 We can iterate x from 1 to R.
 For each `x`, we know Y upper bound of y which satisfies hypot(x,y)<=R
 y<=R<=1e6 shows that we have at most 7 prime factors as seen below:
 
 > https://github.com/k-ori/topcoder/blob/master/lib/divisor.cpp#L118
 > 𝜔'(10^6) = 7, n= 510510, prime factors = {2,3,5,7,11,13,17}
 
 Suppose x is composed of prime factors {2, 3} and upper bound Y is 38.
 Then we want to count |{y : y<38, 2∤y AND 3∤y }|
 This cardinarity can be computed by inclusion-exclusion principle in O(2^𝜔'(x)+√x) time
 
 Actually this is still slow. O(R*√x) <=1e9.
 We need more optimization to reduce √x part in prime factorization.
 
 5/27/2018
 
 10:00-10:53 ACC
 
 Key:
  - Inclusion Exclusion Principle to count numbers co-prime with `x` O(√x+2^𝜔(x))
  - Amortized O(1) time to track edge of circle for each `x`
  - Prime factorization optimization by sieve
 
 Summary:
  - too difficult for me 😞😞😞😞
   - inclusion-exclusion principle to count co-prime numbers
   - fast prime factorization by sieve
   - O(R) linear edge detection
 
 */

// fast prime factorization with sieve
const int MAX_N=1e6+10;
struct PrimeFact {
public:
  PrimeFact(int N): N(N) {
    // make prime table by sieve
    memset(divp, 0, sizeof divp);
    for(int p=2; p<=this->N; ++p) if(divp[p]==0) {
//      P.push_back(p);
      divp[p]=p;
      for(long long q=1LL*p*p; q>=p&&q<=N; q+=p) if(divp[q]==0) divp[q]=p;
    }
  }
  vector<long long> fact(long long n) {
    vector<long long> res;
    while(n>1) res.push_back(divp[n]), n/=divp[n];
    sort(res.begin(),res.end());
    return res;
  }
//  vector<int> P; // list of prime numbers
private:
  int N,divp[MAX_N];
};

// naiive prime factorization with trial division
vector<LL> distinctPrimeFactors(LL n) {
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}

class TheRoundCityDiv1 {
public:
  long long find(int R) {
    LL res=1;
    PrimeFact pf(R);
    
    LL y=R;
    FOR(x,1,R) {
      while(1LL*x*x+1LL*y*y>1LL*R*R) --y;
      int Y=y;
      vector<LL> P=pf.fact(x);
      P.erase(unique(P.begin(),P.end()),P.end());
      LL cur=0;
      int N=SZ(P);
      REP(mask,1<<N) {
        LL a=1;
        REP(i,N) if(mask&(1<<i)) a*=P[i];
        int sign=__builtin_popcount(mask)%2==0?1:-1;
        cur+=sign*(Y/a);
      }
//      dump3(x,Y,cur);
      res+=cur;
    }
    return 4*res;
  }
};

LL euler_phi(LL n) {
  LL res=n;
  // prime factorization
  for(LL p=2; p*p<=n; ++p) if(n%p==0) {
    res=res/p*(p-1);
    while(n%p==0) n/=p;
  }
  if(n!=1) res=res/n*(n-1);
  return res;
}
LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
class TheRoundCityDiv1_wrong {
  public:
  /*
  long long find(int R) {
    if(R==1) return 4;
    LL res=8;
    FOR(y,1,R) {
      for(int x=1; x<R&&x*x+y*y<=R*R; ++x) {
        if(gcd(x,y)==1) res+=4;
      }
    }
    return res;
  }*/
  
  long long find_x(int R) {
    if(R==1) return 4;
    LL res=8;
    int P=floor(1.0*R/sqrt(2.0));
    
    dump2(R,P);
    
    FORE(n,2,P) res+=8*euler_phi(n);
    FOR(y,P+1,R) {
      int ok=1,ng=R;
      while(abs(ok-ng)>1) {
        int mid=(ok+ng)/2;
        (mid*mid+y*y<=R*R?ok:ng)=mid;
      }
      dump2(ok,y);
      FORE(n,2,ok) {
        if(gcd(y,n)==1) {
//          dump2(n,y);
          res+=8;
        }
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("TheRoundCityDiv1.sample");

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

bool do_test(int r, long long __expected) {
    time_t startClock = clock();
    TheRoundCityDiv1 *instance = new TheRoundCityDiv1();
    long long __result = instance->find(r);
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
        int r;
        from_stream(r);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(r, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1526519183;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheRoundCityDiv1 (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
