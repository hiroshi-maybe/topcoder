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
 
 11/2/2019 SRM770
 
 9:00-10:09 AC
 
 */

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}

const LL MOD=1000000007;
class DeleteArrays {
  public:
  vector<long long> doDelete(int NA, int NB, int NC, long long X, long long Y, long long Z) {
    return f(NA,NB,NC,X,Y,Z);
    /*
    while(true) {
      int a=genRandNum(2,100),b=genRandNum(2,100),c=genRandNum(2,100);
      f(a,b,c,a,b,c);
      dump(a,b,c);
    }*/
  }

  vector<long long> f(int NA, int NB, int NC, long long X, long long Y, long long Z) {
    vector<LL> A(NA),B(NB),C(NC);
    A[0]=33,A[1]=42,B[0]=13,C[0]=7,C[1]=2;
    FOR(i,2,NA) A[i]=(5LL*A[i-1]+7LL*A[i-2])%MOD+1;
    FOR(i,1,NB) B[i]=11LL*B[i-1]%MOD+1;
    FOR(i,2,NC) C[i]=(5LL*C[i-1]+7LL*C[i-2])%MOD+1;
    
    if(NA<NB) swap(NA,NB),swap(A,B),swap(Y,Z);
    if(NA<NC) swap(NA,NC),swap(A,C),swap(X,Y);
    if(NB<NC) swap(NB,NC),swap(B,C),swap(Z,X);
    LL suma=accumulate(ALL(A),0LL),sumb=accumulate(ALL(B),0LL),sumc=accumulate(ALL(C),0LL);
    
    sort(ALL(A)),sort(ALL(B)),sort(ALL(C));
      //reverse(ALL(A)),reverse(ALL(B)),reverse(ALL(C));
    if(NA>=(NB+NC)) {
      int rem=NA-(NB+NC);
      LL cost=X*NB+Z*NC;
      LL res0=accumulate(A.begin(),A.begin()+rem,0LL);
      LL sum=suma-res0+sumb+sumc;
      return {res0,cost+sum};
    }
    
    if((NA+NB+NC)%2==0) {
      LL p=(NA+NB-NC)/2,q=(-NA+NB+NC)/2,r=(NA-NB+NC)/2;
      assert(0<=p&&p<=min(NA,NB)&&0<=q&&q<=min(NB,NC)&&0<=r&&r<=min(NC,NA));
      if(0<=p&&p<=min(NA,NB)&&0<=q&&q<=min(NB,NC)&&0<=r&&r<=min(NC,NA)) {
        LL cost=X*p+Y*q+Z*r+suma+sumb+sumc;
        return {0LL,cost};
      }
    }
    
    LL res0=min({A[0],B[0],C[0]});
    if(res0==B[0]) swap(NA,NB),swap(A,B),swap(Y,Z);
    else if(res0==C[0]) swap(NA,NC),swap(A,C),swap(X,Y);
    
    LL sum=suma+sumb+sumc-res0;
    NA-=1;
    LL p=(NA+NB-NC)/2,q=(-NA+NB+NC)/2,r=(NA-NB+NC)/2;
    LL cost=X*p+Y*q+Z*r+sum;
    return {res0,cost};
  }
};

// CUT begin
ifstream data("DeleteArrays.sample");

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

bool do_test(int a, int b, int c, long long x, long long y, long long z, vector<long long> __expected) {
    time_t startClock = clock();
    DeleteArrays *instance = new DeleteArrays();
    vector<long long> __result = instance->doDelete(a, b, c, x, y, z);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        long long x;
        from_stream(x);
        long long y;
        from_stream(y);
        long long z;
        from_stream(z);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, c, x, y, z, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1572710408;
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
        cout << "DeleteArrays (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
