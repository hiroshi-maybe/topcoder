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
 
 2/25/2018
 
 9:56-10:09 analysis
 10:10-10:44 ACC (261.95 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+525
  - http://d.hatena.ne.jp/kusano_prog/20111223/1324668604
  - http://purple-jwl.hatenablog.com/entry/20121024/1351074203
  - http://d.hatena.ne.jp/nise_nabe/20111130/1322622396
  - http://wabelog.blogspot.com/2011/12/topcoder-srm-525.html?m=0
  - https://www.muo.jp/2011/12/topcoder-srm-srm-525-div-2-easymedium.html
 
 Oooops. It turned out that no need to calculate a+b+c+d by looking at empty rows or columns.
 
 My original code was looking for below (a,b,c,d):
 
 ....o.... <-a
 .........
 o..****.o
 .o.****.o
 .........
 ...o..o.. <-d
  ^b     ^c
 
 Note that * is the rectangle that has K coins.
 However this gives same result as below:
 
 ....o.... <-a
 ..******.
 o.******o
 .o******o
 ..******.
 ...o..o.. <-d
 ^b     ^c

 This larger rectangle * has the same K coins.
 So no need to re-compute border (a,b,c,d).
 
 13:30-13:36 Add simpler solution with 2d cumulative sum library (O(R^2*C^2) time)
 14:00-14:06 add solutin without cumulative sum (O(R^3*C^3) time)
 
 Key:
  - There are at most R^2*C^2 final states. Brute-force it.
 
 Summary:
  - Analysis was straighforward. Brute-force final state
  - toooo slow implementation 👎
   - mistake in two dimensions comulative sum 👎👎
   - several mistakes in query range 👎👎👎👎
 
 */

// O(R^3*C^3) time
class DropCoins {
public:
  int getMinimum(vector<string> B, int K) {
    int R=SZ(B),C=SZ(B[0]);
    
    const int Inf=1e8;
    int res=Inf;
    
    REP(i1,R)REP(j1,C)FORE(i2,i1+1,R)FORE(j2,j1+1,C) {
      int cnt=0;
      FOR(i,i1,i2)FOR(j,j1,j2) cnt+=B[i][j]=='o';
      if(cnt!=K) continue;
      int a=i1,b=R-i2,c=j1,d=C-j2;
      SMIN(res,2*min(a,b)+max(a,b)+2*min(c,d)+max(c,d));
    }
    
    return res==Inf?-1:res;
  }
};

struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum(vector<vector<int>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<int>>(R+1,vector<int>(C+1,0));
    
    REP(i,R) REP(j,C) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  int query(int i1, int j1, int i2, int j2) {
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<int>> cum;
};

// O(R^2*C^2) time
class DropCoins_cumsum {
public:
  int getMinimum(vector<string> B, int K) {
    int R=SZ(B),C=SZ(B[0]);
    vector<vector<int>> X(R,VI(C,0));
    REP(i,R) REP(j,C) X[i][j]=B[i][j]=='o';
    TwoDimCumSum cum(X);
    
    const int Inf=1e8;
    int res=Inf;
    REPE(i2,R)REPE(j2,C)REP(i1,i2)REP(j1,j2) if(cum.query(i1,j1,i2,j2)==K) {
      int a=i1,b=j1,c=C-j2,d=R-i2;
      res=min(res,min(a,d)*2+max(a,d)+min(b,c)*2+max(b,c));
    }
    return res==Inf?-1:res;
  }
};

int cum[35][35];
class DropCoins_org {
  public:
  int sum(int i1, int j1, int i2, int j2) {
//    dump4(i1,j1,i2,j2);
    return cum[i2][j2]-cum[i2][j1]-cum[i1][j2]+cum[i1][j1];
  }
  int getMinimum(vector<string> B, int K) {
    ZERO(cum);
    int R=SZ(B),C=SZ(B[0]);
    REP(i,R) REP(j,C) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+(B[i][j]=='o');
    }
    
    const int Inf=1e8;
    int res=Inf;
    REPE(i2,R)REPE(j2,C)REP(i1,i2)REP(j1,j2) if(sum(i1,j1,i2,j2)==K) {
      // below complicated computation is actually unnecessary 😭
      int u=sum(0,0,i1,C);
      int a=0; while(a<i1&&sum(0,0,a,C)<u) ++a;
      int l=sum(0,0,R,j1);
      int b=0; while(b<j1&&sum(0,0,R,b)<l) ++b;
      int r=sum(0,j2,R,C);
      int c=0; while(sum(0,C-c,R,C)<r) ++c;
      int dw=sum(i2,0,R,C);
      int d=0; while(sum(R-d,0,R,C)<dw) ++d;
      res=min(res,min(a,d)*2+max(a,d)+min(b,c)*2+max(b,c));
    }
    return res==Inf?-1:res;
  }
};

// CUT begin
ifstream data("DropCoins.sample");

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
    DropCoins *instance = new DropCoins();
    int __result = instance->getMinimum(board, K);
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
        int T = time(NULL) - 1519581372;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DropCoins (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
