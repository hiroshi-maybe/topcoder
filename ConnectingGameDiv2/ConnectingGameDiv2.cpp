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
 
 9/17/2017
 
 16:46-17:03 dijkstra's algorithm
 17:34 (432.74 pt) 1WA
 17:38 add missing moves and system test passed
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+637
    - Dijkstra's algorithm
    - mention to min-cut approach too
    - shorter than mine by processing each cell as different vertices
  - http://torus711.hatenablog.com/entry/20141024/1414159692
    - Dijkstra's algorithm
    - mention to min-cut approach too
  - http://kmjp.hatenablog.jp/entry/2014/10/26/1030
    - min-cut max flow (Dinic's algorithm)
 
 writer's comment:
  - http://snuke.hatenablog.com/entry/2014/10/24/014124
 
 key:
  - transform to graph problem
  - 8-connected cells are incident
  - min-cut of planar graph is shortest path
 
 summary:
  - interesting graph problem
  - figured out Dijkstra's algorithm quickly 👍
  - solved by myself 👍
  - conversion to graph was a bit complex
 
 submit solutions
  - flow
    - https://community.topcoder.com/stat?c=problem_solution&rm=324150&rd=16080&pm=13507&cr=23056829
    - https://community.topcoder.com/stat?c=problem_solution&rm=324168&rd=16080&pm=13507&cr=23172452
  - Dijkstra's algorithm
    - https://community.topcoder.com/stat?c=problem_solution&rm=324134&rd=16080&pm=13507&cr=23107134
  - Floyd-warshall
    - https://community.topcoder.com/stat?c=problem_solution&rm=324147&rd=16080&pm=13507&cr=23184967
 
 */

VI moves={-1,0,1};
unordered_map<int,int> W[2505];
int dist[2505];
class ConnectingGameDiv2 {
  public:
  int getmin(vector<string> board) {
    int M=SZ(board),N=SZ(board[0]);
    unordered_map<char,int> S;
    REP(i,M)REP(j,N) S[board[i][j]]++;
    int V=SZ(S)+2;
    vector<char> cs;
    FORR(kvp,S) cs.push_back(kvp.first);
    sort(cs.begin(),cs.end());
    unordered_map<char,int> IM;
    REP(i,SZ(cs)) IM[cs[i]]=i;
    vector<vector<int>> B(M,vector<int>(N,-1));
    REP(i,M)REP(j,N) B[i][j]=IM[board[i][j]]+1;
    
    REP(i,V) W[i].clear();
    REP(i,M) {
      int v1=B[i][0];
      W[0][v1]=S[cs[v1-1]];
      int v2=B[i][N-1];
      W[v2][V-1]=0;
    }
    REP(i,M) REP(j,N) {
      int u=B[i][j],ru=S[cs[u-1]];
      FORR(dx,moves) {
        FORR(dy,moves) {
          int i2=i+dx,j2=j+dy;
          if(i2<0||i2>=M||j2<0||j2>=N) continue;
          int v=B[i2][j2];
          if(v==u) continue;
          int rv=S[cs[v-1]];
          
          W[u][v]=rv,W[v][u]=ru;
        }
      }
    }
    
    const int Inf=M*N;
    REP(i,V) dist[i]=Inf;
    set<II> Q; Q.emplace(0,0); dist[0]=0;
    
    while(SZ(Q)) {
      int u,d;
      auto it=Q.begin();
      tie(d,u)=*it; Q.erase(it);
      
      FORR(kvp, W[u]) {
        int v=kvp.first,w=kvp.second;
        if(dist[v]>d+w) {
          auto it2=Q.find({v,dist[v]});
          if(it2!=Q.end()) Q.erase(it2);
          dist[v]=d+w;
          Q.emplace(dist[v],v);
        }
      }
    }
    
    return dist[V-1];
  }
};

// CUT begin
ifstream data("ConnectingGameDiv2.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    ConnectingGameDiv2 *instance = new ConnectingGameDiv2();
    int __result = instance->getmin(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505691935;
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
        cout << "ConnectingGameDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
