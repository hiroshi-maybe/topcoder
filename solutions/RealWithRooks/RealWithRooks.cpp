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
 
 8/3/2019
 
 14:00-14:34 system test failed
 
 8/5/2019
 
 15:10-15:40 read editorial and got AC
 
 https://scrapbox.io/snuke/TCO_2019_Japan_Regional
 https://twitter.com/beet_aizu/status/1157540516335980544?s=20
 
 */

int count(vector<string> B) {
  int R=SZ(B),C=SZ(B[0]),res=0;
  REP(i,R)REP(j,C) if(B[i][j]=='W') {
    int k=i+1;
    while(k<R&&B[k][j]=='.') ++k;
    if(k!=R&&B[k][j]=='B') ++res;
    k=i-1;
    while(k>=0&&B[k][j]=='.') --k;
    if(k>=0&&B[k][j]=='B') ++res;
    
    k=j+1;
    while(k<C&&B[i][k]=='.') ++k;
    if(k!=C&&B[i][k]=='B') ++res;
    k=j-1;
    while(k>=0&&B[i][k]=='.') --k;
    if(k>=0&&B[i][k]=='B') ++res;
    
  }
  return res;
}

class RealWithRooks {
public:
  vector<string> construct(int R, int C, int N) {
    string X="WB";
    vector<string> res(R,string(C,'.'));

    REPE(w,C) if(w*R>=N) {
      vector<string> B(R,string(C,'.'));
      int n=N;
      REP(i,R)REP(j,w)if(n-->0) B[i][j]=X[(i+j)%2];
      if(count(B)>count(res)) res=B;
    }
    return res;
  }
};

class RealWithRooks_wrong {
  public:
  vector<string> construct(int R, int C, int N) {
    int n=N;
    string X="WB";
    vector<string> res(R,string(C,'.'));
    int a=0;
    while((a+1)*(a+1)<=N&&(a+1)<=min(R,C)) ++a;
    dump(a);
    REP(i,a)REP(j,a) res[i][j]=X[(i+j)%2];
    
    n-=a*a;
    int p=0;
    if(R>=C) {
      while(n>0) {
        int i=a+p/a,j=p%a;
        res[i][j]=X[(i+j)%2];
        ++p,--n;
      }
    } else {
      while(n>0) {
        int i=p%a,j=a+p/a;
        res[i][j]=X[(i+j)%2];
        ++p,--n;
      }
    }
    
//    REP(i,R) dump(res[i]);
    
    return res;
  }
};

// CUT begin
ifstream data("RealWithRooks.sample");

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

bool do_test(int R, int C, int N, vector<string> __expected) {
    time_t startClock = clock();
    RealWithRooks *instance = new RealWithRooks();
    vector<string> __result = instance->construct(R, C, N);
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
        int R;
        from_stream(R);
        int C;
        from_stream(C);
        int N;
        from_stream(N);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(R, C, N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1564808405;
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
        cout << "RealWithRooks (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
