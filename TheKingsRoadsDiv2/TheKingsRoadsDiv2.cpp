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
 
 9/5/2017
 
 9:22-10:30 (373.14 pt)
 17:00-17:30 try BFS instead of looking at degree
 17:33 system test passed
 
 editorials:
  - http://kmjp.hatenablog.jp/entry/2015/02/19/0930
  - http://mayokoex.hatenablog.com/entry/2015/03/20/205715
  - http://torus711.hatenablog.com/entry/20150227/1425050883
 
 19:08-19:35 add solution by count check in dfs
 
 tree:
  - no cycle
    - visited vertex set is updated only once
  - all nodes are connected
    - |visited| = N
 
 full binary tree:
  - all the nodes have 0 or 2 children
   - |children(u)| = 0 or 2
 
 perfect binary tree:
  - in any subtree, number of nodes in left subtree is same as one in right subtree
  - number of nodes are 2^h-1 for a tree whose height is `h`
    - |left tree| = |right tree|
 
 => degree properties
  root: degree=2, cnt=1
  leaf: degree=1, cnt=2^(h-1)
  others: degree=3, cnt=2(h-1)-2
 
 key:
  - brute-force removed edges
  - check if graph is full perfect binary tree
    - binary tree: https://en.wikipedia.org/wiki/Binary_tree

 summary:
  - analysis reached that I can solve by checking if graph is full perfect binary tree
  - didn't have idea to find root by degree=2. thus it was tough to check graph
   - if root is determined, it's easy to check by dfs
 
 */
VI E[1025];
class TheKingsRoadsDiv2 {
public:
  int N;
  const int Inf=1e5;
//  MAPII D;
  VI viz;
  int dfs(int u, int pre) {
    if(viz[u]) return -Inf;
    viz[u]=true;
//    ++D[SZ(E[u])];
    VI cnt;
    FORR(v,E[u]) if(pre!=v) {
      cnt.push_back(dfs(v,u));
    }
    if(SZ(cnt)!=2&&SZ(cnt)!=0) return -Inf;
    if(SZ(cnt)==2&&cnt[0]!=cnt[1]) return -Inf;
    return accumulate(cnt.begin(),cnt.end(),1);
  }
  
  string getAnswer(int H, vector<int> A, vector<int> B) {
    N=SZ(A);
    if(H==1) return "Correct";
    REP(i,N) A[i]=A[i]-1, B[i]=B[i]-1;
    REP(i,N) {
      REP(j,N) E[j].clear();
      REP(j,N) if(i!=j) {
        int u=A[j],v=B[j];
        E[u].emplace_back(v);
        E[v].emplace_back(u);
        //        dump2(u,v);
      }
      
      int root=-1;
      REP(u,N) if(SZ(E[u])==2) root=u;
      if(root==-1) continue;
      
      viz=VI(N,0);
//      D=MAPII();
      viz[root]=true;
//      ++D[2];
      
      int l=dfs(E[root][0],root), r=dfs(E[root][1],root);
      if(l<0||r<0) continue;
      if(l!=r) continue;
      if(count(viz.begin(),viz.end(),1)!=N) continue;
      
      // degree check is redandunt
//      if(D[1]!=(1<<(H-1))) continue;
//      if(D[2]!=1) continue;
//      if(D[3]!=((1<<(H-1))-2)) continue;
      return "Correct";
    }
    
    return "Incorrect";
  }
};


class TheKingsRoadsDiv2_bfs {
  public:
  int N;
  SETI E[1025];
  string getAnswer(int H, vector<int> A, vector<int> B) {
    N=SZ(A);
    REP(i,N) A[i]=A[i]-1, B[i]=B[i]-1;
    REP(i,N) {
      REP(j,N) E[j].clear();
      REP(j,N) if(i!=j) {
        int u=A[j],v=B[j];
        E[u].emplace(v);
        E[v].emplace(u);
//        dump2(u,v);
      }
      
//      if(i!=1) continue;
      
      bool ok=true;
      VI viz(N,0);
      SETI Q;
      REP(u,N) if(SZ(E[u])==1) Q.emplace(u);
      for(int h=H-1; h>=0; --h) {
        int n=1<<h;
//        dumpAR(Q);
        if(SZ(Q)!=n) { ok=false; break; }
        MAPII X;
        REP(_,n) {
          auto it=Q.begin(); Q.erase(it);
          int u=*it;
          if(viz[u]) { ok=false; break; }
          viz[u]=true;
          FORR(v,E[u]) if(!viz[v]) {
            ++X[v];
//            E[v].erase(u);
          }
        }
        if(!ok) break;
        Q.clear();
        FORR(kvp,X) if(kvp.second==2) Q.emplace(kvp.first);
      }
      
      /*
      for(int h=H-1; h>=0; --h) {
        int n=1<<h;
        SETI ls;
        REP(u,N) { if(SZ(E[u])==1) {
          int v=*(E[u].begin());
          if(ls.count(v) || v==u) { ok=false; break; }
          E[u].clear();
          ls.emplace(u);
        }}
        if(!ok) {
//          dumpAR(ls);
          break;
        }
//        dump(n);
        dumpAR(ls);
//        dumpAR(E[2]);
        if(n==1) {
          REP(j,N) if(SZ(E[j])!=0) { ok=false; break; }
          break;
        }
        if(SZ(ls)!=n) {
//          dump2(n,SZ(ls));
//          dumpAR(ls);
          ok=false; break;
        }
        REP(u,N) FORR(l,ls) if(E[u].count(l)) E[u].erase(l);
      }*/
  
      if(ok) { /*dump(i);*/ return "Correct"; }
    }
    return "Incorrect";
  }
};

// CUT begin
ifstream data("TheKingsRoadsDiv2.sample");

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

bool do_test(int h, vector<int> a, vector<int> b, string __expected) {
    time_t startClock = clock();
    TheKingsRoadsDiv2 *instance = new TheKingsRoadsDiv2();
    string __result = instance->getAnswer(h, a, b);
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
        int h;
        from_stream(h);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(h, a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504628537;
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
        cout << "TheKingsRoadsDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
