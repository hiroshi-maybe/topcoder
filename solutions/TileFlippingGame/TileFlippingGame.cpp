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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/29/2018 SRM 732
 
 18:00-19:15 Time up 😞
 
 My analysis during the contest
  - This is graph problem. Adjucent cells with same color forms the same vertex
  - Vertices may be separated by empty cells. In such a case we need to add each result of islands for specific color
  - Vertex with more edges seems to give better result. However it's not always optimal for specific color (counter example)
  - Vertices are merged by flip. Brute-force with union-find? However runtime complexity is not clear for me
 
 There are two major approaches
  - flips and brute-force
  - reduce to shortest distance
 
 # Brute-force
 
 Brute-force all the orders of flipping exceeds time limit.
 As described in some of tweets, we keep flipping specific cell until the game ends.
 We can do that for all the cells. That is O(N^6) time.
 Keep flipping specific cell is sufficient. That is the point of this problem (no proof so far)
 
 # Shortest distance
 
 I had no idea about this approach. Looks like computation of diameter is a key.
 
 distance(u,v) = # of merges necessary to merge u with v
 Color after merge is flipped if distanc(u,v) is odd.
 
 In this approach, actually we need the same proof of brute-force solution.
 Keep flipping specific cell should give optimal solution.
 
 For example, suppose we have below graph:
 
 0 1 2 3 4 5 6 7
 w-b-w-b-w-b-w-b
 
 Our distance-based approach is assuming to keep merging from specific vertex.
 For example, if we start merging process from vertex 3...

 0 1 2 3 4 5 6 7
 w-b-w-b-w-b-w-b
 w-b-w-w-w-b-w-b
 w-b-b-b-b-b-w-b
 w-w-w-w-w-w-w-b
 b-b-b-b-b-b-b-b
       ^
 
 It's not obvious that this gives optimal solution.
 For example, below series of operations is possible:
 
 0 1 2 3 4 5 6 7
 b-b-w-b-w-b-w-b
 ^
 b-b-w-b-w-b-b-b
             ^
 b-b-w-w-w-b-b-b
       ^
 b-b-w-w-w-b-b-b
           ^
 b-b-w-w-w-w-w-w
 ^
 w-w-w-w-w-w-w-w
 
 This is total 5 steps.
 Actually this is not optimal. If we keep flipping vertex 4, we get all white in 4 steps 🤔
 
 Editorials:
  - http://kmjp.hatenablog.jp/entry/2018/03/31/0930
  - http://red.cliff.jp/topcoder.html
  - http://codeforces.com/blog/entry/58590
  - https://togetter.com/li/1213472
  - Shortest path
   - https://twitter.com/n_vip/status/979552510498127872
   - https://twitter.com/satanic0258/status/979556111073202176
  - Brute-force
   - https://twitter.com/iwashi31/status/979554301985959937
   - https://twitter.com/koyumeishi_/status/979553515746992128
 
 Submit solutions in the contest
  - BFS + Union-find
   - https://community.topcoder.com/stat?c=problem_solution&rm=331100&rd=17103&pm=14843&cr=23047783
  - Floyd-Warshall
   - https://community.topcoder.com/stat?c=problem_solution&rm=331102&rd=17103&pm=14843&cr=23106841
 
 Similar problem:
  - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1174&lang=jp
 
 4/1/2018
 
 21:35-22:21 add solution with floyd-warshall
 
 I couldn't find proof of the theorem to keep flipping the same cell gives optimal result.
 
 Summary:
  - Figured out that this is graph problem
  - It's hard for me to solve without the theorem
 
 */

