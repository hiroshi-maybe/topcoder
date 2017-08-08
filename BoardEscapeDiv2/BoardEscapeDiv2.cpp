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

vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };

/**
 
 8/7/2017
 
 11:32-12:17 design
 12:17-12:50, 14:15-14:24 give up
 
 16:15 read editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+676
  - http://futurismo.biz/archives/5537
  - http://kmjp.hatenablog.jp/entry/2015/12/19/1000
 
 16:44 passed system test by topdown DP
 16:44-17:28 read game DP problem https://github.com/k-ori/topcoder/tree/master/ThueMorseGame and learn about Nim game again.
 17:28-17:39 add bottom-up DP solution
 
 WL-Algorithm:
  - win(S) = ∃S' where f(x,S)->S' AND win(S')==false (opponent is lost) ? true (current player wins)
           otherwise : false (current player loses)
 
 This problem:
  f(0,*,*) = false
  f(k,x,y) = G[x][y] ? false
             ∃(x',y'), G[x'][y']!='#' AND f(k-1,x',y')==false ? true
             otherwise: false
 
 Key:
  - grundy number and WL-Algorithm
    - http://d.hatena.ne.jp/nanikaka/20120524/1337797626
    - https://www.topcoder.com/community/data-science/data-science-tutorials/algorithm-games/
    - https://www.hackerrank.com/topics/game-theory-and-grundy-numbers
  - problem usually states "player changes state from S to S', then player wins". it's easier to translate to WL-algorithm to think that if state is S', then opponent is LOST, or f(S')=false
 
 17:39-20:00 read programming contest challenge book (ant book) section 4-2
 
 1) N group Nim technique
  i)  XOR{ a[i] : i=1..N } =  0 ? LOSE
  ii) XOR{ a[i] : i=1..N } != 0 ? WIN
 
 2) N grundy numbers
  i)  XOR{ G[i] : i=1..N } =  0 ? LOSE
  ii) XOR{ G[i] : i=1..N } != 0 ? WIN
 
  G(S) >0 => ∃S', f(S)=S' AND G(S')<G(S), there is a state whose grundy number is smaller
  G(S)==0 => ∀S', f(S)=S' AND G(S')>0,    there is a state whose grundy number is larger than 0

 - finite 2-person impartial games
 - perfect information
 - play optimally
 
 Analogy between WIN/LOSE state and grundy number:
 
 LOSE state
 
 i)  S_LOSE (termination)
 ii) S_LOSE <- S_WIN (next states are all WIN)
            <- S_WIN'
 i)  G(S)=0 (termination)
 ii) G(S)=0 <- G(S') >0 (next states are all >0)
            <- G(S'')>0
 
 WIN state
 
 S_WIN <- S_WIN
       <- S_LOSE (there exists a LOSE state in next step)
 G(S)>0 <- G(S') >0
        <- G(S'')=0 (If one of the grundy numbers of next state is 0, G(S) cannot be 0, thus WIN)
 
 23:16-23:20 add solution by grundy number
 
 Key
  - state is small. just do WL-Algorithm
 
 Summary
  - dp space is obvious and figured out it correctly 👍
  - confused about what dp state means 👎
    - dp[][][] represents if Alice wins ❌
    - dp[][][] represents if whoever in the state wins ✅
    - It's exactly the WL-algorithm
 
 */

int gr[101][50][50];
class BoardEscapeDiv2 {
public:
  string alice="Alice",bob="Bob";
  string findWinner(vector<string> G, int K) {
    int M=SZ(G),N=SZ(G[0]);
    ZERO(gr);
    FOR(k,1,K+1)REP(x,M)REP(y,N) {
      if (G[x][y]=='E') {
        gr[k][x][y]=0;
        continue;
      }
      SETI mex;
      FORR(m, moves) {
        int x2=x+m.first,y2=y+m.second;
        if(x2<0||y2<0||x2>=M||y2>=N) continue;
        if(G[x2][y2]=='#') continue;
        mex.insert(gr[k-1][x2][y2]);
      }
      int g=0;
      while(mex.count(g)) ++g;
      gr[k][x][y]=g;
    }
    
    int x=-1,y=-1;
    REP(i,M)REP(j,N) if(G[i][j]=='T') x=i,y=j;
    return gr[K][x][y]==0?bob:alice;
  }
};

