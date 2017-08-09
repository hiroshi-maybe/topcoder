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
typedef tuple< double, int, int > DII;
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

/**
 
 8/8/2017
 
 8:36-8:50 design done
 8:50-9:05 implementation
 9:05-9:26 fixed bugs and passed system test (215.60 pt)
 
 Editorial:
 - http://kmjp.hatenablog.jp/entry/2015/12/11/0930
 - https://apps.topcoder.com/wiki/display/tc/SRM+675
 
 11:03-23:12 add cleaner solution
 
 Key:
  - keep another state in Dijkstra's algorithm
    - it's equivalent to converting |V| graph to k*|V| graph
  - nice to have cost by multiplying twice to avoid rounding problem
 
 Summary:
  - solved 👍
  - bug festival 🥇🏅🎖🏆 👎💢
    - variable name collision
    - double<->int
    - missing update of `dist`
    - swapping position of `u` and `k`
    - boundary condition k>=K
 
 */

int Inf=1e9;
int E[55][55];
int dist[55][55]; //v,k

// O(E+V*lg V) = O(K*N^2 + K*N*lg(K*N)) time
class ShortestPathWithMagic {
public:
  set<DII> Q;
  double getTime(vector<string> D, int K) {
    int V=SZ(D);
    REP(i,V) REP(j,V) {
      E[i][j]=(D[i][j]-'0');
    }
    REP(i,V) REP(k,K+1) dist[i][k]=Inf;
    
    dist[0][K]=0.0;
    Q.emplace(0,0,K);
    
    while(SZ(Q)) {
      int d,u,k;
      auto it=Q.begin(); Q.erase(it);
      tie(d,u,k) = *it;
      
      REP(v,V) if(u!=v) {
        int c1=d+E[u][v]*2;
        push(v,k,c1);
        int c2=d+E[u][v];
        if(k>0) push(v,k-1,c2);
      }
    }
    int res=Inf;
    for(int k=0; k<=K; ++k) res=min(res,dist[1][k]);
    return (double)res/2.0;
  }
  
  void push(int v, int k, int c) {
    if(dist[v][k]<=c) return;
    auto it=Q.find(make_tuple(dist[v][k],v,k));
    if (it!=Q.end()) Q.erase(it);
    dist[v][k] = c;
    Q.emplace(c,v,k);
  }
};

class ShortestPathWithMagic_org {
  public:
  double E[55][55];
  double dist[55][55]; //v,k
  double getTime(vector<string> D, int K) {
    int V=SZ(D);
    REP(i,V) REP(j,V) {
      E[i][j]=(double)(D[i][j]-'0');
    }
    REP(i,V) REP(k,K+1) dist[i][k]=Inf;
    
    set<DII> Q;
    dist[0][0]=0.0;
    Q.emplace(0.0,0,0);
    
    while(SZ(Q)) {
      double d; int k,u;
      auto it=Q.begin(); Q.erase(it);
      tie(d,u,k) = *it;
//      dump3(d,u,k);
      if (k>K) continue;
      
      REP(v,V) if(u!=v) {
        double c1=d+E[u][v];
        if (dist[v][k]>c1) {
//          dump3(c1,v,k);
          auto it2=Q.find(make_tuple(dist[v][k],v,k));
          if (it2!=Q.end()) Q.erase(it2);
          dist[v][k] = c1;
          Q.emplace(c1,v,k);
        }
        
        double c2=d+E[u][v]/2.0;
        if (dist[v][k+1]>c2) {
//          dump3(c2,v,k+1);
          auto it2=Q.find(make_tuple(dist[v][k+1],v,k));
          if (it2!=Q.end()) Q.erase(it2);
          dist[v][k+1] = c2;
          Q.emplace(c2,v,k+1);
        }
      }
    }
//    dump(dist[1][1]);
    double res=Inf;
    for(int k=0; k<=K; ++k) {/* dump2(k,dist[1][k]);*/ if(dist[1][k]<Inf&&res>dist[1][k]) {
      
      res=dist[1][k];
    }}
    return res;
  }
};

// CUT begin
ifstream data("ShortestPathWithMagic.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> dist, int k, double __expected) {
    time_t startClock = clock();
    ShortestPathWithMagic *instance = new ShortestPathWithMagic();
    double __result = instance->getTime(dist, k);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<string> dist;
        from_stream(dist);
        int k;
        from_stream(k);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(dist, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502206599;
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
        cout << "ShortestPathWithMagic (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
