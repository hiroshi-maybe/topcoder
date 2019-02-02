#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) {
  cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...);
}
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"-"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

const int MOD=1e9+7;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};

unordered_set<int> distinctPrimeFactors(int n) {
  assert(n>=1);
  vector<int> res;
  for(int p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.push_back(n);
  return unordered_set<int>(ALL(res));
}

/*
 
 1/26/2019 SRM 748
 
 9:08-10:15 give up
 
 I tried to solve focusing on divisor and multiples in terms of Inclusion Exclusion Principle.
 However I had no progress.
 
 My plans:
  - dp
   => I didn't dig this at all. Eventually this is the right approach
  - math (combinatorics)
  - prime factorization
   - Inclusion Exclusion Principle (intersect operation)
   - bitmask by prime factors
   - Mobious function
 
 2/1/2019
 
 13:00-13:34 got AC
 16:16 add solution by Inclusion Exclusion Principle
 
 https://www.topcoder.com/blog/single-round-match-748-editorials/
 http://kmjp.hatenablog.jp/entry/2019/01/27/0900
 https://community.topcoder.com/stat?c=problem_solution&rm=332036&rd=17397&pm=15292&cr=23080021
 
 I completely missed the most important step to brute-force which comes up with dp easily 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
 
 */

const int MAX_N=501;
const int MAX_S=1001;

struct PrimeFact {
public:
  PrimeFact(int N): N(N) {
    // make prime table by sieve
    divp.resize(N+1,0);
    for(int p=2; p<=this->N; ++p) if(divp[p]==0) {
      P.push_back(p);
      divp[p]=p;
      for(long long q=1LL*p*p; q<=N; q+=p) if(divp[q]==0) divp[q]=p;
    }
  }
  vector<long long> fact(long long n) {
    vector<long long> res;
    while(n>1) res.push_back(divp[n]), n/=divp[n];
    sort(res.begin(),res.end());
    return res;
  }
  vector<int> P; // list of prime numbers
private:
  int N;
  vector<int> divp;
};

PrimeFact pf(MAX_S);

class EraseToGCD {
public:
  int N;
  VI S;
  int countWays(vector<int> S, int GG) {
    this->S=S;
    this->N=SZ(S);
    
    ModInt res;
    int x=0;
    REP(i,N) if(S[i]%GG==0)++x;
    res=ModInt(2).pow(x)-1;
    
    for(int k=2; k*GG<MAX_S; ++k) {
      int x=0,kg=k*GG;
      REP(i,N) if(S[i]%kg==0) ++x;
      if(x==0) continue;
      vector<LL> ps=pf.fact(k);
      set<LL> P(ALL(ps));
      LL y=1; FORR(n,P) y*=n;
      if(y!=k) continue;
      int M=SZ(P),sign=M%2?-1:1;
//      dump(k,kg,x,M,sign);
      res+=ModInt(sign)*(ModInt(2).pow(x)-1);
    }
    return res.val;
  }
};


ModInt F[MAX_S],G[MAX_S];
int cnt[MAX_S];
class EraseToGCD_IEP {
public:
  int N;
  VI S;
  ModInt g(int x) {
    ModInt res=F[x];
    for(int k=2; k*x<MAX_S; ++k) {
      int kx=k*x;
      res-=G[kx];
    }
    return res;
  }
  int countWays(vector<int> S, int GG) {
    this->S=S;
    this->N=SZ(S);
    for(int n=MAX_S-1; n>=1; --n) {
      int x=0;
      REP(i,N) if(S[i]%n==0) ++x;
      cnt[n]=x;
    }
    
    for(int n=MAX_S-1; n>=1; --n) {
      vector<LL> ps=pf.fact(n);
      F[n]=ModInt(2).pow(cnt[n])-ModInt(1);
    }
    for(int n=MAX_S-1; n>=1; --n)  G[n]=g(n);
    return G[GG].val;
  }
};

int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }

ModInt dp[MAX_N][MAX_S];
class EraseToGCD_dp {
public:
  int countWays(vector<int> S, int G) {
    int N=SZ(S);
    REP(i,MAX_N)REP(j,MAX_S)dp[i][j]=ModInt(0);
    REP(i,N) dp[i][S[i]]=ModInt(1);
    REP(i,N-1) REP(j,MAX_S) {
      int a=S[i+1];
      dp[i+1][gcd(a,j)]+=dp[i][j];
      dp[i+1][j]+=dp[i][j];
    }
    return dp[N-1][G].val;
  }
};

class EraseToGCD_wrong {
public:
  int countWays(vector<int> S, int G) {
    
    dump(G);
    
    VI A; REP(i,SZ(S)) if(S[i]%G==0) A.push_back(S[i]/G);
    dumpc(A);
    int N=SZ(A);
    ModInt res(0);
    vector<SETI> P(N);
    REP(i,N) P[i]=distinctPrimeFactors(A[i]);
    REP(i,N) {
      dumpc(P[i]);
      int cnt=0;
      REP(j,N)if(i!=j) {
        dumpc(P[j]);
        bool ok=true;
        FORR(p,P[i]) if(P[j].count(p)) ok=false;
        cnt+=ok;
      }
      dump(i,A[i],cnt);
      res+=ModInt(2).pow(cnt)-1;
    }
    
    vector<pair<string,int>> X={{"abc",1},{"def",10}};
    dumpc(X);
    
    return res.val;
  }
};

// CUT begin
ifstream data("EraseToGCD.sample");

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

bool do_test(vector<int> S, int goal, int __expected) {
    time_t startClock = clock();
    EraseToGCD *instance = new EraseToGCD();
    int __result = instance->countWays(S, goal);
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
        vector<int> S;
        from_stream(S);
        int goal;
        from_stream(goal);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, goal, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1548726422;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "EraseToGCD (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
