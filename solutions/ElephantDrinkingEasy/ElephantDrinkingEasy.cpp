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

/*
 
 10/16/2017
 
 10:01-10:30 analysis
 10:31-11:11 implementation and system test passed (371.32 pt)
 
 Water in the outest cells can be reached from the side.
 No computation is needed. Number of rest of cells is just 9=3x3.
 Just did brute-force by permutation of visiting order and directions of reaching sides.
 
 editorial:
  - greedy, two sides bit mask
   - https://apps.topcoder.com/wiki/display/tc/SRM+611
  - four sides bit mask
   - http://kmjp.hatenablog.jp/entry/2014/03/11/0930
   - http://torus711.hatenablog.com/entry/20140305/p2
 
 Editorial is taking greedy approach. Taking closest water from the side is optimal.
 Number of elephant in top-bottom side is at most 10. Possible state is 2^(5+5).
 Brute force them and mark visited cells by in 5*10*2^10 time.
 If there still exists available water cell from left-right sides, take it. 10*5 time.
 
 22:20-23:03 add solution in editorial.
 
 summary:
  - I found out that my brute-force does not actually guarantee that computation is finished after getting AC..
  - I had the greedy idea though, I couldn't associate it with upperbounded states of top-bottom side.
  - First brute-force idea was 2^25 by visited cell though, it's not great
    - more unnecessary states. we need to pay additional cost to verify it.
    - 2^25 is a bit more expensive than 2^20
    - this is too tight to existing idea. try to find better upperbounded constraint in free mind 👎
 
 submit solutions:
  - clean four sides bitmask
   - https://community.topcoder.com/stat?c=problem_solution&rm=320916&rd=15844&pm=13039&cr=40003080
  - backtracking
   - https://community.topcoder.com/stat?c=problem_solution&rm=320886&rd=15844&pm=13039&cr=40002951
 
 */

class ElephantDrinkingEasy {
public:
  int N;
  vector<string> G;
  int fillviz(int i, int j, int di, int dj, vector<vector<int>> &viz) {
    while(i>=0&&i<N&&j>=0&&j<N) {
      if(viz[i][j]) return 0;
      viz[i][j]=1;
      if(G[i][j]=='Y') return 1;
      i+=di,j+=dj;
    }
    return 0;
  }
  
  int maxElephants(vector<string> G) {
    this->N=SZ(G);
    this->G=G;

    int res=0;
    REP(mask,1<<(2*N)) {
      vector<vector<int>> viz(N,VI(N,0));
      int cnt=0;
      REP(k,2*N) if((mask>>k)&1) {
        int j=k%N,i=k/N==0?0:N-1,move=k/N==0?1:-1;
        cnt += fillviz(i,j,move,0,viz);
      }
      REP(k,2*N) {
        int j=k/N==0?0:N-1,i=k%N,move=k/N==0?1:-1;
        cnt += fillviz(i,j,0,move,viz);
      }
      res=max(res,cnt);
    }
    return res;
  }
};


class ElephantDrinkingEasy_org {
  public:
  int N;
  vector<string> G;
  vector<II> ws;
  bool cango(int i, int j, int di, int dj, vector<vector<int>> &viz) {
    bool ok=true;
    while(i>=0&&i<N&&j>=0&&j<N) {
      if(viz[i][j]) {
        ok=false;
        break;
      }
      i+=di,j+=dj;
    }
    return ok;
  }
  void fillviz(bool v, int i, int j, int di, int dj, vector<vector<int>> &viz) {
    while(i>=0&&i<N&&j>=0&&j<N) {
      viz[i][j]=v;
      i+=di,j+=dj;
    }
  }
  int dfs(int k, int cur, vector<vector<int>> &viz) {
    if(k==SZ(ws)) return cur;
    int res = cur;
    int i=ws[k].first,j=ws[k].second;
//    dump4(k,i,j,cur);
    assert(G[i][j]=='Y');
    if(cur>k) {
      dump2(cur,k);
      REP(i,N) dumpAR(viz[i]);
    }
    assert(cur<=k);

    FORR(m,moves) {
      if(cango(i,j,m.first,m.second,viz)) {
        fillviz(true,i,j,m.first,m.second,viz);
        res=max(res,dfs(k+1,cur+1,viz));
        fillviz(false,i,j,m.first,m.second,viz);
      }
    }
    return res;
  }
  
  int maxElephants(vector<string> G) {
    this->N=SZ(G);
    this->G=G;
    vector<vector<int>> viz(N,VI(N,0));
    
    int res=0,out=0;
    REP(j,N) {
      if(G[0][j]=='Y') ++out, viz[0][j]=true;
      if(G[N-1][j]=='Y') ++out, viz[N-1][j]=true;
    }
    FOR(i,1,N-1) {
      if(G[i][0]=='Y') ++out, viz[i][0]=true;
      if(G[i][N-1]=='Y') ++out, viz[i][N-1]=true;
    }
    
//    REP(i,N) dumpAR(viz[i]);
    
    FOR(i,1,N-1) FOR(j,1,N-1) if(G[i][j]=='Y') ws.emplace_back(i,j);
    sort(ws.begin(),ws.end());
    int x=0;
    do {
      x=max(x,dfs(0,0,viz));
      res=max(res,out+x);
    } while(next_permutation(ws.begin(),ws.end()));
    
    return res;
  }
};

// CUT begin
ifstream data("ElephantDrinkingEasy.sample");

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

bool do_test(vector<string> map, int __expected) {
    time_t startClock = clock();
    ElephantDrinkingEasy *instance = new ElephantDrinkingEasy();
    int __result = instance->maxElephants(map);
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
        vector<string> map;
        from_stream(map);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(map, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508173265;
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
        cout << "ElephantDrinkingEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
