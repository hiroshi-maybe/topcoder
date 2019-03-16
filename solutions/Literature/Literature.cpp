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
 
 3/14/2019
 
 18:51-18:58 pause
 
 3/15/2019
 
 13:27-14:24 analysis
 15:00 give up
 
 15:45-17:00 read editorials
 
 3/16/2019
 
 10:20-11:05 read editorials and got AC
 
 https://www.topcoder.com/blog/single-round-match-752-editorials/
 http://kmjp.hatenablog.jp/entry/2019/03/12/0900
 
 */

double memo[3][1001][1001];
class Literature {
public:
  int N;
  double f(int p, int a, int b) {
    double &res=memo[p][a][b];
    if(res>=0) return res;
    if(a==N||b==N) return res=0.0;
    if(p==0) return res=f(1,a,b)+1.0;
    if(p==1) return res=1.0+(N-b)/(2.0*N)*f(2,a,b+1)+(N+b)/(2.0*N)*f(2,a,b);
    res=(N-a)/(2.0*N)*f(0,a+1,b);
    res+=(N+a)*(N-b)/(4.0*N*N)*f(2,a,b+1);
    res+=(N+a)/(1.0*N)+1.0;
    res/=(1.0-(N+a)*(N+b)/(4.0*N*N));
    return res;
  }
  double expectation(int N, vector<int> AA, vector<int> H) {
    this->N=N;
    int M=SZ(H);
    SETI A(ALL(AA)),cnt[2];
    REP(i,M) if(i%3!=0) {
      int j=i%3-1,a=H[i];
      if(!cnt[1-j].count(a)&&!A.count(a)) cnt[1-j].emplace(a);
      //      dump(i,SZ(cnt[0]),SZ(cnt[1]));
      if(SZ(cnt[j])==N||SZ(cnt[1-j])==N) return i+1;
    }
    MINUS(memo);
    int a0=SZ(cnt[0]),b0=SZ(cnt[1]);
    return f(M%3,a0,b0)+M;
  }
};

class Literature_wrong {
  public:
  double dp[210][1001][1001];
  double expectation(int N, vector<int> AA, vector<int> H) {
    int M=SZ(H);
    SETI A(ALL(AA)),cnt[2];
    REP(i,M) if(i%3!=0) {
      int j=i%3-1,a=H[i];
      if(!cnt[1-j].count(a)&&!A.count(a)) cnt[1-j].emplace(a);
//      dump(i,SZ(cnt[0]),SZ(cnt[1]));
      if(SZ(cnt[j])==N||SZ(cnt[1-j])==N) return i+1;
    }
    ZERO(dp);
    int a0=SZ(cnt[0]),b0=SZ(cnt[1]);
    dump(a0,b0,M);
    dp[0][a0][b0]=1.0;
    double res=0;
    REP(i,200)FOR(a,a0,N)FOR(b,b0,N) if(a!=N&&b!=N){
      if(i%3==0) dp[i+1][a][b]+=dp[i][a][b];
      if(i%3==1) {
        dp[i+1][a][b+1]+=dp[i][a][b]*(N-b)/(2.0*N);
        if(b+1==N) {
          res+=dp[i+1][a][b+1]*(i+M);
          dump(i,a,b,dp[i+1][a][b+1]);
        }
        dp[i+1][a][b]+=dp[i][a][b]*(N+b)/(2.0*N);
      }
      if(i%3==2) {
        dp[i+1][a+1][b]+=dp[i][a][b]*(N-a)/(2.0*N);
        if(a+1==N) {
          res+=dp[i+1][a+1][b]*(i+M);
          dump(i,a,b,dp[i+1][a+1][b]);
        }
        dp[i+1][a][b]+=dp[i][a][b]*(N+a)/(2.0*N);
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("Literature.sample");

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

bool do_test(int n, vector<int> Teja, vector<int> history, double __expected) {
    time_t startClock = clock();
    Literature *instance = new Literature();
    double __result = instance->expectation(n, Teja, history);
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
        int n;
        from_stream(n);
        vector<int> Teja;
        from_stream(Teja);
        vector<int> history;
        from_stream(history);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, Teja, history, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1552557092;
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
        cout << "Literature (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
