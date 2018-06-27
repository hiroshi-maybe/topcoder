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
 
 6/26/2018 SRM 735
 
 20:14-21:00 gave up
 
 6/27/2018
 
 14:00-16:03 Read editorials and got AC with solver of modular linear equations
 16:04-17:00 add simpler solution with mod inverse by extended euclid
 
 Editorials:
  - https://www.topcoder.com/blog/single-round-match-735-editorials/
  - http://drken1215.hatenablog.com/entry/2018/06/27/013100
 
 Tweets:
  - https://togetter.com/li/1241123
  - https://twitter.com/beet_aizu/status/1011588699849494528
  - https://twitter.com/_TTJR_/status/1011589226255691776
  - https://twitter.com/hotpepsi/status/1011616966233153537
 
 References:
  - https://qiita.com/drken/items/b97ff231e43bce50199a
  - https://qiita.com/drken/items/eed62619d929c375d689
 
 x^2≡x (mod M) <=> x*(x-1) ≡ 0 (mod M)
 
 Suppose M = p[0]^n[0]*p[1]^n[1]*.. = ∏ { p^n : p∈P }
 
 `x` and `x-1` are relatively prime for any positive integer.
 x and x-1 should not share prime number.
 
 Suppose set of prime numbers for `x` is P_A, one for `x-1` is P_B.
 
   x ≡ 0 (mod A)
   x-1 ≡ 0 (mod B) <=> x ≡ 1 (mod B)
 
 This system of modular linear equations can be solved.
 Or it's possible to show x = a*A s.t. a = A^-1 (mod B) as @drken's editorial.
 
 Key:
  - x^2≡x (mod M) <=> x*(x-1) ≡ 0 (mod M)
   - a ≡ 0 (mod x) => `a` is multiple of `x`
  - x and x-1 are co-prime
  - reduced to modular linear equations
 
 Summary:
  - I couldn't figure out anything 😞
 
 */

vector<pair<LL,LL>> pfact(LL n) {
  map<LL,int> res;
  for(LL p=2; p*p<=n; ++p) {
    while(n%p==0) res[p]++,n/=p;
  }
  if(n>1) res[n]++;
  
  vector<pair<LL,LL>> ans(SZ(res));
  int i=0;
  FORR(kvp,res) {
    LL p=kvp.first,cnt=kvp.second;
    ans[i]={p,1LL};
    REP(_,cnt) ans[i].second*=p;
    ++i;
  }
  return ans;
}

struct ModularLinearEquations {
public:
  ModularLinearEquations() {}
  
  pair<LL, LL> solve(const vector<LL>& A, const vector<LL>& B,
                     const vector<LL>& M) {
    LL b=0,m=1;
    for(LL i=0; i<A.size(); i++) {
      LL p=A[i]*m,q=B[i]-A[i]*b,d=gcd(M[i],p),mi=M[i]/d;
      if (q%d!=0) return make_pair(0,-1); // solution not found
      LL t=(_modinv(p/d,mi)*q/d)%(mi);
      b=b+m*t;
      m*=mi;
    }
    b=(b+m)%m; // ensure that x is non-negative
    return make_pair(b%m,m);
  }
  LL _modinv(LL a, LL m) {
    assert(gcd(a,m)==1);
    LL x,y;
    _extgcd(a,m,x,y);
    return (m+x%m)%m; // ensure mod inverse is non-negative
  }
  LL _extgcd(LL a, LL b, LL& x, LL& y) {
    if(b==0) {
      x=1,y=0;
      return a;
    }
    LL d=_extgcd(b, a%b, y, x);
    y-=(a/b)*x;
    return d;
  }
private:
  LL gcd(LL a, LL b) {
    return b==0?a:gcd(b,a%b);
  }
} MLE;

tuple<int,int,int> extended_euclid(int a, int b) {
  if (b==0) return make_tuple(a, 1, 0);
  
  int d2,x2,y2;
  tie(d2,x2,y2) = extended_euclid(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}

class QuadraticIdentity {
public:
  vector<long long> getFixedPoints(long long M) {
    auto P=pfact(M);
    int N=SZ(P);
    vector<LL> res;
    REP(mask,1<<N) {
      LL A=1,B=1;
      REP(i,N) {
        (((mask>>i)&1)?A:B)*=P[i].second;
      }
      
      LL a=MLE._modinv(A,B);
      res.push_back(a*A);
    }
    sort(res.begin(),res.end());
    while(SZ(res)>500) {
      vector<LL> ans;
      REP(i,SZ(res)) if(i%2==0) ans.push_back(res[i]);
      res=ans;
    }
    return res;
  }
};

class QuadraticIdentity_modLinearEquations {
public:
  vector<long long> getFixedPoints(long long M) {
    auto P=pfact(M);
    int N=SZ(P);
    vector<LL> res;
    REP(mask,1<<N) {
      LL A=1,B=1;
      REP(i,N) {
        (((mask>>i)&1)?A:B)*=P[i].second;
      }
      vector<LL> AA={1,1};
      vector<LL> BB={0,1};
      vector<LL> MM={A,B};
      res.push_back(MLE.solve(AA,BB,MM).first);
    }
    sort(res.begin(),res.end());
    while(SZ(res)>500) {
      vector<LL> ans;
      REP(i,SZ(res)) if(i%2==0) ans.push_back(res[i]);
      res=ans;
    }
    return res;
  }
};

class QuadraticIdentity_org {
  public:
  vector<LL> f(LL M) {
    set<LL> S;
    //    dump2(5LL*5LL,5LL*5LL%M);
    for(LL p=0; p<M; ++p) if((p*p)%M==p) {
      //      dump3(p*p,p*p%M,p*p%M==p);
      S.emplace(p);
//      S.emplace(p*p);
    }
    //    dump(SZ(S));
    vector<LL> res(S.begin(),S.end());
    return res;
  }
  vector<long long> getFixedPoints(long long M) {
    REP(i,M) {
      auto res=f(i);
      dump(i);
      dumpAR(res);
    }
    return {};
  }
};

// CUT begin
ifstream data("QuadraticIdentity.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(long long m, vector<long long> __expected) {
    time_t startClock = clock();
    QuadraticIdentity *instance = new QuadraticIdentity();
    vector<long long> __result = instance->getFixedPoints(m);
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
        long long m;
        from_stream(m);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1530011634;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "QuadraticIdentity (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
