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
 
 12/11/2017
 
 8:54-10:00 pause
 18:00-20:00 system test passed
 
 Editorial:
   - https://apps.topcoder.com/wiki/display/tc/SRM+575
   - http://kmjp.hatenablog.jp/entry/2013/04/10/0900
   - http://tatsyblog.sakura.ne.jp/wordpress/contests/topcoder/200/
   - http://kujira16.hateblo.jp/entry/2013/04/07/183401
   - http://sucrose.hatenablog.com/entry/2013/04/07/031251
 
 Key:
  - bit DP
  - make puzzle pieces first and try them all
 
 Summary:
  - It was trivial to figure out bit DP
  - Tough design how to design state and move window
  - Tough implementation to iterate possible tiles and validate them
 
 */
vector<vector<II>> BL[4];
vector<II> moves={{-1,0},{0,-1},{1,0},{0,1},{-1,0}};
vector<II> os={{1,0},{1,2},{2,1},{2,3}};

int dp[25][16][4];
class TheTilesDivTwo {
public:
  const int Inf=1e3;
  vector<vector<int>> B;
  // normalize board by putting sentinels
  void mkBoard(vector<string> &BB) {
    int N=SZ(BB[0]);
    while(SZ(BB)<4) BB.push_back(string(N,'X'));
    REP(j,N) {
      VI xs(4);
      REP(i,4) xs[i]=BB[i][j]=='X';
      B.emplace_back(xs);
    }
    if(SZ(B)&1) B.emplace_back(VI(4,1));
    B.emplace_back(VI(4,1));
    assert(SZ(B)%2==1); // odd
  }
  
  // create all the possible blocks for origins `os`
  void mkBlocks() {
    REP(i,4) BL[i].clear();
    REP(i,4) {
      int r=os[i].first,c=os[i].second;
      BL[i].push_back(vector<II>()); // skip choice
      REP(k,4) {
        vector<II> xs;
        xs.emplace_back(r,c);
        int r2=r+moves[k].first,c2=c+moves[k].second;
        if(r2<0||r2>=4||c2<0||c2>=4) continue;
        xs.emplace_back(r2,c2);
        int r3=r+moves[k+1].first,c3=c+moves[k+1].second;
        if(r3<0||r3>=4||c3<0||c3>=4) continue;
        xs.emplace_back(r3,c3);
        
        BL[i].emplace_back(xs);
      }
    }
  }

  // for debug
  void show(vector<VI> &X) {
    REP(r,4) {
      REP(c,4) cout << X[r][c];
      cout << endl;
    }
  }
  
  int find(vector<string> BB) {
    mkBoard(BB); mkBlocks();
    int N=SZ(B)/2;

    REP(i,N+1)REP(j,16)REP(k,4) dp[i][j][k]=-Inf;
    dp[0][15][0]=0;
    REP(i,N) REP(m1,16) REP(m2,4) if(dp[i][m1][m2]>=0) {
      vector<VI> X(4,VI(4,0));
      REP(a,4) if(m1&(1<<a)) X[0][a]=1; // r0
      if((m2&1)!=0) X[1][1]+=1; // r1
      if((m2&2)!=0) X[1][3]+=1; // r1
      REP(a,2)REP(b,4) if(B[2*i+a][b]) X[a+1][b]=1; // r1,r2
      REP(a,4) if(B[2*i+2][a]) X[3][a]=1; // r3
      
      REP(r,4)REP(c,4) assert(X[r][c]<2);
      
      REP(i1,SZ(BL[0]))REP(i2,SZ(BL[1]))REP(i3,SZ(BL[2]))REP(i4,SZ(BL[3])) {
        vector<VI> XX=X;
        FORR(p,BL[0][i1])XX[p.first][p.second]++;
        FORR(p,BL[1][i2])XX[p.first][p.second]++;
        FORR(p,BL[2][i3])XX[p.first][p.second]++;
        FORR(p,BL[3][i4])XX[p.first][p.second]++;
        
        bool ok=true;
        REP(r,4)REP(c,4) if(XX[r][c]>1) ok=false;
        if(!ok) continue;
        
        int cnt=(i1>0)+(i2>0)+(i3>0)+(i4>0);
        
        int mm1=0;
        REP(a,4)if(XX[2][a]) mm1|=(1<<a);
        int mm2=0;
        if (XX[3][1]) mm2|=1;
        if (XX[3][3]) mm2|=2;
        dp[i+1][mm1][mm2]=max(dp[i+1][mm1][mm2], dp[i][m1][m2]+cnt);
      }
    }
    
    int res=0;
    REP(m1,16)REP(m2,4) res=max(res,dp[N][m1][m2]);
    return res;
  }
};

// CUT begin
ifstream data("TheTilesDivTwo.sample");

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
    TheTilesDivTwo *instance = new TheTilesDivTwo();
    int __result = instance->find(board);
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
        int T = time(NULL) - 1513011253;
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
        cout << "TheTilesDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
