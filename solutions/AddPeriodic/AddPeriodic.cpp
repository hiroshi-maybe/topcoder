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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif
struct Frac {
public:
  // numerator / denominator
  long long n,d;
  Frac(): n(0),d(1) {}
  Frac(int nn) : n(nn), d(1) {}
  Frac(long long nn, long long dd) { norm(nn,dd); }
  Frac(int nn, int dd) { norm(nn,dd); }
  Frac& norm(long long nn, long long dd) {
    assert(dd!=0);
    if(dd<0) nn*=-1,dd*=-1;
    bool neg=nn<0;
    nn=neg?-nn:nn;
    long long g=gcd(nn,dd);
    nn/=g,dd/=g;
    this->n=nn;
    if(neg) this->n=-1*this->n;
    this->d=dd;
    return *this;
  }
  Frac abs() { return Frac(n<0?-n:n,d); }
  Frac inv() { return Frac(d,n); }
  Frac &operator -() { n=-n; return *this; }
  Frac &operator += (Frac that) { long long nn=(long long)n*that.d+(long long)that.n*d,dd=(long long)d*that.d; return norm(nn,dd); }
  Frac &operator -= (Frac that) { *this+=-that; return *this; }
  Frac &operator *=(Frac that) { long long nn=(long long)n*that.n,dd=(long long)d*that.d; return norm(nn,dd); }
  Frac &operator /= (Frac that) { *this*=Frac(that.d,that.n); return *this; }
  Frac operator+(Frac that) const { return Frac(*this)+=that; }
  Frac operator-(Frac that) const { return Frac(*this)-=that; }
  Frac operator*(Frac that) const { return Frac(*this)*=that; }
  Frac operator/(Frac that) const { return Frac(*this)/=that; }
  bool operator < (Frac that) { return (long long)n*that.d<(long long)that.n*d; }
  bool operator > (Frac that) { return that<Frac(*this); }
  bool operator == (Frac that) { return n==that.n&&d==that.d; }
  bool operator <= (Frac that) { return Frac(*this)<that||Frac(*this)==that; }
  bool operator >= (Frac that) { return Frac(*this)>that||Frac(*this)==that; }
  friend ostream& operator<<(ostream& os, const Frac& that) { return os<<that.n<<"/"<<that.d; }
private:
  long long gcd(long long a, long long b) {
    return b==0?a:gcd(b,a%b);
  }
};

/*
 
 6/22/2019 SRM 761
 
 8:00-9:15 give up
 
 6/23/2019
 
 17:35-19:05 read editorial and got AC
 
 https://twitter.com/natsugir/status/1142474526304768000
 https://twitter.com/hotpepsi/status/1142663204570427396
 https://community.topcoder.com/stat?c=problem_solution&rm=332766&rd=17592&pm=15579&cr=22931891
 https://community.topcoder.com/stat?c=problem_solution&rm=332762&rd=17592&pm=15579&cr=23080021
 
 - Computation fits in 64bit integer
 - n/d is easy to compute integer part
 - Division can be done by keep dividing until cycle is found
 - During the division keep numerator to restore result
 
 */
LL gcd(LL a, LL b) {
  return b == 0 ? a : gcd(b, a % b);
}
LL lcm(LL a, LL b) {
  return a/gcd(a,b)*b;
}

LL P10[18];
class AddPeriodic {
public:
  Frac frac(string S) {
    int dot=S.find('.'),pl=S.find('(');
    dump(S,dot,pl);
    string X=S.substr(0,dot);
    string Y=S.substr(dot+1,pl-dot-1);
    string Z=S.substr(pl+1,SZ(S)-pl-2);
    dump(X,Y,Z);
    LL x=stoll(X);
    LL A=P10[SZ(Y)+SZ(Z)]*x;
    if(SZ(Y)) A+=stoll(Y)*P10[SZ(Z)];
    A+=stoll(Z);
    
    LL B=P10[SZ(Y)]*x;
    if(SZ(Y)) B+=stoll(Y);
    
    dump(A,B);
    
    Frac res(A-B,P10[SZ(Z)]-1);
    res*=Frac(1LL,P10[SZ(Y)]);
    dump(res);
    
    return res;
  }
  
