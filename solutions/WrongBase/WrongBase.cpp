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
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) {  cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

/*
 
 2/21/2019
 
 20:45-21:15 give up
 
 2/28/2019
 
 11:30-13:10 read editorials and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/02/24/0930
 https://www.topcoder.com/blog/single-round-match-751-editorials/
 https://twitter.com/satanic0258/status/1098788488890073088
 https://twitter.com/satanic0258/status/1098812259374063616
 
 Even after knowing approach of BSGS, I couldn't solve by myself.
 I didn't know how to leverage primitive root condition, because generally discrete log can be solved even when `a` is not primitive root.
 
 Firstly `g` is primitive root.
 g^(P-1)/2 ≢ 1 (mod P), g^(P-1)/7 ≢ 1 (mod P), g^(P-1)/17 ≢ 1 (mod P)
 Above is showing that for any divisor of P-1 (except P-1 itself), g^(2^x*7^y*17^z)≢1 (mod P).
 Thus P-1 is the first `k` s.t. g^k≢1 (mod P) <=> g is primitive root. 
 
 Trick is the same one as used to compute discrete root.
 
 `g` is primitive root <=> there exists `y` s.t. g^y=h
 Exponent can be exchanged by the unique `y` for (g,h).
 Y[i] = h^x[i] = (g^y)^x[i] = (g^x[i])^y = (a+i*d)^y
 
 Once `y` is computed, we can compute Y[i] in O(log MOD) step.
 Total runtime is O(sqrt(MOD)+N*log MOD).
 
 Key:
  - primitive root => reduce problem to discrete logarithm
  - discrete logarithm => BSGS
 
 */

const int MOD=998244353;
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
int powmod(int _a, int b, int MOD) {
  long long a=_a;
  long long res=1;
  for(int mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a,res%=MOD;
    a*=a,a%=MOD;
  }
  return (int)res;
}
int modlog(int a, int b, int MOD) {
  int sqrtM=(int)sqrt(MOD+.0)+1;
  long long ga=powmod(a,sqrtM,MOD);
  unordered_map<int, int> G;
  long long cur=ga;
  for(int p=1; p<=sqrtM; ++p) {
    if(!G.count(cur)) G[cur]=p;
    cur=cur*ga%MOD;
  }
  int res=MOD+10;
  cur=b;
  for(int q=0; q<=sqrtM; ++q) {
    if(G.count(cur)) {
      res=min(res,G[cur]*sqrtM-q);
    }
    cur=cur*a%MOD;
  }
  if(res>MOD) res=-1;
  if(res>=0) assert(powmod(a,res,MOD)==b);
  return res;
}

class WrongBase {
  public:
  int getSum(int g, int h, int a, int d, int N) {
    int y=modlog(g,h,MOD);
    if(y<0) return 0;
    ModInt res;
    REP(i,N) {
      ModInt z=ModInt(a+i*d).pow(y);
      res+=z;
    }
    return res.val;
  }
};

// CUT begin
ifstream data("WrongBase.sample");

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

bool do_test(int g, int h, int a, int d, int n, int __expected) {
    time_t startClock = clock();
    WrongBase *instance = new WrongBase();
    int __result = instance->getSum(g, h, a, d, n);
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
        int g;
        from_stream(g);
        int h;
        from_stream(h);
        int a;
        from_stream(a);
        int d;
        from_stream(d);
        int n;
        from_stream(n);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(g, h, a, d, n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1550810672;
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
        cout << "WrongBase (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
