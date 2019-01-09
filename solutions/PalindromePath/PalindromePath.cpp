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

/**
 
 8/6/2017
 
 10:24-10:45 design done
 10:45-11:07 one failure in sample 2 and found a bug in design. multiple edge pass is needed as shown in the sample
 11:13 time up

 12:45-13:36 read editorials
 - BFS
  - http://kmjp.hatenablog.jp/entry/2015/12/27/0930
 - floyd-warshall like approach with proof of upperbound of the path V^2
  - https://apps.topcoder.com/wiki/display/tc/SRM+677
 
 13:36-13:54 add BFS solution
 
 Dijkstra's algorithm instead of BFS
 - https://community.topcoder.com/stat?c=problem_solution&rm=327770&rd=16627&pm=14100&cr=23127234
 
 BFS
 - https://community.topcoder.com/stat?c=problem_solution&rm=327777&rd=16627&pm=14100&cr=23028795
 - https://community.topcoder.com/stat?c=problem_solution&rm=327774&rd=16627&pm=14100&cr=40100022
 
 Floyd-warshall
 - https://community.topcoder.com/stat?c=problem_solution&rm=327770&rd=16627&pm=14100&cr=23064452
 
 DFS (not sure why this works for loop)
 - https://community.topcoder.com/stat?c=problem_solution&rm=327765&rd=16627&pm=14100&cr=23124930
 
 Keys:
 - p(x,y) forms palindrome
  => ∃z, p(x,y)=p(x,z)+p(z,y) where palindrome(s(x,z),s(z,y))
  => char(x,x')==char(y',y) AND palindrome(s(x',z),s(z,y')) where p(x,z)=e(x,x')+p(x',z), p(z,y)=p(z,y')+e(y',y)
 - edge has unit distance. BFS finds optimal shortest path in such a case.
 - BFS always finds an optimal path. if we ignore longer path, it filters out unnecessary loop by itself like a visited flag.
 - Keep pair of vertices in BFS queue.
 
 Summary:
  - sample was clearly mentioning that loop happens
    - loop happens. that means dfs like approach is hard without max depth.
    - we know endpoint of wanting path. it's straightforward to start search from vertex pair of `0` and `1`
    - weight of edge is a unit distance. it makes sense to use BFS.
 
 */

char E[21][21];
int dist[21][21]; // min dist(0-x)+dist(1-y)
int Inf=1e9;
class PalindromePath {
public:
  int shortestLength(int V, vector<int> A, vector<int> B, string C) {
    ZERO(E);
    REP(i,V)REP(j,V) dist[i][j]=Inf;
    REP(i,SZ(A)) {
      int u=A[i],v=B[i];
      E[u][v]=E[v][u]=C[i];
    }

    queue<II> Q;
    Q.emplace(0,1);
    dist[0][1]=0;
    
    int res=Inf;
    
    while(SZ(Q)) {
      auto p=Q.front(); Q.pop();
      int x=p.first,y=p.second;
      
      if(x==y) res=min(res, dist[x][y]);
      if(E[x][y]) res=min(res, dist[x][y]+1);
      
      REP(x2,V)REP(y2,V)if(E[x][x2]&&E[x][x2]==E[y][y2]) {
        if(dist[x2][y2]>dist[x][y]+2) {
          dist[x2][y2]=dist[x][y]+2;
          Q.emplace(x2,y2);
        }
      }
    }
    
    return res>=Inf ? -1 : res;
  }
};

class PalindromePath_wrong {
  public:
  vector<II> E[21]; // v,char
  bool isPalidrome(string s) {
    int l=0,r=SZ(s)-1;
    while(l<r) if(s[l++]!=s[r--]) return false;
    return true;
  }
  
  int shortestLength(int V, vector<int> A, vector<int> B, string C) {
    dump(V);
    REP(i,21) E[i].clear();
    REP(i,SZ(A)) {
      int u=A[i],v=B[i];
      E[u].emplace_back(v,C[i]-'a');
      E[v].emplace_back(u,C[i]-'a');
    }
    
    set<tuple<int,string,int,int>> Q;
    Q.emplace(0,"",1<<0,0);
    
//    dump("start");
    
    while(SZ(Q)) {
//      dump2(SZ(Q),"x");
      int dist,mask,u; string s;
      auto it = Q.begin();
      tie(dist,s,mask,u) = *it; Q.erase(it);
      
//      dump4(dist,s,mask,SZ(Q));
      
      if (u==1) {
        if(isPalidrome(s)) return SZ(s);
        else continue;
      }
      FORR(pair,E[u]) {
        int v=pair.first;
        char c = 'a'+pair.second;
//        dump2(v,c);
        if((mask>>v)&1) continue;
        
        Q.emplace(dist+1,s+c,mask|(1<<v),v);
      }
//      dump(SZ(Q));
    }
    
    return -1;
  }
};

// CUT begin
ifstream data("PalindromePath.sample");

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

bool do_test(int n, vector<int> a, vector<int> b, string c, int __expected) {
    time_t startClock = clock();
    PalindromePath *instance = new PalindromePath();
    int __result = instance->shortestLength(n, a, b, c);
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
        int n;
        from_stream(n);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        string c;
        from_stream(c);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, a, b, c, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502040251;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PalindromePath (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
