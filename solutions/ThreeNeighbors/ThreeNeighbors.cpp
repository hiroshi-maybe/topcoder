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
 
 4/18/2020 TCO2020 R1A
 
 9:15-10:05 AC
 
 https://www.topcoder.com/2020-tco-algorithm-round-1a/
 
 */

vector<pair<int,int>> movesd = { {0,1}/*R*/,{1,1}/*RD*/,{1,0}/*D*/,{1,-1}/*DL*/,{0,-1}/*L*/,{-1,-1}/*UL*/,{-1,0}/*U*/,{-1,1}/*UR*/ };
void show(vector<string> &A) {
  cerr<<endl;
  REP(i,SZ(A)) cerr<<A[i]<<endl;
}
class ThreeNeighbors {
  public:
  vector<string> f(int N) {
    assert(N<=500);
    vector<string> res(50,string(50,'.'));
    REPE(j,24) res[0][2*j]='X';
    REP(x,N) {
      int r=x/24,c=x%24;
      if(r==N/24&&r%2==0) break;
      int i=2*r+1,j=2*c+1;
      if(r%2==1) {
        res[i+1][j-1]=res[i+1][j+1]='X';
      } else {
        if(c%2==0) res[i+1][j-1]='X';
        else res[i+1][j+1]='X';
      }
    }

    int r=N/24;
    if(r%2==0) {
      int i=2*r+4;
      REP(j,50) res[i-2][j]='.';
      for(int j=0; j<=24&&j<=(N%24); ++j) res[i-1][2*j]='X';
      REP(c,N%24) {
        int j=2*c+1;
        if(c%2==0) res[i+1][j-1]='X';
        else res[i+1][j+1]='X';
      }
    }

//    dump(N);
//    show(res);
    int cnt=0;
    REP(i,50)REP(j,50) if(res[i][j]=='.') {
      int x=0;
      FORR(m,movesd) {
        int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=50||jj<0||jj>=50) continue;
        x+=res[ii][jj]=='X';
      }
      if(x==3) ++cnt;
    }
    assert(SZ(res)<=50&&SZ(res[0])<=50);
    assert(cnt==N);
    return res;
  }
  
  vector<string> construct(int N) {
    return f(N);
  }
};

// CUT begin
ifstream data("ThreeNeighbors.sample");

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

bool do_test(int N, vector<string> __expected) {
    time_t startClock = clock();
    ThreeNeighbors *instance = new ThreeNeighbors();
    vector<string> __result = instance->construct(N);
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
        int N;
        from_stream(N);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1587226443;
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
        cout << "ThreeNeighbors (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
