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
 
 11/11/2017
 
 15:07-15:22 analyze and implement
 15:23-15:27 debug, fix bug and system test passed (353.43 pt)
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+590
  - https://topcoder.g.hatena.ne.jp/firewood/20131124/1385311727
   - so smart to return -Inf if empty cell is found
  - http://emkcsharp.hatenablog.com/entry/SRM590/FoxAndGo
  - http://torus711.hatenablog.com/entry/20130909/p2
  - http://kmjp.hatenablog.jp/entry/2013/09/09/0930
 
 Summary:
  - I counted white tokens which cannot be removed first 😫
  - Fixed the bug in 4 mins 👍
 
 */
// O(N^4) time
int viz[20][20];
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };
class FoxAndGo {
  public:
  int N;
  vector<string> B;
  bool ng=false;
  int dfs(int i, int j) {
    if(viz[i][j]) return 0;
    viz[i][j]=true;
    int res=1;
    FORR(m,moves) {
      int i2=i+m.first,j2=j+m.second;
      if(i2<0||i2>=N||j2<0||j2>=N) continue;
      if(B[i2][j2]=='.') ng=true;
      if(B[i2][j2]!='o') continue;
      res+=dfs(i2,j2);
    }
    return res;
  }
  int maxKill(vector<string> BB) {
    this->B=BB;
    this->N=SZ(B);
    int res=0;
    REP(i,N) REP(j,N) if(B[i][j]=='.') {
      B[i][j]='x';
      int cnt=0;
      ZERO(viz);
      REP(ii,N)REP(jj,N)if(B[ii][jj]=='o') {
        ng=false;
        int a=dfs(ii,jj);
        if(!ng) cnt+=a;
      }
//      if(cnt>res) dump3(i,j,cnt);
      res=max(res,cnt);
      B[i][j]='.';
    }
    return res;
  }
};

// CUT begin
ifstream data("FoxAndGo.sample");

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
    FoxAndGo *instance = new FoxAndGo();
    int __result = instance->maxKill(board);
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
        int T = time(NULL) - 1510441660;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FoxAndGo (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
