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
 
 11/7/2017
 
 9:32-11:30 sample 7 does not pass..
 18:05-19:08 1WA in system test
 19:09-19:40 give up
 
 24:00-25:00 read editorials
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+594
  - http://kmjp.hatenablog.jp/entry/2013/10/17/1130
  - http://emkcsharp.hatenablog.com/entry/SRM594/FoxAndGo2
  - http://topcoder.g.hatena.ne.jp/peryaudo/20131016/1381894135
 
 11/8/2017
 
 23:44-25:46 read editorial and copy solution by @kmjp
 
 Key:
  - Dependency of connected components forms directed bipartite graph
   - { e[i] : e[i] is connected component of empty cells adjacent to w[j] } -> w[j]
 
 Summary:
  - Analysis between components was missing
    - which reduces problem to bipartite graph
  - Too much implementation. too painful.
 
 */
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };
int WN,EN;

set<II> W[400],E[400]; // id->position (white), id->position (empty)
SETI w2eT[400],w2eL[400]; // white->empty (tight bind), white->empty (loose bind)
int tight[400][400]; // white -> empty
class FoxAndGo2 {
public:
  int N;
  vector<string> B;
  int cid[20][20]; // (r,c) -> comp ID
  void show() {
    cout <<endl;
    REP(i,N) cout << B[i] << endl;
  }
  
  void dfs(char c, int i,int j,int id,set<II>& S) {
    S.emplace(i,j);
    cid[i][j]=id;
    FORR(m,moves) {
      int i2=i+m.first,j2=j+m.second;
      if(i2<0||i2>=N||j2<0||j2>=N) continue;
      if(B[i2][j2]!=c) continue;
      if(cid[i2][j2]!=-1) continue;
      S.emplace(i2,j2);
      cid[i2][j2]=id;
      dfs(c,i2,j2,id,S);
    }
  }
  
  int maxKill(vector<string> BB) {
    this->B=BB;
    this->N=SZ(BB);
    MINUS(cid);
    WN=EN=0;
    REP(i,400) W[i].clear(),E[i].clear(),w2eT[i].clear(),w2eL[i].clear();
    REP(i,N)REP(j,N) if(cid[i][j]==-1&&B[i][j]=='o') dfs('o',i,j,WN,W[WN]),WN++;
    REP(i,N)REP(j,N) if(cid[i][j]==-1&&B[i][j]=='.') dfs('.',i,j,EN,E[EN]),EN++;
    if(WN==0) return 0;
    
    REP(wi,WN) REP(ei,EN) {
      tight[wi][ei]=0;
      FORR(p,E[ei]) {
        int i=p.first,j=p.second;
        int f=1;
        FORR(m,moves) {
          int i2=i+m.first,j2=j+m.second;
          if(i2<0||i2>=N||j2<0||j2>=N) continue;
          if(B[i2][j2]=='o'&&cid[i2][j2]==wi) f=0;
        }
        tight[wi][ei]|=f;
      }
    }
    
    REP(i,N) REP(j,N) if(B[i][j]=='o') {
      FORR(m,moves) {
        int i2=i+m.first,j2=j+m.second;
        if(i2<0||i2>=N||j2<0||j2>=N) continue;
        int wi=cid[i][j],ei=cid[i2][j2];
        if(B[i2][j2]=='.' && tight[wi][ei]==0) w2eT[wi].insert(ei);
        if(B[i2][j2]=='.') w2eL[wi].insert(ei);
      }
    }
    SETI cand;
    REP(wi,WN) cand.emplace(wi);
    int res=0;
    int up=1;
    while(up) {
      up=0;
      FORR(wi,cand) if(w2eT[wi].size()<=1) {
        up=1;
        cand.erase(wi);
        res+=W[wi].size();
        
        FORR(p,W[wi]) B[p.first][p.second]='#';
        FORR(ei,w2eL[wi]) FORR(wi,cand) w2eT[wi].erase(ei);
        break;
      }
//      show();
    }
    return res;
  }
};

int viz[20][20];
class FoxAndGo2_wrong {
  public:
  int N;
  vector<string> B;
  bool dfs(int i, int j) {
    if(B[i][j]=='.') { dump2(i,j); return false; }
    if(B[i][j]=='B') return true;
    if(B[i][j]=='#') return true;
    assert(B[i][j]=='o');
    viz[i][j]=true;
    
    FORR(m,moves) {
      int i2=i+m.first,j2=j+m.second;
      if(i2<0||i2>=N||j2<0||j2>=N) continue;
      if(viz[i2][j2]) continue;
      if(!dfs(i2,j2)) return false;
    }
    return true;
  }
  
