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
 
 2/21/2019 SRM751 div2
 
 18:30-19:15 give up
 
 After the contest, I figured out that no need to be connected in the result graph...
 Spanning is misleading name...
 
 2/27/2019
 
 11:35-12:56 I figured out that Eulerian Cycle is the key and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/02/24/1000
 https://www.topcoder.com/blog/single-round-match-751-editorials/
 
 Let's look at each connected component independently.
 There are two necessary conditions to build half graph:
  1. degree of each vertex is even
  2. # of edges is even
 
 Condition #1 is trivial. Let's prove condition #2.
 Suppose there are 2*D degrees. Then there are D edges.
 If we halve degrees, # of edge decreases by D/2.
 Thus # of edges should be even as well.
 
 If condition #1 and #2 hold, we can build Eulerian cycle with even edges.
 It's possible to achieve halving degrees by removing half of edges in Eulerian tour.
 Mark edges in the cycle by parities.
 If either one is erased, remaining subgraph satisfies half of degrees. Below proves it.

 There are two cases for a vertex `u`.
 
 1. `u` is part of cycle with even edges.
  If "in" edge is erased, "out" edge remains. Thus # of degree decreased by exactly D[u]/2
 2. `u` is part of even number of cycles (namely C0,C1) with odd edges.
  If "in" edge is erased in C0, "out" edge is erased in C1 as well.
  In such a case, both "in" and "out" edges remain in C1.
 Therefore # of degree decreases by exactly D[u]/2
 
 From #1 and #2 analysis, if graph has Eulerian cycle with even edges, half graph can be constructed.
 
 Key:
  - Even degree <=> Eulerian cycle
  - Eulerian cycle <=> edges can be tagged by "in" and "out"
 
 */
int N;
VI vviz;

struct UndirectedEulereanPath {
public:
  // input
  int V;
  vector<multiset<int>> G;
  UndirectedEulereanPath() {}
  UndirectedEulereanPath(int V): V(V), G(V) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].emplace(v),G[v].emplace(u);
  }
  vector<int> solve(int u) {
    vector<int> res;
    dfs(u,res);
    return vector<int>(res.rbegin(),res.rend());
  }
private:
  void dfs(int u, vector<int> &res) {
    while(G[u].size()) {
      auto it=G[u].begin();
      int v=*it;
      G[u].erase(it),G[v].erase(G[v].find(u));
      dfs(v,res);
    }
    res.push_back(u);
  }
};

class HalfGraph {
public:
  vector<string> A;
  vector<string> compute(vector<string> AA) {
    this->A=AA;
    N=SZ(A);
    VI D(N,0);
    REP(i,N) {
      REP(j,N) D[i]+=A[i][j]=='1';
      if(D[i]%2==1) return {};
    }
    int ecnt=accumulate(ALL(D),0)/2;
    if(ecnt%2==1) return {};
    UndirectedEulereanPath ec(N);
    REP(j,N)REP(i,j) if(A[i][j]=='1') ec.edge(i,j);
    VV<int> paths;
    vviz=VI(N,0);
    REP(i,N) if(SZ(ec.G[i])) {
      VI path=ec.solve(i);
      paths.push_back(path);
      assert(SZ(path)%2==1);
//      dumpc(path);
    }
    vector<string> res=AA;
    FORR(p,paths)REP(i,SZ(p)/2) {
      int u=p[2*i],v=p[2*i+1];
//      dump(u,v);
      res[u][v]=res[v][u]='0';
    }
    REP(i,N){
      int d=0;
      REP(j,N) d+=res[i][j]=='1';
//      dump(i,d,D[i]);
      assert(d==D[i]/2);
    }
    return res;
  }
};
class HalfGraph_wrong {
  public:
  vector<string> A;
  VI viz;
  void dfs(int u) {
    if(viz[u]) return;
    viz[u]=1;
    REP(j,N) if(A[u][j]=='1') dfs(j);
  }
  bool connected() {
    viz=VI(N,0);
    dfs(0);
    return accumulate(ALL(viz),0)==N;
  }
  vector<string> compute(vector<string> AA) {
    this->A=AA;
    N=SZ(A);
    VI D(N,0);
    REP(i,N) {
      REP(j,N) {
        D[i]+=A[i][j]=='1';
      }
      if(D[i]%2==1) return {};
    }
    if(accumulate(ALL(D),0)==0) return A;
    dumpc(D);
    VI ds=D;
    set<II> Q; REP(i,N) if(ds[i]>0) Q.emplace(ds[i],i);
    while(SZ(Q)) {
      auto it=Q.rbegin();
      int d,u; tie(d,u)=*it; Q.erase(*it);
      assert(d>D[u]/2);
      int d2=0,v=-1;
      REP(vv,N) if(A[u][vv]=='1') {
        if(d2<ds[vv]&&ds[vv]>D[vv]/2) {
          A[u][vv]=A[vv][u]='0';
          if(connected()) d2=ds[vv],v=vv;
          A[u][vv]=A[vv][u]='1';
        }
      }
      if(v==-1) {
        dump(u);
        dumpc(ds);
        return {};
      }
      dump(u,v);
      A[u][v]=A[v][u]='0';
      Q.erase({ds[v],v});
      ds[u]--,ds[v]--;
      if(ds[u]>D[u]/2) Q.emplace(ds[u],u);
      if(ds[v]>D[v]/2) Q.emplace(ds[v],v);
    }
    /*
    REP(i,N) {
      REP(j,N) if(A[i][j]=='1'&&ds[i]>D[i]/2&&ds[j]>D[j]/2) {
        A[i][j]=A[j][i]='0';
        dump(i,j);
        ds[i]--,ds[j]--;
      }
      if(ds[i]!=D[i]/2) {
        dump(i);
        dumpc(ds);
        return {};
      }
    }*/
    
    REP(i,N) assert(ds[i]==D[i]/2);
//    assert(connected());
    
    return A;
  }
};

// CUT begin
ifstream data("HalfGraph.sample");

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

bool do_test(vector<string> a, vector<string> __expected) {
    time_t startClock = clock();
    HalfGraph *instance = new HalfGraph();
    vector<string> __result = instance->compute(a);
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
        vector<string> a;
        from_stream(a);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1550802449;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "HalfGraph (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