int dp[101][50][50];
class BoardEscapeDiv2_dp2 {
public:
  string alice="Alice",bob="Bob";
  string findWinner(vector<string> G, int K) {
    int M=SZ(G),N=SZ(G[0]);
    ZERO(dp);
    FOR(k,1,K+1)REP(x,M)REP(y,N) {
      if (G[x][y]=='E') {
        dp[k][x][y]=false;
        continue;
      }
      dp[k][x][y]=0;
      FORR(m, moves) {
        int x2=x+m.first,y2=y+m.second;
        if(x2<0||y2<0||x2>=M||y2>=N) continue;
        if(G[x2][y2]=='#') continue;
        dp[k][x][y] |= !dp[k-1][x2][y2];
      }
    }
    
    int x=-1,y=-1;
    REP(i,M)REP(j,N) if(G[i][j]=='T') x=i,y=j;
    return dp[K][x][y]?alice:bob;
  }
};

int memo[101][50][50];
class BoardEscapeDiv2_dp1 {
public:
  vector<string> G;
  int M,N;
  string alice="Alice",bob="Bob";
  int f(int k, int x, int y) {
    if(k==0) return false;
    if(memo[k][x][y]>=0) return memo[k][x][y];
    
    if(G[x][y]=='E') return false;
    
    FORR(m, moves) {
      int x2=x+m.first,y2=y+m.second;
      if(x2<0||y2<0||x2>=M||y2>=N) continue;
      if(G[x2][y2]=='#') continue;
      if(!f(k-1,x2,y2)) return memo[k][x][y]=true;
    }
    
    return memo[k][x][y]=false;
  }
  string findWinner(vector<string> _G, int K) {
    G=_G;
    MINUS(memo);
    M=SZ(G),N=SZ(G[0]);
    int x=-1,y=-1;
    REP(i,M)REP(j,N) if(G[i][j]=='T') x=i,y=j;
    
    return f(K,x,y)?alice:bob;
  }
};

class BoardEscapeDiv2_wrong {
  public:
  string alice="Alice",bob="Bob";
  int dp[101][50][50];
  string findWinner(vector<string> G, int K) {
//    K=4;
    MINUS(dp);
    int M=SZ(G),N=SZ(G[0]);
    REP(i,M)REP(j,N) if(G[i][j]=='T') dp[0][i][j]=0;
    
    FOR(k,1,K+1) REP(i,M) REP(j,N) {
      if(G[i][j]=='#') continue;
      if(G[i][j]=='E'&&dp[k-1][i][j]!=-1) {
        dp[k][i][j]=dp[k-1][i][j];
        continue;
      }
      FORR(m, moves) {
        int i2=i+m.first,j2=j+m.second;
        if(i2<0||j2<0||i2>=M||j2>=N) continue;
        if (G[i2][j2]=='#'||G[i2][j2]=='E') continue;
        if (dp[k-1][i2][j2]==-1) continue;
        if (dp[k][i][j]==-1) dp[k][i][j]=0;
        dp[k][i][j]|=!dp[k-1][i2][j2];
      }
    }
    
    int res=0;
/*    REP(i,M)REP(j,N) {
      if(dp[K][i][j]!=-1) res|=dp[K][i][j];
    }*/
    REP(i,M) {
      string x="";
      REP(j,N) {
        if(dp[K][i][j]==-1) x+="#";
        else if(dp[K][i][j]==1) x+="1";
        else if(dp[K][i][j]==0) x+="0";
        else assert(false);
      }
      cout << x << endl;
    }
    
    return res?alice:bob;
  }
};

// CUT begin
ifstream data("BoardEscapeDiv2.sample");

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

bool do_test(vector<string> s, int k, string __expected) {
    time_t startClock = clock();
    BoardEscapeDiv2 *instance = new BoardEscapeDiv2();
    string __result = instance->findWinner(s, k);
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
        vector<string> s;
        from_stream(s);
        int k;
        from_stream(k);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502130751;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BoardEscapeDiv2 (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
