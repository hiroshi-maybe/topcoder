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
 
 2/2/2018
 
 10:36-11:13 analysis
 11:13-12:02 implement but MLE
 18:05-18:35 implement by imos, submit and ACC
 
 To save memory, I built intervals at each row and counted overlapped intervals.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+541
  - http://kmjp.hatenablog.jp/entry/2014/01/04/1000
  - http://d.hatena.ne.jp/komiyam/20120630/1340982112
  - http://lepton.hatenablog.jp/entry/20120424/1335273075
 
 Summary:
  - I thought 49MB array exceeds memory limit though, it did not 😔
    - single int[3150][3150] array fits
  - My first code had a bug of BFS 👎👎
 
 */
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
// 15MB even for K=1500
// imos, O(K*N^2*lg N) time
map<int,int> xs[3100];
class NonXorLife {
public:
  const int offset=1510;
  int countAliveCells(vector<string> F, int K) {
    REP(i,3100) xs[i].clear();
    REP(i,SZ(F)) REP(j,SZ(F[0])) if(F[i][j]=='o') {
      int ii=i+offset;
      for(int d=-K;d<=K; ++d) {
        int i2=ii+d;
        int dd=K-abs(d);
        int l=j-dd,r=j+dd+1;
        xs[i2][l]+=1;
        xs[i2][r]-=1;
      }
    }
    
    int res=0;
    REP(i,3100) {
      int l=-1500,sum=0;
      FORR(kvp,xs[i]) {
        int sum2=sum+kvp.second;
        if(sum==0&&sum2>0) l=kvp.first;
        if(sum>0&&sum2==0) {
          res+=kvp.first-l,l=-1500;
        }
        sum=sum2;
      }
    }
    return res;
  }
};

// bfs, O(K^2) time
// int: 49MB -> bool: 21MB
bool viz[3150][3150];
class NonXorLife {
public:
  int K;
  const int Inf=1e4;
  int bfs(vector<string> &F) {
    const int offset=1510;
    queue<II> Q;
    REP(i,SZ(F)) REP(j,SZ(F[0])) if(F[i][j]=='o') {
      int ii=i+offset,jj=j+offset;
      Q.emplace(ii,jj);
      viz[ii][jj]=1;
    }
    REP(_1,K) {
      int M=SZ(Q);
      REP(_2,M) {
        auto p=Q.front(); Q.pop();
        int i=p.first,j=p.second;
        FORR(m,moves) {
          int ii=i+m.first,jj=j+m.second;
          if(viz[ii][jj]) continue;
          viz[ii][jj]=1;
          Q.emplace(ii,jj);
        }
      }
    }
    int res=0;
    REP(i,3150) REP(j,3150) res+=viz[i][j];
    return res;
  }
  int countAliveCells(vector<string> F, int K) {
    this->K=K;
    ZERO(viz);
//    REP(i,3150)REP(j,3150) dist[i][j]=Inf;
    return bfs(F);
  }
};

/*
class NonXorLife_org {
  public:
  int K;
  int viz[3150][3150];
  int B[3150][3150];

  int bfs(vector<string> &F) {
    const int offset=55;
    int B[160][160]={};
    REP(i,SZ(F)) REP(j,SZ(F[0])) B[i+offset][j+offset]=F[i][j]=='o';
    REP(_1,K) {
      int B2[160][160]={};
      REP(i,160)REP(j,160) B2[i][j]=B[i][j];
      FOR(i,1,159)FOR(j,1,159) {
        int cnt=B[i][j];
        FORR(m,moves) {
          int ii=i+m.first,jj=j+m.second;
          cnt+=B[ii][jj];
        }
        B2[i][j]=cnt>0;
      }
      swap(B2,B);
    }
    int res=0;
    REP(i,160) {
      REP(j,160) cout<<B[i][j];
      cout<<endl;
    }
    
    REP(i,160) REP(j,160) {
      res+=B[i][j];
    }
    return res;
  }
  
  VI ps;
  void dfs1(int i, int j) {
    if(viz[i][j]) return;
    viz[i][j]=1;
    if(B[i][j]==1) {
      ps.push_back(1600*i+j);
      return;
    }
    dump2(i,j);
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(i<0||i>=3150||j<0||j>=3150) continue;
      dfs1(ii,jj);
    }
  }
  void dfs2(int i, int j) {
    if(viz[i][j]) return;
    if(B[i][j]==1) return;
    viz[i][j]=1;
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(i<0||i>=3150||j<0||j>=3150) continue;
      dfs2(ii,jj);
    }
  }
  
  void bfs1(int i, int j) {
    queue<II> Q; Q.emplace(i,j);
    viz[i][j]=1;
    while(SZ(Q)) {
//      dump(SZ(Q));
      auto p=Q.front(); Q.pop();
      int i=p.first,j=p.second;
//      dump2(i,j);
      if(B[i][j]) {ps.push_back(3150*i+j); continue; }
      FORR(m,moves) {
        int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=3150||jj<0||jj>=3150) continue;
        if(viz[ii][jj]) continue;
        viz[ii][jj]=1;
        Q.emplace(ii,jj);
      }
    }
  }
  
  void bfs2(int i, int j) {
//    dump("poo");
    queue<II> Q; Q.emplace(i,j);
    while(SZ(Q)) {
      dump(SZ(Q));
      auto p=Q.front(); Q.pop();
      int i=p.first,j=p.second;
      if(B[i][j]) { continue; }
      viz[i][j]=1;
      FORR(m,moves) {
        int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=3150||jj<0||jj>=3150) continue;
        if(viz[ii][jj]) continue;
        Q.emplace(ii,jj);
      }
    }
  }
  
  int countAliveCells(vector<string> F, int K) {
    this->K=K;
    if(K<=50) return bfs(F);
    
    ZERO(B),ZERO(viz);
    const int offset=1550;
    REP(i,SZ(F)) REP(j,SZ(F[0])) B[i+offset][j+offset]=F[i][j]=='o';
    dump(K);
    bfs1(0,0);
    dump(K);
    FORR(p,ps) {
      int i=p/3150,j=p%3150;
//      dump2(i,j);
      B[i+K][j+K]=1,B[i+K][j-K]=1,B[i-K][j+K]=1,B[i-K][j-K]=1;
    }
    ZERO(viz);
    bfs2(0,0);
    int cnt=0;
    REP(i,3150)REP(j,3150) cnt+=viz[i][j];
    
    return 3150*3150-cnt;
  }
};*/

// CUT begin
ifstream data("NonXorLife.sample");

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

bool do_test(vector<string> field, int K, int __expected) {
    time_t startClock = clock();
    NonXorLife *instance = new NonXorLife();
    int __result = instance->countAliveCells(field, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517596565;
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
        cout << "NonXorLife (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
