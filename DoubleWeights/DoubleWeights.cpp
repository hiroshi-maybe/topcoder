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
typedef vector < VI > VVI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef tuple<int, int, int, int> IIII;
typedef tuple<int, int, int> III;

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
 
 7/29/2017
 
 17:46-18:22 passed system test (258.39 pt)

 7/30/2017
 
 read editorials
 - https://apps.topcoder.com/wiki/display/tc/SRM+685
  - interesting idea. we have two parameters of weight. converting G to G' where vertices are pairs of weights and original vertex (v,w) in G
  - compute shortest path to (1,w). res = w1*w2 where w1*w2 = min { w1*w2, w1 cost at (1,w2) }
 
 10:30-11:02 add editorial solution
 
 DP solution
 - https://community.topcoder.com/stat?c=problem_solution&rm=328287&rd=16689&pm=14191&cr=40389566
 - less efficient than Dijkstra though, enough for problem size
 - looks like kind of bellmanford?
 
 11:17-11:30 add bellmanford solution
 
 BFS solution
 - https://community.topcoder.com/stat?c=problem_solution&rm=328282&rd=16689&pm=14191&cr=22907329
 - Generally Dijkstra is optimized BFS. Thus it's possible to solve by BFS too.
 
 DFS solution
 - https://community.topcoder.com/stat?c=problem_solution&rm=328291&rd=16689&pm=14191&cr=23169695
 - avoid inifite loop by marking visited flag
 
 12:30-12:48 add DFS solution
 12:54-13:04 add BFS solution
 
 */

// BFS, O(V!) time
class DoubleWeights {
public:
  int INF = 1e9;
  int minimalCost(vector<string> W1, vector<string> W2) {
    int V=SZ(W1);
    VI dist1(V, INF);
    VI dist2(V, INF);
    
    queue<int> Q;
    Q.push(0);
    dist1[0]=0, dist2[0]=0;
    while(SZ(Q)) {
      int u = Q.front(); Q.pop();
      REP(v,V) if(u!=v && W1[u][v]!='.') {
        int w1=dist1[u]+W1[u][v]-'0', w2=dist2[u]+W2[u][v]-'0';
        if(dist1[v]!=INF && dist2[v]!=INF&&w1*w2>dist1[v]*dist2[v]) continue;
        dist1[v]=w1, dist2[v]=w2;
        Q.push(v);
      }
    }
    
    return dist1[1]>=INF||dist2[1]>=INF ? -1 : dist1[1]*dist2[1];
  }
};

// DFS, O(V!) time
class DoubleWeights_dfs {
public:
  VI dist;
  int V;
  int INF = 1e9;
  VI viz;
  vector<string> W1, W2;
  
  void dfs(int u, int d1, int d2) {
    if(viz[u]) return;
    if(d1*d2>dist[u]) return;
    
    dist[u]=d1*d2;
    viz[u] = true;
    
    REP(v, V) if(W1[u][v]!='.') {
      dfs(v,d1+W1[u][v]-'0',d2+W2[u][v]-'0');
    }
    
    viz[u] = false;
    return;
  }
  
  int minimalCost(vector<string> WW1, vector<string> WW2) {
    W1=WW1, W2=WW2;
    V=SZ(W1);
    dist = VI(V, INF);
    viz = VI(V,0);
    
    dfs(0, 0, 0);
    
    return dist[1]>=INF ? -1 : dist[1];
  }
};

// Bellmanford, O(V^3*WMAX)
class DoubleWeights_bellmanford {
public:
  int minimalCost(vector<string> W1, vector<string> W2) {
    int V=SZ(W1);
    int MAXW = 20*9;
    int INF = 1e9;
    VVI dist(MAXW+1, VI(V, INF));
    
    dist[0][0] = 0;
    REP(_,V) REP(u,V) REP(w2,MAXW+1) REP(v,V) if(W1[u][v]!='.' && dist[w2][u]<INF) {
      int x1=dist[w2][u]+W1[u][v]-'0', x2=w2+W2[u][v]-'0';
      if(x2>MAXW) continue;
      dist[x2][v] = min(dist[x2][v], x1);
    }
    
    int res=INF;
    REP(w,MAXW+1) if(dist[w][1]<INF) res=min(res,dist[w][1]*w);
    return res>=INF ? -1 : res;
  }
};

class DoubleWeights_dijkstra2 {
public:
  int minimalCost(vector<string> W1, vector<string> W2) {
    int V=SZ(W1);
    int MAXW = 20*9;
    int INF = 1e9;
    set<III> Q; // w1 cost, w2 cost, node
    VVI dist(MAXW+1, VI(V, INF)); // w2 cost, node -> w1 cost
    
    dist[0][0]=0, Q.emplace(0,0,0);
    
    while(SZ(Q)) {
      int w1,w2,u;
      tie(w1,w2,u) = *(Q.begin()); Q.erase(Q.begin());
      
      REP(v,V) if(W1[u][v]!='.') {
        int x1=w1+W1[u][v]-'0', x2=w2+W2[u][v]-'0';
        if(x2>MAXW) continue;
        if(x1>dist[x2][v]) continue;
        
        auto cur=Q.find(make_tuple(dist[x2][v],x2,v));
        if (cur!=Q.end()) Q.erase(cur);
        
        Q.emplace(x1,x2,v);
        dist[x2][v] = x1;
      }
    }
    
    int res=INF;
    REP(w,MAXW+1) if(dist[w][1]<INF) res=min(res,dist[w][1]*w);
    return res>=INF ? -1 : res;
  }
};

// Dijkstra's algorithm, O(E+V*lg V) time
class DoubleWeights_org {
  public:
  int minimalCost(vector<string> W1, vector<string> W2) {
    int V=SZ(W1);
    VI viz(V,false);
    unordered_map<int, set<IIII>::iterator> P;
    set<IIII> Q; // cost, w1 sum, w2 sum, node
    FOR(u,1,V) {
      Q.emplace(INT_MAX, 0, 0, u);
      P[u] = Q.find(make_tuple(INT_MAX, 0, 0, u));
    }
    Q.emplace(0,0,0,0);
    P[0]=Q.find(make_tuple(0,0,0,0));
    
    while(SZ(Q)) {
      int w, w1s, w2s, u;
      IIII cur = *(Q.begin()); Q.erase(cur);
      tie(w,w1s,w2s,u) = cur;
      viz[u]=true;
      
      if(u==1) return w==INT_MAX ? -1 : w;
      REP(v,V) if (!viz[v]&&v!=u&&W1[u][v]!='.') {
        auto& it = P[v];
        int ww,ww1s,ww2s,v;
        tie(ww,ww1s,ww2s,v) = *it;
        int x1 = w1s+W1[u][v]-'0', x2 = w2s+W2[u][v]-'0';
        if(x1*x2<ww) {
          Q.erase(it);
          Q.emplace(x1*x2, x1, x2, v);
          P[v] = Q.find(make_tuple(x1*x2, x1, x2, v));
        }
      }
    }
    return -1;
  }
};

// CUT begin
ifstream data("DoubleWeights.sample");

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

bool do_test(vector<string> weight1, vector<string> weight2, int __expected) {
    time_t startClock = clock();
    DoubleWeights *instance = new DoubleWeights();
    int __result = instance->minimalCost(weight1, weight2);
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
        vector<string> weight1;
        from_stream(weight1);
        vector<string> weight2;
        from_stream(weight2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(weight1, weight2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501375607;
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
        cout << "DoubleWeights (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
