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
 
 9/16/2017
 
 10:00-10:30 time up
 
 17:10-18:22 read editorials
  - https://apps.topcoder.com/wiki/display/tc/SRM+639
  - http://kmjp.hatenablog.jp/entry/2014/11/29/1000
  - http://topcoder.g.hatena.ne.jp/kuuso1/20141206/1417897417
 
 22:35-24:04 array initalization bug and TLE
 
 O(N*M^4+M*N^4) solution passed in div2 size though,
 O(N*M^2+M*N^2) algorithm is needed in div2 medium size.
 
 key:
  - horizontal fold is indepdent from vertical fold
  - implement complex fold validation without mistakes and analyze runtime
  - count rectangles withotu duplication
 
 summary:
  - hard to design due to complexity of rectangle subproblem and fold validation
  - touch implementation due to complicated boundary
  - rotated P initialization bug
  - at least try some samples to analyze
    - low-motivated due to messed up div2 medium
 
 */

int viz[51][51];
int res;
// O(N*M^4+M*N^4) time
class BoardFoldingDiv2 {
  public:
  vector<string> P;
  int M,N;
  // O(N) time
  bool rowcheck(int i1, int i2) {
    assert(0<=i1&&i1<M&&0<=i2&&i2<M);
    REP(j,N) if(P[i1][j]!=P[i2][j]) return false;
    return true;
  }
  // O(M*N) time
  bool canfold(int l, int r, int len) {
    REP(_,len) {
      if(!rowcheck(l,r)) return false;
      --l,++r;
    }
    return true;
  }

  // O(N*M^2) time
  // rectangle rows in [a,M-b-1]
  void countRow(int a, int b) {
    assert(0<=a&&a<M&&0<=b&&b<M);
    if(viz[a][b]) return;
    viz[a][b]=true;
    res+=1;
    for(int x=a; x<M-b-1; ++x) {
      int r1=x-a+1,r2=M-b-a-r1;
      if(canfold(x,x+1,min(r1,r2))) {
        if(r1<r2) {
          countRow(a+r1,b);
        } else if(r1>r2) {
          countRow(a,b+r2);
        } else {
          countRow(a+r1,b);
          countRow(a,b+r2);
        }
      }
    }
  }
  
  int howMany(vector<string> P) {
    this->P=P;
    this->M=SZ(P),this->N=SZ(P[0]);
    
    ZERO(viz); res=0;
    countRow(0,0);

    int res1=res;
    
    vector<string> PP(N,string(M,'#'));
    
    REP(i,M) REP(j,N) PP[j][i]=P[i][j];
    
    this->P=PP;
    this->M=SZ(PP),this->N=SZ(PP[0]);
    
    ZERO(viz); res=0;
    countRow(0,0);

    int res2=res;
    
    return res1*res2;
  }
};

// CUT begin
ifstream data("BoardFoldingDiv2.sample");

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

bool do_test(vector<string> paper, int __expected) {
    time_t startClock = clock();
    BoardFoldingDiv2 *instance = new BoardFoldingDiv2();
    int __result = instance->howMany(paper);
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
        vector<string> paper;
        from_stream(paper);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(paper, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505581215;
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
        cout << "BoardFoldingDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
