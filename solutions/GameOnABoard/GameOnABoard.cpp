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
 
 11/19/2017
 
 15:15-15:30 analysis
 15:30-15:45 implementation
 15:45-15:48 debug and 1WA (486.98 pt)
 15:53-15:58 fixed a bug and system test passed
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+583
   - interesting idea to use deque in shortest path problem
   - 0-1 BFS: http://codeforces.com/blog/entry/22276
  - http://kmjp.hatenablog.jp/entry/2013/06/20/1030
  - http://emkcsharp.hatenablog.com/entry/SRM583/GameOnABoard
 
 Key:
  - score `L` is computed by shortest distance
  - V=1600 is too large for Floyd-Warshall
  - Bob's move is position whose shortest distance from Alice's position is maximum
  - Computing shortest path for all Alice's move is possible by Dijkstra's algorithm
   - O(V*(V+E)*lg V) = O(R*C*(V+4*V)*lg V) ≈ 2*10^8
 
 Summary:
  - trivial problem solved by Dijkstra's algorithm though, 1WA 👎
    - actually no need to check source point because we are interested in largest shortest distance
 
 Solution with deque:
  - https://community.topcoder.com/stat?c=coder_room_stats&rd=15503&cr=23036521
 
 11/20/2017
 
 23:42-23:49 add solution with 0-1 BFS
 
 Item is pushed to the Q exactly same number of times in both Dijkstra's algorithm and 0-1 BFS.
 However Dijkstra's algorithm is slower by lg V times.
 
 */
int dist[1600];
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };
class GameOnABoard {
  public:
  int R,C;
  vector<string> G;
  const int Inf = 1e5;
  // Dijkstra's algorithm, 489 (ms) in worst test case
  int f_dijkstra(int i0, int j0) {
    REP(u,1600) dist[u]=Inf;
    int o=i0*C+j0;
    dist[o]=G[i0][j0]-'0';
    set<II> Q; Q.emplace(dist[o],o);
    while(SZ(Q)) {
      auto it=Q.begin();
      int d=(*it).first, u=(*it).second; Q.erase(it);
      int i=u/C,j=u%C;
      
      FORR(m,moves) {
        int i2=i+m.first,j2=j+m.second;
        if(i2<0||i2>=R||j2<0||j2>=C) continue;
        
        int d2=d+G[i2][j2]-'0';
        int v=i2*C+j2;
        if(dist[v]>d2) {
          auto it2=Q.find({dist[v],v});
          if(it2!=Q.end()) Q.erase(it2);
          Q.emplace(d2,v);
          dist[v]=d2;
        }
      }
    }
    
    int res=0;
    REP(i,R)REP(j,C) res=max(res,dist[i*C+j]);
    //if(i!=i0||j!=j0 /* bug: i!=i0&&j!=j0 */) {
//      res=max(res,dist[i*C+j]);
//    }
    return res;
  }
  
  // 0-1 BFS, 105 (ms) in worst test case
  int f(int i0, int j0) {
    REP(u,1600) dist[u]=Inf;
    int o=i0*C+j0;
    dist[o]=G[i0][j0]-'0';
    deque<II> Q; Q.emplace_back(dist[o],o);
    while(SZ(Q)) {
      auto p=Q.front();
      int d=p.first, u=p.second; Q.pop_front();
      int i=u/C,j=u%C;
      
      FORR(m,moves) {
        int i2=i+m.first,j2=j+m.second;
        if(i2<0||i2>=R||j2<0||j2>=C) continue;
        
        int delta=G[i2][j2]-'0';
        int d2=d+delta;
        int v=i2*C+j2;
        if(dist[v]>d2) {
          dist[v]=d2;
          if(delta==0) Q.emplace_front(d2,v);
          else Q.emplace_back(d2,v);
        }
      }
    }
    
    int res=0;
    REP(i,R)REP(j,C) res=max(res,dist[i*C+j]);
    //if(i!=i0||j!=j0 /* bug: i!=i0&&j!=j0 */) {
    //      res=max(res,dist[i*C+j]);
    //    }
    return res;
  }
  
  int optimalChoice(vector<string> B) {
    this->R=SZ(B),this->C=SZ(B[0]);
    this->G=B;
    
    int res=Inf;
    REP(i,R)REP(j,C) res=min(res,f(i,j));
    return res;
  }
};

// CUT begin
ifstream data("GameOnABoard.sample");

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

bool do_test(vector<string> cost, int __expected) {
    time_t startClock = clock();
    GameOnABoard *instance = new GameOnABoard();
    int __result = instance->optimalChoice(cost);
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
        vector<string> cost;
        from_stream(cost);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cost, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1511133315;
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
        cout << "GameOnABoard (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
