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
struct GaussJordanElimination {
  const double eps=1e-8;
  vector<double> solve(vector<vector<double>> A, vector<double> b) {
    const int N=A.size();
    vector<vector<double>> X(N, vector<double>(N+1)); // Augmented matrix which merges A with b
    for(int i=0; i<N; ++i) {
      for(int j=0; j<N; ++j) X[i][j] = A[i][j];
      X[i][N] = b[i];
    }
    
    for(int i=0; i<N; ++i) {
      // invariant: X[p][p]=1 for p=0..i-1
      int pivot=i;
      for(int j=i; j<N; ++j) {
        // find maximum coefficient to minimize precision error
        if (fabs(X[j][i])>fabs(X[pivot][i])) pivot=j;
      }
      swap(X[i], X[pivot]);
      // solution is undeterministic, or no solution exists
      if (fabs(X[i][i])<eps) return vector<double>();
      
      // X[i][i]=1
      for(int j=i+1; j<=N; ++j) X[i][j]/=X[i][i];
      for(int j=0; j<N; ++j) if (i != j) {
        // row reduction
        for(int k=i+1; k<=N; ++k) X[j][k]-=X[j][i]*X[i][k];
      }
    }
    
    vector<double> xs(N);
    for(int i=0; i<N; ++i) xs[i]=X[i][N];
    return xs;
  }
} GJE;
/*
 
 4/24/2020 SRM784 div1 medium
 
 8:39-9:15 give up
 
 4/25/2020
 
 14:00-16:19 read editorials and got AC
 
 x[0] = comp[0]
 x[1] = comp[1]+∑ { pr(1,i)*x[i] }
 x[2] = comp[2]+∑ { pr(2,i)*x[i] }
 ...
 
 res = x[i] s.t. pattern[i]=A
 
 https://kmjp.hatenablog.jp/entry/2020/04/25/0930
 
 https://twitter.com/uwitenpen/status/1253724200327495688
 https://twitter.com/uwitenpen/status/1253724467173289986
 https://twitter.com/HIR180/status/1253725383175729155
 https://twitter.com/kyort0n/status/1253725435206066176
 https://twitter.com/uwitenpen/status/1253726731040485376
 https://twitter.com/HIR180/status/1253726988314935296
 https://twitter.com/satanic0258/status/1253727314250067968
 
 */

const int MAX_S=1000+1;
const int MAX_N=720+1;
double dp[MAX_S][MAX_N];
class SpeedingUpBozosort {
  public:
  
  double expectedComparisons(vector<int> A, int S) {
    ZERO(dp);
    int N=SZ(A);
    VI B(ALL(A));
    sort(ALL(B));
    map<VI,int> aid;
    VV<int> as;
    VI comp;
    int id=0;
    do {
      aid[B]=id;
      as.push_back(B);
      comp.push_back(0);
      REP(i,N-1) {
        ++comp[id];
        if(B[i]>B[i+1]) break;
      }
      ++id;
    } while(next_permutation(ALL(B)));
//    dumpc(comp);
    
    VV<int> ps;
    map<VI,int> pid;
    VI P(N); REP(i,N) P[i]=i;
    id=0;
    do {
      pid[P]=id++;
      ps.push_back(P);
    } while(next_permutation(ALL(P)));
    
    // transform table from permutation
    VV<int> T(SZ(ps));
    REP(i,SZ(ps)) {
      VI P=ps[i];
      REP(j,N)REP(k,N) {
        swap(P[j],P[k]);
        T[i].push_back(pid[P]);
        swap(P[j],P[k]);
      }
//      dumpc(T[i]);
    }
    
    dp[0][0]=1.0;
    REP(i,S) REP(j,SZ(ps)) FORR(k,T[j]) {
      dp[i+1][k]+=dp[i][j]/N/N;
    }
    
    int M=SZ(as);
    VV<double> mx(M, vector<double>(M,0));
    mx[0][0]=-1;
    FOR(i,1,M) {
      REP(j,SZ(ps)) {
        VI A=as[i],AA(N),P=ps[j];
        REP(i,N) AA[P[i]]=A[i];
        double pr=dp[S][j];
        mx[i][aid[AA]]+=pr;
      }
      mx[i][i]-=1;
    }
    
    /*
    REP(i,SZ(mx)) {
      REP(j,SZ(mx[i])) cout<<mx[i][j]<<" ";
      cout<<endl;
    }*/
    
    vector<double> b(ALL(comp));
    REP(i,SZ(comp)) b[i]=-b[i];
    
    auto res=GJE.solve(mx,b);
    return res[aid[A]];
  }
};

// CUT begin
ifstream data("SpeedingUpBozosort.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> A, int numSwaps, double __expected) {
    time_t startClock = clock();
    SpeedingUpBozosort *instance = new SpeedingUpBozosort();
    double __result = instance->expectedComparisons(A, numSwaps);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> A;
        from_stream(A);
        int numSwaps;
        from_stream(numSwaps);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, numSwaps, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1587742713;
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
        cout << "SpeedingUpBozosort (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