  bool killed(int i, int j) {
//    if(B[i][j]=='o') return true;
    viz[i][j]=true;
    
    bool res=true;
    FORR(m,moves) {
      int i2=i+m.first,j2=j+m.second;
      if(i2<0||i2>=N||j2<0||j2>=N) continue;
      if(viz[i2][j2]) continue;
      if(B[i2][j2]=='.'||B[i2][j2]=='#') return false;
      if(B[i2][j2]=='o') continue;
      assert(B[i2][j2]=='B');
      res&=killed(i2,j2);
    }
//    dump4('X',i,j,res);
    return res;
  }
  
  int kill(int i, int j) {
    int res=0;
    FORR(m,moves) {
      int i2=i+m.first,j2=j+m.second;
      if(i2<0||i2>=N||j2<0||j2>=N) continue;
      ZERO(viz);
      if(B[i2][j2]=='o'&&dfs(i2,j2)) {
        REP(ii,N) REP(jj,N) if(viz[ii][jj]) {
          res++;
          B[ii][jj]='#';
        }
      }
    }

    if(res>0)dump3(i,j,res);
    return res;
  }
  
  void show() {
    cout <<endl;
    REP(i,N) cout << B[i] << endl;
  }
  
  int maxKill(vector<string> BB) {
    this->B=BB;
    this->N=SZ(BB);
//    queue<II> Q;
    
    int res=0;
    
    REP(_,N*N) {
      
      /*
      REP(i,N) REP(j,N) if(B[i][j]=='.') {
        bool ok=false;
        FORR(m,moves) {
          int i2=i+m.first,j2=j+m.second;
          if(i2<0||i2>=N||j2<0||j2>=N) continue;
          if(B[i2][j2]=='o') continue;
          ok=true;
        }
        if(ok) B[i][j]='B';
      }*/
      
      REP(i,N) REP(j,N) if(B[i][j]=='.') {
        // no-kill
        ZERO(viz);
        B[i][j]='B';
        bool xxx=killed(i,j);
        if(!xxx) {
//          dump3(i,j,xxx);
          res+=kill(i,j);
          show();
        } else {
//          B[i][j]='B';
          int x=kill(i,j);
          dump3(i,j,x);
          if(x>0) {
            res+=x;
            show();
          } else {
            B[i][j]='.';
          }
        }
      }
      /*
      REP(i,N) REP(j,N) if(B[i][j]=='.') {
        B[i][j]='B';
        //        show();
        ZERO(viz);
        bool okok=false;
        REP(k,4) {
          auto m=moves[k];
          int i2=i+m.first,j2=j+m.second;
          if(i2<0||i2>=N||j2<0||j2>=N) continue;
          if(B[i2][j2]!='o') continue;
          bool ok=dfs(i2,j2);
          //          dump3(i2,j2,ok);
          if(ok) {
            REP(ii,N)REP(jj,N) if(viz[ii][jj]) {
              res++;
              B[ii][jj]='#';
            }
          }
          okok|=ok;
        }
        //        dump3(i,j,okok);
        if(!okok) {
          B[i][j]='.';
          Q.emplace(i,j);
        }
      }*/
      
      /*
      REP(_,M) {
        auto p=Q.front(); Q.pop();
        int i=p.first,j=p.second;
//        dump2(i,j);
        
        B[i][j]='B';
//        show();
        ZERO(viz);
        bool okok=false;
        REP(k,4) {
          auto m=moves[k];
          int i2=i+m.first,j2=j+m.second;
          if(i2<0||i2>=N||j2<0||j2>=N) continue;
          if(B[i2][j2]!='o') continue;
          bool ok=dfs(i2,j2);
//          dump3(i2,j2,ok);
          if(ok) {
            REP(ii,N)REP(jj,N) if(viz[ii][jj]) {
              res++;
              B[ii][jj]='#';
            }
          }
          okok|=ok;
        }
//        dump3(i,j,okok);
        if(!okok) {
          B[i][j]='.';
          Q.emplace(i,j);
        }
      }
      if(SZ(Q)==M) break;*/
    }
    
    show();
    
    return res;
  }
};

// CUT begin
ifstream data("FoxAndGo2.sample");

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
    FoxAndGo2 *instance = new FoxAndGo2();
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
        int T = time(NULL) - 1510075942;
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
        cout << "FoxAndGo2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
