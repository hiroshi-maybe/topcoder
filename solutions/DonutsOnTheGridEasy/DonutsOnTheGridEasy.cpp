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
 
 16:16-16:46 I cannot understand problem statement and sample #4 at all
 
 If below case #1 gives 3, why case #2 is invalid? It's ridiculous 😡
 If we are interested in ONLY nested donuts, case #1 should return 2 rather than 3. Sigh...
 
 case #1
 
 "0000000....",
 "0.....0....",
 "0.000.0.000",
 "0.0.0.0.0.0",
 "0.000.0.000",
 "0.....0....",
 "0000000...."
 
 case #2
 
 "0000000....",
 "0.000.0....",
 "0000000.000",
 "0000000.0.0",
 "0.000.0.000",
 "0000000....",
 "0000000...."
 
 Ok. Looks like no need to insert '.'.
 So looks like below is intended 3 donuts in sample #4.
 Example is too poor.
 
 "1111111....",
 "1222221....",
 "1233321.000",
 "1230321.0.0",
 "1233321.000",
 "1222221....",
 "1111111...."
 
 17:32 finally I understood the problem.
 17:45 got AC
 
 http://apps.topcoder.com/wiki/display/tc/Member+SRM+455
 https://ameblo.jp/utmath/entry-10988360181.html
 https://chngng.blogspot.com/2015/05/srm-455-div1-easy-donutsonthegrideasy.html
 
 */

int memo[51][51][51][51];
int cumR[51][51],cumC[51][51];
class DonutsOnTheGridEasy {
  public:
  vector<string> G;
  int N,M;
  bool ok(int i, int j, int h, int w) {
    bool res=true;
    /*
    if(i==0&&j==0&&h==7&&w==7) {
      dump4(cumR[i+h][j],cumR[i][j],h,cumR[i+h][j]-cumR[i][j]);
      dump4(cumR[i+h][j+w-1],cumR[i][j+w-1],h,cumR[i+h][j+w-1]-cumR[i][j+w-1]);
      dump4(cumC[i][j+w],cumC[i][j],w,cumC[i][j+w]-cumC[i][j]);
      dump4(cumC[i+h-1][j+w],cumC[i+h-1][j],w,cumC[i+h-1][j+w]-cumC[i+h-1][j]);
    }*/
    
    res&=cumR[i+h][j]-cumR[i][j]==h;
    res&=cumR[i+h][j+w-1]-cumR[i][j+w-1]==h;
    res&=cumC[i][j+w]-cumC[i][j]==w;
    res&=cumC[i+h-1][j+w]-cumC[i+h-1][j]==w;
    return res;
  }
  int f(int r1, int c1, int r2, int c2) {
    int &res=memo[r1][c1][r2][c2];
    if(res>=0) return res;
    int h=r2-r1,w=c2-c1;
    if(h<3||w<3) return res=0;
    
    res=0;
    if(ok(r1,c1,h,w)) SMAX(res,1+f(r1+1,c1+1,r2-1,c2-1));
    SMAX(res,f(r1+1,c1,r2,c2));
    SMAX(res,f(r1,c1+1,r2,c2));
    SMAX(res,f(r1,c1,r2-1,c2));
    SMAX(res,f(r1,c1,r2,c2-1));
    
    /*
    if(r1==0&&c1==0&&r2==7&&c2==7) {
      dump4(r1,c1,r2,c2);
      dump2(ok(r1,c1,h,w),res);
    }*/
    
    return res;
  }
  int calc(vector<string> G) {
    this->G=G;
    this->N=SZ(G),this->M=SZ(G[0]);
    MINUS(memo);
    REP(j,M) {
      cumR[0][j]=0;
      REP(i,N) cumR[i+1][j]=G[i][j]=='0'?cumR[i][j]+1:0;
    }
    REP(i,N) {
      cumC[i][0]=0;
      REP(j,M) cumC[i][j+1]=G[i][j]=='0'?cumC[i][j]+1:0;
    }
    return f(0,0,N,M);
  }
};

// CUT begin
ifstream data("DonutsOnTheGridEasy.sample");

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

bool do_test(vector<string> grid, int __expected) {
    time_t startClock = clock();
    DonutsOnTheGridEasy *instance = new DonutsOnTheGridEasy();
    int __result = instance->calc(grid);
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
        vector<string> grid;
        from_stream(grid);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536880568;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DonutsOnTheGridEasy (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
