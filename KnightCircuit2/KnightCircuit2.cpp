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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('\n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

/*
 
 11/10/2018
 
 10:49-11:40, 11:46 resubmit to avoid stack overflow due to deep recursion. got AC
 
 http://apps.topcoder.com/wiki/display/tc/SRM+564
 Simple classification work. I should have digged experiment more deeply.
 
 I'm always takin more complex solution. Probably my guess is not going well.
 If I looked at this problem, I should have a guess that all the cells are visited for large N or M.
 If I had this guess, I shouldn't dig into search solution. I should have spent more time to prove it.
 My guess is always going wrong. My taste is always missing compact approach. My approach is always poor.
 Don't rush into feasible solution. Guess plausible solution to resolve unknown.
 We can visit cells arbitrary times. This loose constraint gives more opportunities for us.
 It's reasonable to guess that all of the cells can be visited for large N.
 
 Summary:
  - Loose constaraint gives us chances to find greedy approach. Keep in mind.
 
 */
const int MAX_N=45010;
int vizH[4][MAX_N],vizV[MAX_N][4];

vector<pair<int,int>> movesk = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} };

class KnightCircuit2 {
  public:
  int N,M;
  void bfs1(int i, int j) {
    queue<II> Q; Q.emplace(i,j);
    vizH[i][j]=true;
    while(SZ(Q)) {
      int i,j; tie(i,j)=Q.front(); Q.pop();
      for(auto m : movesk) {
        int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=N||jj<0||jj>=M) continue;
        if(vizH[ii][jj]) continue;
        vizH[ii][jj]=true;
        Q.emplace(ii,jj);
      }
    }
  }
  void bfs2(int i, int j) {
    queue<II> Q; Q.emplace(i,j);
    vizV[i][j]=true;
    while(SZ(Q)) {
      int i,j; tie(i,j)=Q.front(); Q.pop();
      for(auto m : movesk) {
        int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=N||jj<0||jj>=M) continue;
        if(vizV[ii][jj]) continue;
        vizV[ii][jj]=true;
        Q.emplace(ii,jj);
      }
    }
  }
  void dfs2(int i, int j) {
    if(vizV[i][j]) return;
    vizV[i][j]=true;
    // snippet of board move
    for(auto m : movesk) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      dfs2(ii,jj);
    }
  }
  int maxSize(int W, int H) {
    int res=0;
    if(W>=4&&H>=4) {
      res+=(H-4)*(W-4);
      ZERO(vizH),ZERO(vizV);
    
      N=4,M=W;
      FOR(i,2,4)REP(j,W-2)bfs1(i,j);
      REP(i,4)REP(j,M-4)res+=vizH[i][j];
      N=H,M=4;
      FOR(i,2,H)REP(j,2)bfs2(i,j);
      FOR(i,4,N)REP(j,4)res+=vizV[i][j];
      REP(i,4)REP(j,4) res+=(vizH[i][W-4+j]|vizV[i][j]);
    } else {
      if(H<4) {
        N=H,M=W;
        REP(i,H)REP(j,min(4,W)) {
          ZERO(vizH);
          bfs1(i,j);
          int x=0;
          REP(i,H)REP(j,W) x+=vizH[i][j];
//          dump3(i,j,x);
          SMAX(res,x);
        }
      } else {
        N=H,M=W;
        REP(i,min(4,H))REP(j,W) {
          ZERO(vizV);
          bfs2(i,j);
          int x=0;
          REP(i,H)REP(j,W) x+=vizV[i][j];
          SMAX(res,x);
        }
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("KnightCircuit2.sample");

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

bool do_test(int w, int h, int __expected) {
    time_t startClock = clock();
    KnightCircuit2 *instance = new KnightCircuit2();
    int __result = instance->maxSize(w, h);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(w, h, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541875756;
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
        cout << "KnightCircuit2 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
