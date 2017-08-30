#include <fstream> // for greed plugin
#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;

// type alias
typedef long long LL;

typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/*
 
 8/29/2017
 
 9:00-9:04 pause
 18:16-18:46,18:51-19:31 design pre-check, floyd-warshall, union-find
 20:11 sample doesn't pass. time up
 
 22:25-23:35 read editorials and add solution
  - http://kmjp.hatenablog.jp/entry/2015/05/06/0930
    - http://kmjp.hatenablog.jp/entry/2015/05/06/0900
    - d(i,j)+d(j,k)+d(i,k)==even validation
  - https://apps.topcoder.com/wiki/display/tc/SRM+658
  - https://chaingng.github.io/post/srm-658-div2-hard---oddeventreehard/
    - dfs of graph coloring: http://mathworld.wolfram.com/VertexColoring.html
    - 2 colors/bipartite check: http://www.geeksforgeeks.org/bipartite-graph/
  - https://bitbucket.org/temp_impl/topcodersrm/src/tip/SRMClass/0601-0700/Srm658/OddEvenTreeHard.cs?fileviewer=file-view-default
 
 key:
  - odd/even corresponds to graph coloring problem of bipartite graph
  - 3 subproblems to solve
   1. matrix validation
   2. how to fill unknown in matrix with even or odd
   3. how to build tree from even/odd relations
  1. how to validate matrix?
    - X[i][i]=='E'
    - X[i][j]=='?' or X[j][i]=='?' or X[i][j]==X[j][i]
    - other node relation consistency (below 3 approaches are actually equivalent)
      - nodes can be colored by either two colors (dfs in offical editorial)
        - X[i][j] == 'E' ? i and j are same color, X[i][j] == 'O' ? i and j are different color
      - (d(i,k)+d(k,j)) % 2 == d(i,j) (floyd-warshall in my solution)
      - d(i,j)+d(j,k)+d(i,k) is odd (@kmjp's solution)
  2. how to fill unknown?
    - greedily give odd except node `0` (official editorial's approach)
      - this is valid because we can start coloring from any node. the first node can be root.
      - Since we need at least one adjacent node from root, we can give odd (different color) to others greedily
    - brute-force both even and odd. take valid one (mine and @kmjp's solution)
  3. how to build tree?
    - build simplest structure of three layers: {root} - {odd nodes} - {even nodes}
    - union-find tree (I couldn't achieve)
      - see @kmjp's editorial of div1 easy how to do it
 
 summary:
  - I tried to solve trivial pre-check and floyd-warshal validation and build tree by union-find
    - pre-checks were trivial (X[i][i]=='E' AND X[i][j]=='?' or X[j][i]=='?' or X[i][j]==X[j][i])
    - once we get full matrix of even or odd, we can build tree easily (div1 easy problem). I couldn't catch it up.
  - could not build valid tree by union-find. I couldn't catch up below two ideas.
   1. how to fill unknown fields?
    - to build a tree, we need to fill all the '?' fields
    - we can brute force them by either even or odd
    - validation by floyd-warshal (or just DFS) works in O(V^5) time
   2. once we find out relations of even or odd, how to build tree?
    - any node can be root.
    - build three layers leveraging graph coloring property
 
 25:06-25:30 add graph coloring and dfs solution of official editorial
 
 */

int C[51];
class OddEvenTreeHard {
public:
  int V;
  unordered_map<int, VI> NE,EQ;
  bool dfs(int u, int c) {
    bool res=true;
    if(C[u]!=-1) return C[u]==c;
    C[u]=c;
    FORR(v,EQ[u]) res&=dfs(v,c);
    FORR(v,NE[u]) res&=dfs(v,!c);
    return res;
  }
  vector<int> getTree(vector<string> X) {
    V=SZ(X);
    REP(i,V)REP(j,V) {
      // add the other direction because it's undirected. if edge is not added, dfs doesn't work.
      if(X[i][j]=='E') EQ[i].push_back(j),EQ[j].push_back(i);
      else if(X[i][j]=='O') NE[i].push_back(j),NE[j].push_back(i);
    }
    MINUS(C);
    REP(i,V) if(C[i]==-1) {
      if (!dfs(i,i==0?0:1)) return {-1};
    }
    VI O,E;
    REP(i,V) (C[i]?O:E).push_back(i);
    if(O.empty()||E.empty()) return {-1};
    int root=E.front(),odd=O.front();
    VI res;
    res.push_back(root),res.push_back(odd);
    FOR(i,1,SZ(O)) res.push_back(root),res.push_back(O[i]);
    FOR(i,1,SZ(E)) res.push_back(odd),res.push_back(E[i]);
    return res;
  }
};

int mx[51][51];
int tmp[51][51];
// O(V^5) time
class OddEvenTreeHard_floydwarshall {
public:
  int V;
  VI res;
  bool valid() {
    REP(k,V)REP(i,V)REP(j,V) {
      if(tmp[i][k]!=-1&&tmp[k][j]!=-1) {
        if(tmp[i][j]==-1) tmp[i][j]=(tmp[i][k]+tmp[k][j])%2;
        else if(tmp[i][j]!=(tmp[i][k]+tmp[k][j])%2) return false;
      }
    }
    return true;
  }
  
