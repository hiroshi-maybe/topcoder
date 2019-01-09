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
 
 9/20/2017
 
 8:41-8:53 design
 9:00 pause
 9:50 implement
 9:58 debug
 10:18 sample 2 doesn't pass
 10:40 I cannot understand why sample's result is correct 🤔
 
 19:30 understand problem correctly and implement
 20:30 1WA in system test
 20:40 fix overflow bug and corner case with one vertex and hit TLE
 20:47 optimized code by sort. system test passed.
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+635
  - http://kmjp.hatenablog.jp/entry/2014/10/05/1030
  - http://torus711.hatenablog.com/entry/20141005/1412522366
  - http://sucrose.hatenablog.com/entry/2014/10/05/230214
 
 9/24/2017
 
 it takes O(V) to brute force removed edge e.
 suppose we get T1 and T2 from T. anyway we need to connect T1 and T2 by edge e.
 maximal diameter f(T1,T2,e) = f(T1)+f(T2)+weight(e)
 
 finding a longest path in a tree is a classical problem:
  - CLRS exercise 22.2-8
  - proof
    - https://www.quora.com/How-does-following-algorithm-for-finding-longest-path-in-tree-work
    - http://www.prefield.com/algorithm/graph/tree_diameter.html
  - editorial of contest
    - http://kmjp.hatenablog.jp/entry/2014/05/05/0930
    - http://torus711.hatenablog.com/entry/20140504/1399210328
    - https://www.slideshare.net/chokudai/arc022
 
 key:
  - it's possible to calculate tree diameter with O(V) time
 
 summary:
  - It took a lot of time to solve
    - first misunderstanding of problem affected following analysis
    - I was unfamiliar with classic longest path problem in tree
 
 19:15-19:36 add solution with tree diameter
 
 submit solutions
  - two dfs to calculate tree diameter
    - https://community.topcoder.com/stat?c=problem_solution&rm=323948&rd=16078&pm=13416&cr=22869652
    - https://community.topcoder.com/stat?c=problem_solution&rm=323942&rd=16078&pm=13416&cr=23078492
 
 */

// O(V^2) time
vector<pair<int,LL>> E[2001];
class LonglongestPathTree {
public:
  int V;
  pair<int,int> ng={-1,-1};
  
  pair<LL,int> dfs(int u, int pre) {
    int maxv=u; LL maxl=0;
    FORR(p, E[u]) {
      int v=p.first; LL w=p.second;
      if(v==pre) continue;
      if(make_pair(u,v)==ng||make_pair(v,u)==ng) continue;
      
      auto p2=dfs(v,u);
      if(p2.first+w>maxl) {
        maxl=p2.first+w;
        maxv=p2.second;
      }
    }
    return {maxl,maxv};
  }
  
  LL diameter(int u) {
    auto p=dfs(u,-1);
    int ep=p.second;
    auto p2=dfs(ep,-1);
    return p2.first;
  }
  
  long long getLength(vector<int> A, vector<int> B, vector<int> L) {
    this->V=SZ(A)+1;
    REP(i,V) E[i].clear();
    REP(i,SZ(A)) {
      int u=A[i],v=B[i],w=L[i];
      E[u].emplace_back(v,w);
      E[v].emplace_back(u,w);
    }
    
    LL res=diameter(0);
    REP(i,SZ(A)) {
      int u=A[i],v=B[i];
      this->ng={u,v};
      LL d=diameter(u)+diameter(v)+1LL*L[i];
      res=max(res, d);
    }
    
    return res;
  }
};

// tree dp
class LonglongestPathTree_org {
public:
  int V;
  
