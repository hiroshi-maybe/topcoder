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
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/24/2018
 
 17:01-17:40 pause
 18:00-18:15 pause
 22:20-22:35 analysis
 22:56 submit 1WA
 23:27 bug fix. but WA :(
 23:51 TLE for 2500 digits :(
 23:55 ACC
 
 3/25/2018
 
 Finding a path to visits all the slimes seemed to be NP-hard.
 Thus I tried to find some condition which reduces search space.
 I found out that lifetime of slime is at most 9.
 So max path length is 9. Possible path is upper-bounded by 4^9. This seems to work.
 However I couldn't design algorithm to solve this quickly 😞
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+506
  - http://kmjp.hatenablog.jp/entry/2014/03/26/0930
  - http://d.hatena.ne.jp/kusano_prog/20110527/1306469078
  - http://area.hateblo.jp/entry/2014/03/11/201558
 
 Add solution with permutation
 
 Key:
  - Search space is upper-bounded by 9!
  - All-pairs shortest path problem is impossible for 50*50 vertices. However by above constraint, it's possible to solve.
 
 Summary:
  - It took a lot of time to solve after figuring out path length is upper-bounded by 9 👎
  - Not only path length but also total number of slimes is upper-bounded by 9
   - If I figured out this, I should have solved earlier 😞
 
 */

int dist[51][51];
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
class SlimeXResidentSlime {
public:
  vector<string> B;
  int R,C;
  const int Inf=1e5;
  VI S; // pos of slimes
  int bfs(int s, int t) {
    REP(i,R)REP(j,C) dist[i][j]=Inf;
    queue<int> Q;
    Q.emplace(s); dist[s/C][s%C]=0;
    while(SZ(Q)) {
      int u=Q.front(); Q.pop();
      int i=u/C,j=u%C;
      if(u==t) return dist[i][j];
      FORR(m,moves) {
        int ii=i+m.first,jj=j+m.second;
        if(ii>=R||ii<0||jj>=C||jj<0) continue;
        if(B[ii][jj]=='#') continue;
        if(dist[ii][jj]>dist[i][j]+1) {
          dist[ii][jj]=dist[i][j]+1;
          Q.emplace(ii*C+jj);
        }
      }
    }
    return Inf;
  }
  int exterminate(vector<string> B) {
    this->B=B;
    R=SZ(B),C=SZ(B[0]);
    int s=-1;
    REP(i,R) REP(j,C) {
      if(B[i][j]=='$') s=i*C+j;
      if(isdigit(B[i][j])) S.push_back(i*C+j);
    }
    if(SZ(S)>9) return -1;
    
    int N=SZ(S);
    VI D(N,Inf);
    REP(i,N) D[i]=bfs(s,S[i]);
    vector<VI> mx(N, VI(N, Inf));
    REP(j,N) REP(i,j) {
      mx[i][j]=mx[j][i]=bfs(S[i], S[j]);
    }
    
    int res=Inf;
    VI P(N); REP(i,N) P[i]=i;
    do {
      int x=0;
      VI T(N,0);
      REP(i,N-1) x+=mx[P[i]][P[i+1]], T[i+1]=x;
      bool ok=true;
      REP(i,N) {
        int p=S[P[i]];
        ok&=(x-T[i]<B[p/C][p%C]-'0');
      }
      if(ok) SMIN(res,D[P[0]]+x);
    } while(next_permutation(P.begin(),P.end()));
    return res>=Inf?-1:res;
  }
};

// O(R*C*4^P) time
int viz[51][51];
class SlimeXResidentSlime_org {
  public:
  vector<string> B;
  int R,C;
  VI S; // pos of slimes
  MAPII SS;
  int step;
  void dfs(int i, int j, int d, int st) {
    if(d==0) return;
//    if(viz[i][j]) return;
//    viz[i][j]=true;
    int prev=-2;
    if(isdigit(B[i][j])) {
      if(SS.count(i*C+j)==0) {
        prev=-1;
      } else {
        prev=SS[i*C+j];
      }
      SS[i*C+j]=st;
    }
//    dump4(i,j,d,SZ(SS));
    if(SZ(SS)==SZ(S)) {
      bool ok=true;
      FORR(kvp,SS) {
        int pos=kvp.first;
        if(st-kvp.second>=(B[pos/C][pos%C]-'0')) {
          ok=false;
          break;
        }
      }
//      dump3(i,j,st);
      if(ok) SMIN(step,st);
    }
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii>=R||ii<0||jj>=C||jj<0) continue;
      if(B[ii][jj]=='#') continue;
      dfs(ii,jj,d-1,st+1);
    }
//    viz[i][j]=false;
    if(prev>-2) {
      if(prev==-1) SS.erase(i*C+j);
      else SS[i*C+j]=prev;
    }
  }
  int exterminate(vector<string> B) {
    this->B=B;
    const int Inf=1e5;
    R=SZ(B),C=SZ(B[0]);
    int s=-1;
    REP(i,R) REP(j,C) {
      if(B[i][j]=='$') s=i*C+j;
      if(isdigit(B[i][j])) S.push_back(i*C+j);
    }
    // avoid TLE
    if(SZ(S)>81) return -1;
    REP(i,R)REP(j,C) dist[i][j]=Inf;
    queue<II> Q; Q.emplace(0,s); dist[s/C][s%C]=0;
    while(SZ(Q)) {
      auto p=Q.front(); Q.pop();
      int d=p.first,pos=p.second;
      int i=pos/C,j=pos%C;
      FORR(m,moves) {
        int ii=i+m.first,jj=j+m.second;
        if(ii>=R||ii<0||jj>=C||jj<0) continue;
        if(B[ii][jj]=='#') continue;
        if(dist[ii][jj]>d+1) {
          dist[ii][jj]=d+1;
          Q.emplace(d+1,C*ii+jj);
        }
      }
    }
    int res=Inf;
    dump2(s/C,s%C);
    
    /*
    REP(i,R) {
      cout<<i<<"|";
      REP(j,C) cout << dist[i][j] << ",";
      cout<<endl;
    }*/
    
    REP(i,R)REP(j,C) if(isdigit(B[i][j])) {
      ZERO(viz); step=Inf; SS.clear();
      dump2(i,j);
      dfs(i,j,B[i][j]-'0', 0);
      dump3(dist[i][j],step,dist[i][j]+step);
      if(step<Inf) SMIN(res,dist[i][j]+step);
    }
    return res>=Inf?-1:res;
  }
};

// CUT begin
ifstream data("SlimeXResidentSlime.sample");

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

bool do_test(vector<string> field, int __expected) {
    time_t startClock = clock();
    SlimeXResidentSlime *instance = new SlimeXResidentSlime();
    int __result = instance->exterminate(field);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521916310;
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
        cout << "SlimeXResidentSlime (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
