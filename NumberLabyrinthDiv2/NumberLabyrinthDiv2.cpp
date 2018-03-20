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
 
 3/19/2018
 
 8:53-9:10 analysis
 9:11-9:30 ACC (504.84 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+509
  - http://kmjp.hatenablog.jp/entry/2014/02/14/1000
  - http://d.hatena.ne.jp/kusano_prog/20110610/1307711120
  - http://topcoder.g.hatena.ne.jp/firewood/20110618
  - http://purple-jwl.hatenablog.com/entry/20130401/1364792780
  - http://area.hateblo.jp/entry/2013/08/20/020320
 
 Key:
  - At most R*C*K states to remember
  - Problem can be reduced to shortest path with unit distance
 
 Summary:
  - No major issue to both analysis and implementation
 
 */
int dist[51][51][51];
class NumberLabyrinthDiv2 {
  public:
  int R,C;
  void enQ(int i, int j, int step, int k, queue<III> &Q) {
//    dump4(i,j,k,step);
    if(i<0||j<0||i>=R||j>=C) return;
    if(dist[i][j][k]<=step) return;
    dist[i][j][k]=step;
    dump4(i,j,k,step);
    Q.emplace(step,i*C+j,k);
  }
  
  int getMinimumNumberOfMoves(vector<string> B, int r1, int c1, int r2, int c2, int K) {
    const int Inf=1e5;
    this->R=SZ(B),this->C=SZ(B[0]);
    REP(i,R)REP(j,C)REPE(k,K) dist[i][j][k]=Inf;
    dist[r1][c1][K]=0;
    queue<III> Q; Q.emplace(0,r1*C+c1,K);
    while(SZ(Q)) {
      int step,p,k;
      tie(step,p,k)=Q.front(); Q.pop();
      int i=p/C,j=p%C;
//      dump4(i,j,step,k);
      if(B[i][j]!='.') {
        int d=B[i][j]-'0';
        if(d==0) continue;
        for(int ii=i-d; ii<=i+d; ii+=d) enQ(ii,j,step+1,k,Q);
        for(int jj=j-d; jj<=j+d; jj+=d) enQ(i,jj,step+1,k,Q);
      } else {
        if(k<=0) continue;
        for(int d=1; d<10; ++d) {
          for(int ii=i-d; ii<=i+d; ii+=d) enQ(ii,j,step+1,k-1,Q);
          for(int jj=j-d; jj<=j+d; jj+=d) enQ(i,jj,step+1,k-1,Q);
        }
      }
    }
    
    int res=Inf;
    REPE(k,K) SMIN(res,dist[r2][c2][k]);
    return res==Inf?-1:res;
  }
};

// CUT begin
ifstream data("NumberLabyrinthDiv2.sample");

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

bool do_test(vector<string> board, int r1, int c1, int r2, int c2, int K, int __expected) {
    time_t startClock = clock();
    NumberLabyrinthDiv2 *instance = new NumberLabyrinthDiv2();
    int __result = instance->getMinimumNumberOfMoves(board, r1, c1, r2, c2, K);
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
        int r1;
        from_stream(r1);
        int c1;
        from_stream(c1);
        int r2;
        from_stream(r2);
        int c2;
        from_stream(c2);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, r1, c1, r2, c2, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521474814;
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
        cout << "NumberLabyrinthDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
