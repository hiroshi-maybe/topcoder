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
 
 12/10/2017
 
 15:44-15:54 analysis
 15:55-16:17 submit and system test passed (305.07 pt)
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+576
   - dfs
  - http://kmjp.hatenablog.jp/entry/2013/04/22/0900
   - bfs
  - http://ekaing.hatenablog.com/entry/2013/04/12/205314
   - Dijkstra's algorithm
  - http://tatsyblog.sakura.ne.jp/wordpress/contests/topcoder/950/
   - bfs
 
 Key:
  - At most O(R) ladders. We can search reachability to coing by DFS in O(R*C)
 
 Summary:
  - It was not hard to reduce to graph problem
  - I spent most of time to build graph
  - It took a bit time to find a bug of start position left most (=(R-1)*C)
  - I figured out that binary search works though, I didn't take it to keep code simple.
 
 */

// O(R^2*C) time
int viz[2500];
vector<II> E[2500];
class ArcadeManao {
  public:
  int R,C;
  int T;
  void dfs(int u, int D) {
    if(viz[u]) return;
    viz[u]=true;
    FORR(p,E[u]) {
      int v=p.first,w=p.second;
      if(w<=D) dfs(v,D);
    }
  }
  
  bool ok(int D) {
    ZERO(viz);
    dfs((R-1)*C,D);
    /*
    REP(i,R) {
      REP(j,C) {
        if(viz[i*C+j]) cout << '*';
        else cout << '.';
      }
      cout << endl;
    }
    dump2(D,viz[T]);*/
    return viz[T];
  }
  int shortestLadder(vector<string> B, int tr, int tc) {
    --tr,--tc;
    this->R=SZ(B),this->C=SZ(B[0]);
    this->T=C*tr+tc;
//    dump3(R,C,T);
    REP(i,R*C) E[i].clear();
    REP(i,R)REP(j,C) if(B[i][j]=='X') {
      int u=i*C+j;
      if(j>0&&B[i][j-1]=='X') E[u].emplace_back(i*C+j-1,0);
      if(j<C-1&&B[i][j+1]=='X') E[u].emplace_back(i*C+j+1,0);
      int ii=i-1;
      while(ii>=0&&B[ii][j]=='.') --ii;
      if(ii>=0&&B[ii][j]=='X') E[u].emplace_back(ii*C+j,i-ii);
      ii=i+1;
      while(ii<R&&B[ii][j]=='.') ++ii;
      if(ii<R&&B[ii][j]=='X') E[u].emplace_back(ii*C+j,ii-i);
    }
    
    int res=50;
    for(int D=50; D>=0; --D) if(ok(D)) res=D;
    return res;
  }
};

// CUT begin
ifstream data("ArcadeManao.sample");

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

bool do_test(vector<string> level, int coinRow, int coinColumn, int __expected) {
    time_t startClock = clock();
    ArcadeManao *instance = new ArcadeManao();
    int __result = instance->shortestLadder(level, coinRow, coinColumn);
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
        vector<string> level;
        from_stream(level);
        int coinRow;
        from_stream(coinRow);
        int coinColumn;
        from_stream(coinColumn);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(level, coinRow, coinColumn, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512949431;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 576 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ArcadeManao (576 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
