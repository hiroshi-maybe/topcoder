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
 
 12/25/2017
 
 17:09-18:10 Time up
 
 x = x0+p*a+q*b
 y = y0+s*a+q*b
 
 0<=x<C, 0<=y<R
 |p|+|q|=|r|+|s|
 
 This is similar to random walk in a grid.
 I thought modular arithmetic may be useful though, I could not move forward.
 
 Another idea is finding all `p` and find corresponding possible `q`s.
 However it seemed to take 10^10 to compute it. I got in stuck.
 
 22:40-26:28 read editorials
  - https://apps.topcoder.com/wiki/display/tc/SRM+564
  - http://kmjp.hatenablog.jp/entry/2012/12/24/1030
  - http://ekaing.hatenablog.com/entry/2013/05/05/230533
  - http://d.hatena.ne.jp/kusano_prog/mobile?sid=fe913461a6a7a55d&date=20121215&section=1355560026
 
 Suppose g=gcd(a,b)
 Reachable cell is { (g*p,g*q) }.
 So we can compress board from (R,C) to (R',C') s.t. (R',C') = (ceil(R/g), ceil(C/g))
 
 Then reachable cells in compressed board are { (a'*p+b'*q, a'*r, b'*s) } s.t. (a',b') = (a/g, b/g)

 Suppose R' and C' are infinitely large.
 By move (x,y) -> (x+a',y+b'), (x+a'+a',y+b'-b') = (x+2*a',y), we can reach 2*a' or 2*b'.

 Also we can find (p,q) s.t. a'*p+b'*q=1 by Euclid's algorithm.
 So it's possible to visit all possible x and y.
 However there may be some constraint for pair of (x,y).
 
 1) a'+b' is even
 
 a' and b' are pair-wise coprime. Both a' and b' should be odd.
 Starting from (0,0), reachable (x,y) satisifies x+y is even.
 Also we can reach any (x,y) in (R',C') by a'*p+b'*q=1 property.
 
 (x,y) forms checker board. res = ceil(R'*C'/2)
 
 2) a'+b' is odd
 
 Either a' or b' is even. The other is odd.
 Starting from (0,0), (x,y) s.t. x+y is odd are reachable.
 Also it's possible to form (x,y) s.t. x+y is even because odd + odd is even.
 
 (x,y) forms all the positions. res = R'*C'
 
 3) R'<2*a' or C'<2*b'
 
 It's not possible to reach 2*a or 2*b. We can brute-force all start points in (max(a,b)*max(R,C)) time.
 We'll find disjoint sets of points by DFS or BFS. The largest one is the result.
 We need to try all the starting point because there exists corner cases where edge is not optimal due to small board.
 One tricky point is that DFS throws segmentation fault due ot deep recursive call. We need to use BFS in this problem.
 
 Key:
  - Observe most of places in a board is reachable if board is infinitely large
  - Compress board by gcd(a,b)
  - Make and prove hypothesis for large R and C mathematically
  - To catch corner cases with small R or C, brute-force
 
 Summary:
  - Try samples and observe it. If most of grids are likely to be reachable, make hypothesis and prove it.
   - It's tough to solve this problem without this approach
   - To simplify, solve problem in infinitely large case
  - Interesting to reduce a problem to find lartest connected component
  - I should try to use gcd(a,b) if formula p*a+q*b shows up
  - Many unknowns that I could not resolve
    - a*p+b*q is constrained by gcd(a,b) => Search space can be compressed
    - Checker-board is associated with parity of (x,y)
  - Starting (0,0) is optimal ONLY WHEN R>=2*a AND C>=2*b
 
 */
vector< pair < int, int > >  moves = { {1,1},{1,-1},{-1,1},{-1,-1} };
int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }
class KnightCircuit {
  public:
  int R,C,a,b;
  int viz[21][100001]={};
  int x=0;
  
  // segmentation fault due to deep call
  int dfs() {
    ZERO(viz);
    int res=0;
    REP(i,R) REP(j,C) if(viz[i][j]==0) {
      x=0;
      dfsdfs(i,j);
      res=max(x,res);
    }
    return res;
  }
  void dfsdfs(int i, int j) {
    if(viz[i][j]) return;
    dump2(i,j);
    viz[i][j]=1;
    ++x;
//    dump(x);
    vector<II> ds={{a,b},{b,a}};
    FORR(d, ds) FORR(m,moves) {
      int di=d.first*m.first,dj=d.second*m.second;
      int i2=i+di,j2=j+dj;
      if(i2<0||i2>=R||j2<0||j2>=C) continue;
      dfsdfs(i2,j2);
    }
  }
  
  int bfs() {
    ZERO(viz);
    int res=0;
    REP(i,R) REP(j,C) if(viz[i][j]==0) {
      int x=0;
      queue<II> Q; Q.emplace(i,j);
      viz[i][j]=1;
      
      while(SZ(Q)) {
        ++x;
        auto p=Q.front(); Q.pop();
        int ii=p.first,jj=p.second;
        vector<II> ds={{a,b},{b,a}};
        FORR(d, ds) FORR(m,moves) {
          int di=d.first*m.first,dj=d.second*m.second;
          int i2=ii+di,j2=jj+dj;
          if(i2<0||i2>=R||j2<0||j2>=C) continue;
          if(viz[i2][j2]) continue;
          viz[i2][j2]=1;
          Q.emplace(i2,j2);
        }
      }
      
      res=max(x,res);
    }
    return res;
  }
  
  long long maxSize(int C, int R, int a, int b) {
    int g=gcd(a,b);
    if(g!=1) {
      R=(R+g-1)/g;
      C=(C+g-1)/g;
      a/=g;
      b/=g;
    }
    if(R>C) swap(R,C),swap(a,b);
    this->R=R,this->C=C,this->a=a,this->b=b;
//    dump4(R,C,a,b);
    // R<=C
    if(R<=max(a,b)*2) {
//      return dfs();
      return bfs();
    }
    return (a+b)%2?1LL*R*C:(1LL+(LL)R*C)/2LL;
  }
};

// CUT begin
ifstream data("KnightCircuit.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int w, int h, int a, int b, long long __expected) {
    time_t startClock = clock();
    KnightCircuit *instance = new KnightCircuit();
    long long __result = instance->maxSize(w, h, a, b);
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
        int w;
        from_stream(w);
        int h;
        from_stream(h);
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(w, h, a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514250548;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1050 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "KnightCircuit (1050 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