  string add(string A, string B) {
    P10[0]=1;
    REP(i,17) P10[i+1]=P10[i]*10;
    auto a=frac(A),b=frac(B);
    auto c=a+b;
    string res;
    LL n=c.n, d=c.d;
    res+=to_string(n/d)+".";
    n%=d;
    map<LL,int> M;
    vector<LL> X;
    for(int i=0; true; ++i) {
      if(M.count(n)) break;
      M[n]=i;
      X.push_back(n);
      n = n*10%d;
    }
    REP(i,SZ(X)) {
      if(X[i]==n) res+='(';
      char c='0'+X[i]*10/d;
      assert(isdigit(c));
      res.push_back(c);
    }
    res.push_back(')');
    return res;
  }
};

/*
class AddPeriodic_wrong {
  public:
  pair<string, int> f(string s) {
    string A,B,C;
    int N=SZ(s);
    string cur="";
    REP(i,N) {
      if(s[i]=='.') A=cur,cur="";
      else if(s[i]=='(') B=cur,cur="";
      else if(s[i]=='(') C=cur;
      else cur+=s[i];
    }
    int L=lcm(SZ(B),SZ(C));
    string CC(L,'0');
    REP(i,L) CC[i]=C[i%SZ(C)];
    int M=SZ(A)+SZ(B)+SZ(CC);
    string X(M,'0'),Y(M,'0');
    REP(i,M) {
      char c;
      if(i<SZ(A)) c=A[i];
      else if(i<SZ(A)+SZ(B)) c=B[i-SZ(A)];
      else c=CC[i-SZ(A)-SZ(B)];
      X[i]=c;
    }
    REP(i,M-SZ(B)) {
      int b=SZ(B);
      char c;
      if(i<SZ(A)) c=A[i];
      else if(i<SZ(A)+SZ(B)) c=B[i-SZ(A)];
      else c=CC[i-SZ(A)-SZ(B)];
      Y[b+i]=c;
    }
    for(int i=M-1; i>=0; --i) {
      int x=X[i],y=Y[i];
      if(x<y) x+=10,assert(i>0),X[i-1]=X[i-1]-1;
      assert(x>=y);
      X[i]='0'+x-y;
    }
    return {X,SZ(B)};
  }
  tuple<string, string, string> g(string s) {
    string A,B,C;
    int N=SZ(s);
    string cur="";
    REP(i,N) {
      if(s[i]=='.') A=cur,cur="";
      else if(s[i]=='(') B=cur,cur="";
      else if(s[i]=='(') C=cur;
      else cur+=s[i];
    }
    return {A,B,C};
  }
  vector<int> f0(string n) {
    VI res;
    for(int i=SZ(n)-1; i>=0; --i) {
      res.push_back(n[i]-'0');
    }
    return res;
  }
  vector<int> f1(string n) {
    VI res;
    REP(i,SZ(n)) {
      res.push_back(n[i]-'0');
    }
    return res;
  }
  void f2(string n, int cnt, VI &A) {
    REP(i,cnt) {
      A.push_back(n[i%SZ(n)]-'0');
    }
  }
  string add(string A, string B) {
    //auto AA=f(A),BB=f(B);
    //if(AA.second<BB.second) swap(AA,BB);
    vector<int> A0,A1,B0,B1;
    auto AA=g(A),BB=g(B);
    A0=f0(get<0>(AA)),B0=f0(get<0>(BB));
    A1=f1(get<1>(AA)),B1=f1(get<1>(BB));
    f2(get<2>(AA),1e5,A1),f2(get<2>(BB),1e5,B1);
    
    
    return "";
  }
};
*/
// CUT begin
ifstream data("AddPeriodic.sample");

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

bool do_test(string A, string B, string __expected) {
    time_t startClock = clock();
    AddPeriodic *instance = new AddPeriodic();
    string __result = instance->add(A, B);
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
        string A;
        from_stream(A);
        string B;
        from_stream(B);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1561215605;
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
        cout << "AddPeriodic (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