  vector<int> getTree(vector<string> X) {
    this->V=SZ(X);
    REP(i,V) if(X[i][i]=='O') return {-1};
    REP(i,V)REP(j,V) if(X[i][j]!='?'&&X[j][i]!='?'&&X[i][j]!=X[j][i]) return {-1};
    
    MINUS(mx);
    REP(i,V)REP(j,V) {
      if(i==j) mx[i][j]=mx[j][i]=0;
      else if(X[i][j]=='E') mx[i][j]=mx[j][i]=0;
      else if (X[i][j]=='O') mx[i][j]=mx[j][i]=1;
    }
    REP(k,V)REP(i,V)REP(j,V) {
      if(mx[i][k]!=-1&&mx[k][j]!=-1) {
        if(mx[i][j]==-1) mx[i][j]=(mx[i][k]+mx[k][j])%2;
        else if(mx[i][j]!=(mx[i][k]+mx[k][j])%2) return {-1};
      }
    }
    
    REP(i,V)FOR(j,i+1,V) if(mx[i][j]==-1) {
      REP(i,V)REP(j,V) tmp[i][j]=mx[i][j];
      tmp[i][j]=tmp[j][i]=1;
      if(valid()) {
        REP(i,V)REP(j,V) mx[i][j]=tmp[i][j];
        continue;
      }
      tmp[i][j]=tmp[j][i]=0;
      if(valid()) {
        REP(i,V)REP(j,V) mx[i][j]=tmp[i][j];
        continue;
      }
      return {-1};
    }
    
    VI O,E;
    REP(i,V) (mx[0][i]?O:E).push_back(i);
    if(E.empty()||O.empty()) return {-1};
    int root=E.front(),odd=O.front();
    VI res;
    res.push_back(root),res.push_back(odd);
    FOR(i,1,SZ(O)) res.push_back(root),res.push_back(O[i]);
    FOR(i,1,SZ(E)) res.push_back(odd),res.push_back(E[i]);
    return res;
  }
};

// not a valid tree error in system test
class OddEvenTreeHard_wrong {
  public:
  int mx[51][51];
  int V;
  VI res;
  VI uf;
  int find(int u) {
//    dump2(u,uf[u]);
    return u==uf[u]?u:find(uf[u]);
  }
  void unite(int child, int parent) {
    uf[child]=parent;
    res.push_back(child),res.push_back(parent);
    if(SZ(res)>2*V-2) { dumpAR(res); dumpAR(uf); }
    assert(SZ(res)<=2*V-2);
  }
  int depth(int u) {
    if(uf[u]==u) return 0;
    return 1+depth(uf[u]);
  }
  bool united(int u, int v) {
    return find(u)==find(v);
  }
  vector<int> getTree(vector<string> X) {
    this->V=SZ(X);
    REP(i,V) if(X[i][i]=='O') return {-1};
    REP(i,V)REP(j,V) if(X[i][j]!='?'&&X[j][i]!='?'&&X[i][j]!=X[j][i]) return {-1};
    
    MINUS(mx);
    REP(i,V)FOR(j,i+1,V) {
      if(X[i][j]=='E') mx[i][j]=mx[j][i]=0;
      else if (X[i][j]=='O') mx[i][j]=mx[j][i]=1;
    }
    REP(k,V)REP(i,V)REP(j,V) {
      if(mx[i][k]!=-1&&mx[k][j]!=-1) {
        if(mx[i][j]==-1) mx[i][j]=(mx[i][k]+mx[k][j])%2;
        else if(mx[i][j]!=(mx[i][k]+mx[k][j])%2) return {-1};
      }
    }
    
    uf=VI(V);
    REP(i,V) uf[i]=i;
//    dump("edge O");
    REP(i,V)FOR(j,i+1,V) if(mx[i][j]==1) {
      if(!united(i,j)&&SZ(res)<2*V-2) {
//        dump2(i,j);
        unite(i,j);
      }
    }
//    dumpAR(res);
//    dump("edge E");
    REP(i,V)FOR(j,i+1,V) if(mx[i][j]==0&&!united(i,j)&&SZ(res)<2*V-2) {
//      dump2(i,j);
      int d1=depth(i),d2=depth(j);
      if((d1%2)^(d2%2)) {
        unite(find(i),find(j));
      } else if(d1%2==1&&d2%2==1) {
        unite(i,find(j));
      } else {
        // depth is both even
        if(uf[i]!=i) {
          unite(find(j),uf[i]);
        } else if(uf[j]!=j) {
          unite(find(j),uf[i]);
        } else {
          // both root
          bool found=false;
          REP(x,V) if(x!=i&&uf[x]==i) {
            unite(x,find(j));
            found=true;
            break;
          }
          if(!found) return {-1};
        }
      }
    }
    
//    dump("rest");
    REP(i,V) REP(j,V) if(SZ(res)<2*V-2&&find(i)!=find(j)) unite(i,j);
    
    return res;
  }
};

// CUT begin
ifstream data("OddEvenTreeHard.sample");

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

bool do_test(vector<string> x, vector<int> __expected) {
    time_t startClock = clock();
    OddEvenTreeHard *instance = new OddEvenTreeHard();
    vector<int> __result = instance->getTree(x);
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
        vector<string> x;
        from_stream(x);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504022412;
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
        cout << "OddEvenTreeHard (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
