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
const int MOD=1000000007;
//const int MOD=998244353;
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

/*
 
 10/10/2019
 
 8:42-9:15 give up
 
 10/13/2019
 
 11:13-13:26 read editorials and got AC
 
 Firstly E[X=Limak]=∑E[X∈Polar]/P because Limak is one of Polar bear.
 ∑E[X∈Polar] = ∑E[X∈Polar or Grizzly] - ∑E[X∈Polar]
 
 ∑E[X∈Polar or Grizzly] = f(P+G,B)
 ∑E[X∈G] = f(G,P+B)
 
 => res = (f(P+G,B)-f(G,P+B))/P
 
   f(a,b)
 = P(a-vs-a)*(a+b+f(a-1,b)) + P(a-vs-b)*f(a,b-1) + P(b-vs-b)*f(a,b-1)
 
 P(a-vs-a)=C(a,2)/C(a+b,2)
 P(a-vs-b)=a*b/C(a+b,2)
 P(b-vs-b)=C(b,2)/C(a+b,2)
 
 http://kmjp.hatenablog.jp/entry/2019/10/12/1100
 https://docs.google.com/document/d/1XbeqZMHsNjv2J3h8x0PsJnBn4IV8llJx9hT39iQkOcY/edit
 https://twitter.com/beet_aizu/status/1182333804905525249?s=20
 https://twitter.com/kyort0n/status/1182334052394651648?s=20
 https://twitter.com/n_vip/status/1182334310898008065?s=20
 https://twitter.com/risujiroh/status/1182334461859397633?s=20
 https://twitter.com/kmjp_pc/status/1182334563785117696?s=20
 
 */

const int MAX_N=2000+1;
ModInt memo[2*MAX_N][2*MAX_N];
int viz[2*MAX_N][2*MAX_N];
ModInt xc2[3*MAX_N],revxc2[3*MAX_N];
ModInt f(int a, int b) {
  ModInt &res=memo[a][b];
  if(viz[a][b]) return res;
  viz[a][b]=1;
  if(a==0) return res=0;
  if(b==0) return res=ModInt(a)+f(a-1,0);
  
  ModInt revnc2=revxc2[a+b];
  ModInt paa=xc2[a]*revnc2;
  ModInt pab=ModInt(a)*b*revnc2;
  ModInt pbb=xc2[b]*revnc2;
  
  res=pab*f(a,b-1);
  if(a>=2) res+=paa*(ModInt(a)+b+f(a-1,b));
  if(b>=2) res+=pbb*f(a,b-1);
  return res;
}
class PBG {
  public:
  int findEV(int P, int B, int G) {
    FOR(i,1,3*MAX_N) xc2[i]=ModInt(i)*(i-1)/2,revxc2[i]=ModInt(1)/xc2[i];
    ZERO(viz);
    ModInt res=(f(P+G,B)-f(G,P+B))/P;
    return res.val;
  }
};

// CUT begin
ifstream data("PBG.sample");

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

bool do_test(int P, int B, int G, int __expected) {
    time_t startClock = clock();
    PBG *instance = new PBG();
    int __result = instance->findEV(P, B, G);
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
        int P;
        from_stream(P);
        int B;
        from_stream(B);
        int G;
        from_stream(G);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(P, B, G, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1570722177;
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
        cout << "PBG (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
