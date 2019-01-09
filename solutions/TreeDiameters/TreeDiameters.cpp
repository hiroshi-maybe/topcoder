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
typedef pair<int,int> II;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/9/2017
 
 17:00-17:15 time up
 17:42-17:57
 19:45-19:55 greedy came up with me and passed samples
 20:10 BFS idea tracing tree from leaves
 20:50 give up
 
 22:50-23:02 read solutions
  - http://kmjp.hatenablog.jp/entry/2016/12/27/0900
  - https://community.topcoder.com/stat?c=problem_solution&rd=16848&rm=329475&cr=22860847&pm=14462
 23:17-23:59 passed samples but TLE for one test case :(
 24:25 passed system test by reducing array dimension from two to one
 
 Tree diameter
 i)  diameter is odd -> vertex is center
 ii) diameter is even -> edge is center
 
 tree in graph representation
 -> i) search from leaves ii) search from inner vertices
 -> in this case, ii is right approach.
 
 Count up in efficient way in one dimension array. It's a bit tricky part in implemantation perspective.
 two dimension array hit TLE :(
 
 7/12/2017
 
 Researched more solutions and found two more techniques
  - https://community.topcoder.com/stat?c=problem_solution&rd=16848&rm=329478&cr=40379086&pm=14462
  - https://community.topcoder.com/stat?c=problem_solution&rd=16848&rm=329475&cr=40499879&pm=14462
 
 - Adding dummy nodes to force center of the tree to be a vertex (not edge)
 - Sum of product of all pairs by Sum(x) and Sum(x^2)
  - ∑ {x[i]*x[j]|i!=j} = (∑{x[i]|i=1..n})^2 - ∑{x[i]^2|i=1..n})/2
  - http://www.geeksforgeeks.org/sum-product-pairs-array-elements/
 
 7/13/2017
 
 18:21-18:41 add solution with dummy vertex
 
 */

VI E[2001];
int cnt[2002];
int sum[1002];
int sum2[1002];

class TreeDiameters {
public:
  void dfs(int t, int u, int d, int prev) {
    ++cnt[d];
    FORR(v,E[u]) if(v!=prev) dfs(t,v,d+1,u);
  }

  int getMax(vector<int> p) {
    REP(i,1001) E[i].clear();
    int V=SZ(p)+1;
    REP(i,SZ(p)) {
      // dummy vertex `V+1+i`
      E[p[i]].push_back(V+1+i), E[V+1+i].push_back(p[i]);
      E[i+1].push_back(V+1+i), E[V+1+i].push_back(i+1);
    }
    
    int res=0;
    REP(u,2*V) {
      memset(sum,0,sizeof sum);
      memset(sum2,0,sizeof sum2);
      FORR(v,E[u]) {
        memset(cnt,0,sizeof cnt);
        dfs(u, v, 1, u);
        for(int d=1; d<V; ++d) sum[d]+=cnt[d], sum2[d]+=cnt[d]*cnt[d];
      }
      
      for(int d=1; d<V; ++d) res = max(res, (sum[d]*sum[d]-sum2[d])/2);
    }
    
    return res;
  }
};
           
class TreeDiameters_org {
public:
  int cnt[1001];
  int num[1001];
  int sum[1001];
  
  int maxd=0;
  void dfs(int t, int u, int d, int prev) {
    maxd=max(d,maxd);
    FORR(v,E[u]) {
      if (v==prev) continue;
      ++cnt[d];
      dfs(t,v,d+1,u);
    }
  }

  int getMax(vector<int> p) {
    REP(i,1001) E[i].clear();
    int V=SZ(p)+1;
    REP(i,SZ(p)) E[p[i]].push_back(i+1), E[i+1].push_back(p[i]);
    
    int res=1;
    
    // vertex is center
    REP(s,V) {
      maxd=0;
      memset(num,0,sizeof num);
      memset(sum,0,sizeof sum);
      
      FORR(t, E[s]) {
        memset(cnt,0,sizeof cnt);
        cnt[0]=1;
        dfs(t,t,1,s);
        
        /*
        REP(d,maxd) {
          sum[d]+=num[d]*cnt[d];
          res=max(res,sum[d]);
          num[d]+=cnt[d];
        }*/
        REP(d,maxd) {
          sum[d]+=cnt[d];
          num[d]+=cnt[d]*cnt[d];
        }
      }
      
      REP(d,maxd) {
        res = max(res, (sum[d]*sum[d]-num[d])/2);
      }
    }
    
    // edge is center
    REP(i,SZ(p)) {
      maxd=0;
      memset(num,0,sizeof num);
      memset(sum,0,sizeof sum);

      int s1=i+1,s2=p[i];
      
      FORR(t, E[s1]) {
        if (t==s2) continue;
        memset(cnt,0,sizeof cnt);
        cnt[0]=1;
        dfs(t,t,1,s1);
        REP(d,maxd) num[d]+=cnt[d];
      }
      FORR(t, E[s2]) {
        if (t==s1) continue;
        memset(cnt,0,sizeof cnt);
        cnt[0]=1;
        dfs(t,t,1,s2);
        REP(d,maxd) {
          sum[d]+=cnt[d]*num[d];
          res=max(res,sum[d]);
        }
      }
    }
    
    return res;
  }
};

class TreeDiameters_wrong {
  public:
  int dp[1005][1005]; // node, dist -> count
  int getMax(vector<int> p) {
    memset(dp,0,sizeof dp);
    int N=SZ(p)+1;
    vector<SETI> es(N);
    REP(i,SZ(p)) {
      es[p[i]].insert(i+1), es[i+1].insert(p[i]);
    }
    queue<II> Q;
    REP(u,N) {
      if(es[u].size()==1) {
        int v=*(es[u].begin());
        Q.emplace(u,v);
        es[v].erase(u);
      }
      dp[u][0]=1;
    }
    
    int res = 1;
    while(Q.size()>1) {
      auto pair=Q.front(); Q.pop();
      int u=pair.first, v=pair.second;
      dump2(u,v);
      REP(d,1005) res=max(res, dp[u][d]*dp[v][d]);
      
      REP(d,1000) {
        dp[v][d+1]+=dp[u][d];
      }
      if (es[v].size()==1) {
        int w=*(es[v].begin());
        Q.emplace(v,w);
        es[w].erase(v);
      }
    }
    
    auto pair=Q.front();
    int u=pair.first;
    dump(u);
    REP(d,1005){
      res = max(res, dp[u][d]*(dp[u][d]-1)/2);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("TreeDiameters.sample");

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

bool do_test(vector<int> p, int __expected) {
    time_t startClock = clock();
    TreeDiameters *instance = new TreeDiameters();
    int __result = instance->getMax(p);
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
        vector<int> p;
        from_stream(p);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(p, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499644800;
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
        cout << "TreeDiameters (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
