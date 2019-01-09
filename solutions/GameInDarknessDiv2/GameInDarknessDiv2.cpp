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
 
 11/14/2017
 
 9:21-10:20 system test passed (394.42 pt)
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+588
   - dfs
  - http://d.hatena.ne.jp/semiexp/20130813/1376357527
   - problem writer
   - dp
  - http://kmjp.hatenablog.jp/entry/2013/08/13/1000
   - bfs
  - http://kenkoooo.hatenablog.com/entry/2016/04/27/015828
   - bfs
  - http://emkcsharp.hatenablog.com/entry/SRM588/GameInDarknessDiv2
   - bfs
 
 Bob can win if and only if Bob can reach any place except Alice's final position.
 Search space is at most R*C*M. So it's possible to search entire search spaces.
 => DFS and BFS works too
 
 Key:
  - search space is small enough to do even DFS or BFS
  - Bob cannot reach both ps[t] and ps[t+1]
  - Bob needs to make another move after Alice exhausts moves
 
 Summary:
  - Analysis was straightforward
  - Solved by DP by myself 👍
  - It took 20 mins to find a bug 👎
   - Missed to check Alice check in one of two cases
 
 */

// O(R*C*M) time
int viz[51][51][2501];
class GameInDarknessDiv2 {
public:
  int R,C;
  string M;
  vector<II> ps;
  vector<string> B;
  string p1="Alice wins",p2="Bob wins";
  vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };
  void dfs(int i, int j, int t) {
    if(t==SZ(ps)+1) return;
    if(viz[i][j][t]) return;
    if(i==ps[t].first&&j==ps[t].second) return;
    viz[i][j][t]=true;
    FORR(m,moves) {
      int i2=i+m.first,j2=j+m.second;
      if(i2<0||i2>=R||j2<0||j2>=C) continue;
      if(B[i2][j2]=='#') continue;
      if(i2==ps[t].first&&j2==ps[t].second) continue;
      dfs(i2,j2,t+1);
    }
  }
  string check(vector<string> B, vector<string> ms) {
    this->B=B;
    this->R=SZ(B),this->C=SZ(B[0]);
    this->M=""; FORR(m,ms)M+=m;
    ZERO(viz);
    
    int ai=-1,aj=-1,bi=-1,bj=-1;
    REP(ii,R)REP(jj,C) {
      if(B[ii][jj]=='A') ai=ii,aj=jj;
      if(B[ii][jj]=='B') bi=ii,bj=jj;
    }
    assert(ai>=0); assert(bi>=0);
    unordered_map<char,II> T = {
      {'U', {-1, 0}},
      {'D', { 1, 0}},
      {'R', { 0, 1}},
      {'L', { 0,-1}},
    };
    FORR(c,M) {
      ai=ai+T[c].first;
      aj=aj+T[c].second;
      ps.emplace_back(ai,aj);
//      dump3(SZ(ps)-1,ai,aj);
    }
    
    dfs(bi,bj,0);
    bool bob=false;
//    dump3(ps.back().first,ps.back().second,SZ(ps)-1);
    REP(i,R)REP(j,C) {
      if(i==ps.back().first&&j==ps.back().second) continue;
      bob|=viz[i][j][SZ(ps)];
    }
    return bob?p2:p1;
  }
};

// O(R*C*M) time
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };
int memo[51][51][2501];
class GameInDarknessDiv2_org {
  public:
  int R,C;
  string M;
  vector<II> ps;
  vector<string> B;
  string p1="Alice wins",p2="Bob wins";
  bool f(int i, int j, int pi) {
    int &res=memo[i][j][pi];
    if(res>=0) return res;
    if(pi>=SZ(ps)) return true;
    if(i==ps[pi].first&&j==ps[pi].second) return false;
    res=false;
    FORR(m,moves) {
      int i2=i+m.first,j2=j+m.second;
      if(i2<0||i2>=R||j2<0||j2>=C) continue;
      if(B[i2][j2]=='#') continue;
      if(i2==ps[pi].first&&j2==ps[pi].second) continue;
      res|=f(i2,j2,pi+1);
    }
    return res;
  }
  string check(vector<string> B, vector<string> ms) {
    this->B=B;
    this->R=SZ(B),this->C=SZ(B[0]);
    this->M=""; FORR(m,ms)M+=m;
    MINUS(memo);
    
    int ai=-1,aj=-1,bi=-1,bj=-1;
    REP(ii,R)REP(jj,C) {
      if(B[ii][jj]=='A') ai=ii,aj=jj;
      if(B[ii][jj]=='B') bi=ii,bj=jj;
    }
    assert(ai>=0); assert(bi>=0);
    unordered_map<char,II> T = {
      {'U', {-1, 0}},
      {'D', { 1, 0}},
      {'R', { 0, 1}},
      {'L', { 0,-1}},
    };
    FORR(c,M) {
      ai=ai+T[c].first;
      aj=aj+T[c].second;
      ps.emplace_back(ai,aj);
//      dump2(ai,aj);
    }
    
    return f(bi,bj,0)?p2:p1;
  }
};

// CUT begin
ifstream data("GameInDarknessDiv2.sample");

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

bool do_test(vector<string> field, vector<string> moves, string __expected) {
    time_t startClock = clock();
    GameInDarknessDiv2 *instance = new GameInDarknessDiv2();
    string __result = instance->check(field, moves);
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
        vector<string> field;
        from_stream(field);
        vector<string> moves;
        from_stream(moves);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, moves, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510680047;
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
        cout << "GameInDarknessDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