  long long getLength(vector<int> A, vector<int> B, vector<int> L) {
    this->V=SZ(A)+1;
    REP(i,V) E[i].clear();
    REP(i,SZ(A)) {
      int u=A[i],v=B[i],w=L[i];
      E[u].emplace_back(v,w);
      E[v].emplace_back(u,w);
    }

    LL res=0;
    REP(u,V) {
      vector<pair<LL,LL>> xs;
      FORR(p,E[u]) {
        submax=0;
        LL x=subtree(p.first,u,p.second)+p.second;
        submax=max(submax,x);
//        if(u==1) dump4(u,p.first,x,submax);
        xs.emplace_back(x,submax);
      }
      
      sort(xs.rbegin(),xs.rend());
      if(SZ(xs)) {
        res=max(res,xs[0].first);
      }
      if(SZ(xs)>1) {
        res=max(res,xs[0].first+xs[1].first);
      }
      if(SZ(xs)>2) {
        res=max(res,xs[0].first+xs[1].first+xs[2].second);
        res=max(res,xs[1].first+xs[2].first+xs[0].second);
        res=max(res,xs[2].first+xs[0].first+xs[1].second);
      }
      
      /*
      int M=SZ(xs);
      REP(i,M) {
        res=max(res,xs[i].first);
        FOR(j,i+1,M) {
          res=max(res, xs[i].first+xs[j].first);
          REP(k,M) if(k!=i&&k!=j) {
  //        dump4(xs[i].first,xs[j].first,xs[k].second,xs[i].first+xs[j].first+xs[k].second);
          res=max(res, xs[i].first+xs[j].first+xs[k].second);
          }
        }
      }*/
    }
    
    return res;
  }
  bool debug=false;
  LL submax=0;
  LL subtree(int u, int pre, LL w) {
    vector<LL> xs;
    FORR(p,E[u]) if(p.first!=pre) {
      xs.push_back(subtree(p.first, u,p.second)+p.second);
    }
    if(xs.empty()) return 0;
    sort(xs.rbegin(),xs.rend());
//    if(debug) dump(u);
//    if(debug) dumpAR(xs);
    LL res=xs.front();
    if(SZ(xs)>1) submax=max(submax,res+xs[1]+w);
    
    return res;
  }
};

class LonglongestPathTree_wrong {
  public:
  int V;
  
  pair<LL,VI> dfs(int u, int pre, LL dist, VI &cur) {
//    dump3(u,pre,dist);
    LL res1=dist; VI res2=cur;
    FORR(p,E[u]) {
      int v=p.first, w=p.second;
      if(v==pre) continue;
      cur.push_back(v);
      auto p2=dfs(v,u,dist+w,cur);
      if(res1<p2.first) {
        res1=p2.first;
        res2=p2.second;
      }
      cur.pop_back();
    }
    return {res1,res2};
  }
  
  long long getLength(vector<int> A, vector<int> B, vector<int> L) {
    this->V=SZ(A)+1;
    REP(i,V) E[i].clear();
    REP(i,SZ(A)) {
      int u=A[i],v=B[i],w=L[i];
      E[u].emplace_back(v,w);
      E[v].emplace_back(u,w);
//      dump3(u,v,w);
    }
    
    VI maxpath; LL d=0;
    REP(u,V) {
      if(SZ(E[u])==1) {
//        dump(u);
        VI path={u};
        auto p=dfs(u,-1,0,path);
        if(p.first>d) {
          d=p.first;
          maxpath=p.second;
        }
      }
    }
    dumpAR(maxpath);
    LL res=d;
    FOR(i,1,SZ(maxpath)-1) {
      int pre=maxpath[i-1],cur=maxpath[i],next=maxpath[i+1];
      FORR(p,E[cur]) {
        if(p.first==pre) continue;
        if(p.first==next) continue;
        
        submax=0;
        LL x=subtree(p.first,cur,p.second)+p.second;
        submax=max(submax, x);
        res=max(res, d+submax);
      }
    }
    
    return res;
  }
  
  LL submax=0;
  LL subtree(int u, int pre, LL w) {
    vector<LL> xs;
    FORR(p,E[u]) if(p.first!=pre) {
      xs.push_back(subtree(p.first, u,p.second)+p.second);
    }
    if(xs.empty()) return 0;
    sort(xs.begin(),xs.end());
    int res=xs.front();
    if(SZ(xs)>1) submax=max(submax,res+xs[1]+w);
    
    return res;
  }
};

// CUT begin
ifstream data("LonglongestPathTree.sample");

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

bool do_test(vector<int> A, vector<int> B, vector<int> L, long long __expected) {
    time_t startClock = clock();
    LonglongestPathTree *instance = new LonglongestPathTree();
    long long __result = instance->getLength(A, B, L);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        vector<int> L;
        from_stream(L);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505835649;
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
        cout << "LonglongestPathTree (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
