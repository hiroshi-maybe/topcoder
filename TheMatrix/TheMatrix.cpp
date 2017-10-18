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
 
 10/17/2017
 
 9:08-9:30 analysis
 9:31-9:51 1WA (254.68 pt)
 9:58 bugfix and system test passed
 
 Solved by O(N^4) algorithm.
 Try all left top corner (N^2) and compute largest rectangle maintaining valid width.
 
 23:30- add solution in official editorial
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+610
   - brute force left right index and check 0/1 by DP. O(N^3) time.
  - http://kmjp.hatenablog.jp/entry/2014/03/01/0900
   - pre-compute consecutive 0/1 and brute force top right positions. O(N^3) time.
   - more efficient algorithm than my original solution
  - 2D cumulative sum. O(N^4) times
   - http://torus711.hatenablog.com/entry/20140226/p1
   - http://topcoder.g.hatena.ne.jp/kagamiz/20140305
   - http://topcoder.g.hatena.ne.jp/kojingharang/20140226#1393393731
 
 submit solutions:
  - @kmjp's approach (precompute consecutive length and try all top right positions
   - https://community.topcoder.com/stat?c=problem_solution&rm=320789&rd=15843&pm=13035&cr=23082290
   - https://community.topcoder.com/stat?c=problem_solution&rm=320803&rd=15843&pm=13035&cr=23176728
   - https://community.topcoder.com/stat?c=problem_solution&rm=320797&rd=15843&pm=13035&cr=23026606
   - https://community.topcoder.com/stat?c=problem_solution&rm=320808&rd=15843&pm=13035&cr=23099298
 
 */

// similar to dp in 2D Kadane's algorithm, @kmjp solution
// O(N^3) time
int mx[101][101];
class TheMatrix {
public:
  int MaxArea(vector<string> G) {
    int R=SZ(G),C=SZ(G[0]);
    ZERO(mx);
    REP(i,R)REP(j,C) {
      if(j==0||G[i][j-1]==G[i][j]) mx[i][j]=1; // reset
      else mx[i][j]=mx[i][j-1]+1;
    }
    
    int res=1;
    REP(i,R)REP(j,C) {
      int w=mx[i][j];
      for(int h=1; i+h<=R; ++h) {
        if(h>1&&G[i+h-1][j]==G[i+h-2][j]) break;
        w=min(w,mx[i+h-1][j]);
        res=max(res,h*w);
      }
    }
    
    return res;
  }
};

// similar to dp in 2D Kadane's algorithm, official editorial solution.
// O(N^3) time
class TheMatrix_leftright_dp {
public:
  int MaxArea(vector<string> G) {
    int M=SZ(G),N=SZ(G[0]);
    
    int res=1;
    REP(l,N) {
      VI rs(M,0);
      FOR(r,l+1,N+1) {
        REP(i,M) {
          if(rs[i]==3) continue;
          if(r-l==1) {
            rs[i]=G[i][r-1]-'0';
          } else if(G[i][r-1]!=(G[i][r-2]^1)) {
            rs[i]=3;
          }
        }

        int i=0;
        while(i<M) {
          while(i<M&&rs[i]==3) ++i;
          if(i==M) break;
          int j=i+1;
          while(j<M&&rs[j-1]==(1^rs[j])) ++j;
          res=max(res,(j-i)*(r-l));
          i=j;
        }
      }
    }
    return res;
  }
};

// O(N^4) time, official editorial solution.
class TheMatrix_leftright {
public:
  int MaxArea(vector<string> G) {
    int M=SZ(G),N=SZ(G[0]);
    string s0(N,'0'),s1(N,'1');
    for(int i=1; i<N; i+=2) s0[i]='1',s1[i]='0';
//    dump2(s0,s1);
    
    int res=1;
    REP(r,N+1) REP(l,r) {
      string ss0=s0.substr(0,r-l),ss1=s1.substr(0,r-l);
      VI rs(M,0);
      REP(i,M) {
        string s=G[i].substr(l,r-l);
        if(s==ss0) rs[i]=0;
        else if (s==ss1) rs[i]=1;
        else rs[i]=3;
      }
//      dumpAR(rs);
      int i=0;
      while(i<M) {
        while(i<M&&rs[i]==3) ++i;
        if(i==M) break;
        int j=i+1;
        while(j<M&&rs[j-1]==(1^rs[j])) ++j;
        res=max(res,(j-i)*(r-l));
        i=j;
      }
    }
    return res;
  }
};

// O(N^4) time
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };
class TheMatrix_topleft {
  public:
  int MaxArea(vector<string> G) {
    int M=SZ(G),N=SZ(G[0]);
    
    int res=1;
    REP(i,M)REP(j,N) {
      int j2=j+1,r;
      for(; j2<N; ++j2) {
        if(G[i][j2]==G[i][j2-1]) break;
      }
      r=j2;
      res=max(res,j2-j);
      int i2=i+1;
      for(; i2<M; ++i2) {
//        dump4(i2,j,G[i2][j],G[i2-1][j]);
        if(G[i2][j]==G[i2-1][j]) break;
        res=max(res,(j2-j)*(i2-i));

        j2=j+1;
        for(; j2<r; ++j2) {
          if(G[i2-1][j2]==G[i2][j2]||G[i2][j2-1]==G[i2][j2]) { /*dump4(i2,j2,G[i2-1][j2],G[i2][j2-1]);*/ break; }
        }
        r=j2;
//        if(i==0&&j==2)dump4(i,j,i2,j2);
      }
      res=max(res,(j2-j)*(i2-i));
    }
    return res;
  }
};

// CUT begin
ifstream data("TheMatrix.sample");

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
    TheMatrix *instance = new TheMatrix();
    int __result = instance->MaxArea(board);
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
        int T = time(NULL) - 1508256527;
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
        cout << "TheMatrix (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