// floyd-warshall, O(R^3*C^3) time
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
int D[400][400];
int viz[400][400];
class TileFlippingGame {
public:
  const int Inf=1e3;
  int R,C;
  vector<string> X;
  VI f(int r, int c) {
    dump2(r,c);
    VI res={Inf,Inf};
    REP(i,R)REP(j,C) if(D[i*C+j][r*C+c]<Inf) {
      viz[i][j]=true;
      int maxd=0;
      REP(ii,R)REP(jj,C)if(D[ii*C+jj][i*C+j]<Inf) SMAX(maxd,D[ii*C+jj][i*C+j]);
      int c=X[i][j]=='b';
      if(maxd%2==0) {
        SMIN(res[c],maxd);
        SMIN(res[1^c],maxd+1);
      } else {
        SMIN(res[c],maxd+1);
        SMIN(res[1^c],maxd);
      }
//      dump3(i,j,maxd);
    }
    return res;
  }
  
  int HowManyMoves(int R, int C, vector<string> X) {
    this->R=R,this->C=C,this->X=X;
    REP(i,R*C)REP(j,R*C) D[i][j]=i==j?0:Inf;
    REP(i,R)REP(j,C) if(X[i][j]!='e') {
      REP(di,2) {
        int dj=1^di;
        int ii=i+di,jj=j+dj;
        if(ii>=R||jj>=C) continue;
        if(X[ii][jj]=='e') continue;
        int d=X[ii][jj]==X[i][j]?0:1;
        D[i*C+j][ii*C+jj]=D[ii*C+jj][i*C+j]=d;
      }
    }
    REP(k,R*C)REP(i,R*C)REP(j,R*C) SMIN(D[i][j],D[i][k]+D[k][j]);

    ZERO(viz);
    int resb=0,resw=0;
    REP(i,R)REP(j,C) if(X[i][j]!='e'&&!viz[i][j]) {
      auto p=f(i,j);
      resb+=p[0];
      resw+=p[1];
    }
    return min(resb,resw);
  }
};

int GR[21][21];
class TileFlippingGame_wrong {
  public:
  int viz[21][21];
  VI uf;
  int find(int x) { return uf[x]==x?x:uf[x]=find(uf[x]); }
  void unite(int a, int b) {
    int aa=find(a),bb=find(b);
    uf[aa]=bb;
  }
  int R,C;
  vector<string> X;
  vector<VI> G;
  void dfs(int i, int j, char c, int v) {
    if(viz[i][j]||X[i][j]!=c) return;
    viz[i][j]=1;
    GR[i][j]=v;
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=R||jj<0||jj>=C)continue;
      dfs(ii,jj,c,v);
    }
  }
  int HowManyMoves(int R, int C, vector<string> X) {
    this->R=R,this->C=C,this->X=X;
    ZERO(viz); MINUS(GR);
    int V=0;
    REP(i,R)REP(j,C) if(X[i][j]!='e'&&!viz[i][j]) {
//      dump2(i,j);
      dfs(i,j,X[i][j],V++);
    }
    dump(V);
    G=vector<VI>(V);
    REP(i,R)REP(j,C) if(X[i][j]!='e') {
      int u=GR[i][j];
      int v1=-1;
      if(i+1<R&&X[i+1][j]!='e'&&GR[i+1][j]!=u) {
        v1=GR[i+1][j];
        G[u].push_back(v1),G[v1].push_back(u);
      }
      if(j+1<C&&X[i][j+1]!='e'&&GR[i][j+1]!=u) {
        int v=GR[i][j+1];
        if(v==v1) continue;
        G[u].push_back(v),G[v].push_back(u);
      }
    }
    
    /*
    REP(i,V) {
      dump(i);
      dumpAR(G[i]);
    }*/
    
    uf=VI(V); REP(i,V) uf[i]=i;
    
    
    return 0;
  }
};

// CUT begin
ifstream data("TileFlippingGame.sample");

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

bool do_test(int n, int m, vector<string> X, int __expected) {
    time_t startClock = clock();
    TileFlippingGame *instance = new TileFlippingGame();
    int __result = instance->HowManyMoves(n, m, X);
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
        int m;
        from_stream(m);
        vector<string> X;
        from_stream(X);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522371611;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TileFlippingGame (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
