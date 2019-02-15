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

/*
 
 2/14/2019
 
 15:26-16:46 pause (I figured out bipartite matching. However resolving remaining blacks was challenge)
 17:00-18:12 I figured out and implemented. However I got WA.
 18:24 fixed implementation bug and got AC!!!
 
 https://www.topcoder.com/blog/single-round-match-749-editorials/
  - greedy
 http://kmjp.hatenablog.jp/entry/2019/02/06/0930
  - matching
 https://twishort.com/Bmvnc
  - greedy
  - https://snuke.hatenablog.com/entry/2019/01/04/004133
 https://twitter.com/satanic0258/status/1091692581677760512
 https://twitter.com/beet_aizu/status/1091691979723821056
 
 */

const int MAX_V=1e3;
class MaxBipartiteMatching {
public:
  MaxBipartiteMatching(int V) : V(V) {}
  int match[MAX_V];

  void addEdge(int u, int v) {
    assert(u<V&&v<V);
    E[u].push_back(v);
    E[v].push_back(u);
  }
  
  int solve() {
    int res=0;
    memset(match, -1, sizeof(match));
    for(int u=0; u<V; ++u) if(match[u]<0) {
      memset(viz,0,sizeof viz);
      res+=dfs(u);
    }
    
    return res;
  }
private:
  int V;
  vector<int> E[MAX_V];
  bool viz[MAX_V];
  
  // find augmenting path in residual network
  bool dfs(int u) {
    viz[u]=true;
    for(auto v : E[u]) {
      int w=match[v];
      if(w<0||(!viz[w]&&dfs(w))) {
        match[v]=u;
        match[u]=v;
        return true;
      }
    }
    return false;
  }
};

class TransformBoardDiv1 {
  public:
  int N,M;
  VI res;
  vector<string> S;
  void show(vector<string> &S) {
    cerr<<endl;
    REP(i,N) {
      REP(j,M) cerr<<S[i][j];
      cerr<<endl;
    }
    cerr<<endl;
  }
  void f(int r1, int c1, int r2, int c2) {
    //dump(r1,c1,r2,c2,S[r1][c1],S[r2][c2]);
    assert(r1<=r2&&c1<=c2);
    assert(r1!=r2||c1!=c2);
    if(r1==r2||c1==c2) move(r1,c1,r2,c2);
    else {
      move(r1,c1,r1,c2);
      move(r1,c2,r2,c2);
    }
  }
  void move(int r1, int c1, int r2, int c2) {
    assert(0<=r1&&0<=r2&&0<=c1&&0<=c2);
    assert(r1<N&&r2<N&&c1<M&&c2<M);
//    dump(r1,c1,r2,c2,S[r1][c1],S[r2][c2]);
    if(S[r1][c1]=='#'&&S[r2][c2]=='.') {
      swap(S[r1][c1],S[r2][c2]);
    } else if(S[r1][c1]=='#'&&S[r2][c2]=='#') {
      S[r1][c1]='.',S[r2][c2]='.';
    } else {
      assert(false);
    }
    res.push_back(r1 * 1000000 + c1 * 10000 + r2 * 100 + c2);
  }
  vector<int> getOperations(vector<string> SS, vector<string> T) {
    this->N=SZ(SS),this->M=SZ(SS[0]),this->S=SS;
    MaxBipartiteMatching matching(2*N*M);
    
//    show(S),show(T);
    
    vector<II> bs;
    REP(i,N)REP(j,M)if(S[i][j]=='.'&&T[i][j]=='#') bs.emplace_back(i,j);
    REP(i1,N)REP(j1,M) {
      if(S[i1][j1]=='#'&&T[i1][j1]=='.') {
        REP(i2,N)REP(j2,M)if(i1<=i2&&j1<=j2&&S[i2][j2]=='.'&&T[i2][j2]=='#') {
          matching.addEdge(i1*M+j1,N*M+i2*M+j2);
        }
      }
    }
    int L=SZ(bs);
    int n=matching.solve();
    if(n<L) return {-1};
    REP(i,N)REP(j,M)if(matching.match[N*M+i*M+j]!=-1) {
      int u=matching.match[N*M+i*M+j];
      int i2=i,j2=j,i1=u/M,j1=u%M;
      assert(S[i1][j1]=='#');
      assert(S[i2][j2]=='.');
      dump(i1,j1,i2,j2,S[i1][j1],S[i2][j2]);
      if(i1!=i2&&j1!=j2&&S[i1][j2]=='#') {
        f(i1,j2,i2,j2),f(i1,j1,i1,j2);
      } else {
        f(i1,j1,i2,j2);
      }
    }
    
//    show(S),show(T);
    
    vector<II> rem;
    REP(i,N)REP(j,M) {
      if(T[i][j]=='#') assert(S[i][j]=='#');
      if(S[i][j]=='#'&&T[i][j]=='.') rem.emplace_back(i,j);
    }
    sort(ALL(rem));
    L=SZ(rem);
    if(L%2==1) return {-1};
    dump(L);
    REP(i,L/2) {
      auto p1=rem[2*i],p2=rem[2*i+1];
      int i1=p1.first,j1=p1.second,i2=p2.first,j2=p2.second;
      assert(S[i1][j1]=='#'&&S[i2][j2]=='#');
      if(i1==i2) f(i1,j1,i2,j2);
      else if(j1==j2) f(i1,j1,i2,j2);
      else if(j1<j2) {
        if(S[i1][j2]=='#') f(i1,j2,i2,j2),f(i1,j1,i1,j2);
        else f(i1,j1,i1,j2),f(i1,j2,i2,j2);
      } else {
        f(i1,j1,i2,j1),f(i2,j2,i2,j1);
      }
    }
    
//    show(S),show(T);
    assert(S==T);
    
    return res;
  }
};

// CUT begin
ifstream data("TransformBoardDiv1.sample");

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

bool do_test(vector<string> start, vector<string> target, vector<int> __expected) {
    time_t startClock = clock();
    TransformBoardDiv1 *instance = new TransformBoardDiv1();
    vector<int> __result = instance->getOperations(start, target);
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
        vector<string> start;
        from_stream(start);
        vector<string> target;
        from_stream(target);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(start, target, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1550186797;
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
        cout << "TransformBoardDiv1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
