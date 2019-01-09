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
 
 10/2/2017
 
 16:09-16:22 analysis
 16:23-16:35 implement
 16:35-16:45 debug (bug of cumulative sum query), submit though 1WA (misunderstanding of problem)
 17:11 2WA
 17:14 system test passed
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2014/06/07/0900
   - no empty cell is process as K=0. So smart.
  - http://apps.topcoder.com/wiki/display/tc/SRM+623
  - http://torus711.hatenablog.com/entry/20140605/1401983286

 22:10-22:21 add simpler solution inspired by @kmjp solution
 
 key:
  - 2d cumulative sum to query in O(1)
  - necessary move is differnt in fruit and empty cell
 
 summary:
  - quickly figured out approach by 2d cumulative sum 👍
  - I forgout constraint that fruit can move to only empty cell 👎
 
 */

int cum[51][51][3];
class ApplesAndPears {
public:
  int cnt(int i1, int j1, int i2, int j2, int k) {
    return cum[i2][j2][k]-cum[i2][j1][k]-cum[i1][j2][k]+cum[i1][j1][k];
  }
  int getArea(vector<string> B, int K) {
    int N=SZ(B);
    ZERO(cum);
    int tot[3]={0,0,0};
    char cs[3]={'P','A','.'};
    REP(i,N) REP(j,N) REP(k,3) {
      cum[i+1][j+1][k]=cum[i+1][j][k]+cum[i][j+1][k]-cum[i][j][k]+(B[i][j]==cs[k]);
      tot[k]+=(B[i][j]==cs[k]);
    }
    
    if(tot[2]==0) K=0;
    int res=1;
    REP(i,N)REP(j,N)for(int h=1; i+h<=N; ++h)for(int w=1; j+w<=N; ++w) REP(k,3) {
      int a=w*h;
      if(a>tot[k]) continue;
      if(k==2) {
        int n=cnt(i,j,i+h,j+w,k);
        if(a-n<=K) res=max(res,a);
      } else {
        int en=cnt(i,j,i+h,j+w,2),xn=cnt(i,j,i+h,j+w,k^1);
        if(en+2*xn<=K) res=max(res,a);
      }
    }
    return res;
  }
};

class ApplesAndPears_org {
  public:
  int cnt(int i1, int j1, int i2, int j2, int k) {
    return cum[i2][j2][k]-cum[i2][j1][k]-cum[i1][j2][k]+cum[i1][j1][k];
  }
  int getArea(vector<string> B, int K) {
    int N=SZ(B);
    ZERO(cum);
    int tot[3]={0,0,0};
    char cs[3]={'P','A','.'};
    REP(i,N) REP(j,N) REP(k,3) {
      cum[i+1][j+1][k]=cum[i+1][j][k]+cum[i][j+1][k]-cum[i][j][k]+(B[i][j]==cs[k]);
      tot[k]+=(B[i][j]==cs[k]);
    }
    
    int res=1;
    REP(i1,N)REP(j1,N)FOR(i2,i1+1,N+1)FOR(j2,j1+1,N+1)REP(k,3) {
      int extra=tot[k]-cnt(i1,j1,i2,j2,k), missing=(i2-i1)*(j2-j1)-cnt(i1,j1,i2,j2,k);
      if(extra>=missing&&missing<=K) {
        if(k==2||missing==0) {
          res=max(res,(i2-i1)*(j2-j1));
          continue;
        }
        int cntE=cnt(i1,j1,i2,j2,2);
        int k=K-cntE;
        int cntF=missing-cntE;
        if(tot[2]>=1&&k>=cntF*2) res=max(res,(i2-i1)*(j2-j1));
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ApplesAndPears.sample");

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

bool do_test(vector<string> board, int K, int __expected) {
    time_t startClock = clock();
    ApplesAndPears *instance = new ApplesAndPears();
    int __result = instance->getArea(board, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506985737;
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
        cout << "ApplesAndPears (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
