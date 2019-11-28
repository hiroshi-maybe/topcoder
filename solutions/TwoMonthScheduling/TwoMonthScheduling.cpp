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
 
 11/27/2019 SRM771 div1
 
 8:32-9:15 give up
 
 11/28/2019
 
 12:00-12:50 got AC before reading editorial (Looked at submit solution though)
 
 https://twitter.com/hanseilimak/status/1200156505619591168
 https://docs.google.com/document/d/e/2PACX-1vSsBDFr8U3VDA7l7WT7dJdTlCRO_vP7fopr9u_dD8JsFGamkLttWqcgComfC_LFfZun0kPQdOXzu9-E/pub
 
 
 */
const int MAX_N=5001;
pair<LL,LL> dp[MAX_N];
class TwoMonthScheduling {
  public:
  int minimumMonths(int W, vector<int> firstMonth0, vector<int> firstMonth1, vector<int> secondMonth0, vector<int> secondMonth1) {
    int L0=SZ(firstMonth0),L1=SZ(firstMonth1);
    int N=L0*L1;
    vector<LL> A(L0*L1),B(L0*L1);
    REP(i1,L1)REP(i0,L0) {
      A[i1*L0+i0]=min(W,firstMonth0[i0]^firstMonth1[i1]);
      B[i1*L0+i0]=min(W,secondMonth0[i0]^secondMonth1[i1]);
    }
//    dumpc(A);
//    dumpc(B);
    const LL Inf=1e10;
    REP(i,N+1)dp[i]={Inf,Inf};
    dp[0]={1,-W};
    vector<LL> cuma(N+1),cumb(N+1);
    REP(i,N) cuma[i+1]=cuma[i]+A[i],cumb[i+1]=cumb[i]+B[i];
    
    REP(i,N) {
      vector<pair<LL,LL>> X={
        {dp[i].first  ,dp[i].second},
        {dp[i].first+1,-W}
      };
      FORR(x,X) {
        LL stam=-x.second;
//        dump(i,x.first,stam);
        int cnt=0;
        FORE(j,i+1,N) {
          if(stam<cuma[j]-cuma[i]) break;
          if(W<cumb[j]-cumb[i]) break;
          ++cnt;
          LL rem=W-(cumb[j]-cumb[i]);
          SMIN(dp[j],{x.first+1, -rem});
//          dump(i,j,dp[j].first,dp[j].second);
        }
      }
    }
//    dump(dp[N].first,dp[N].second);
    return dp[N].first;
  }
};

// CUT begin
ifstream data("TwoMonthScheduling.sample");

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

bool do_test(int workers, vector<int> firstMonth0, vector<int> firstMonth1, vector<int> secondMonth0, vector<int> secondMonth1, int __expected) {
    time_t startClock = clock();
    TwoMonthScheduling *instance = new TwoMonthScheduling();
    int __result = instance->minimumMonths(workers, firstMonth0, firstMonth1, secondMonth0, secondMonth1);
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
        int workers;
        from_stream(workers);
        vector<int> firstMonth0;
        from_stream(firstMonth0);
        vector<int> firstMonth1;
        from_stream(firstMonth1);
        vector<int> secondMonth0;
        from_stream(secondMonth0);
        vector<int> secondMonth1;
        from_stream(secondMonth1);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(workers, firstMonth0, firstMonth1, secondMonth0, secondMonth1, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1574872352;
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
        cout << "TwoMonthScheduling (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
