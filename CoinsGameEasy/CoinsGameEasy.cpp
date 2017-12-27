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
 
 12/26/2017
 
 10:39-10:44 analysis
 10:45-10:56 implement, submit and system test passed (415.32 pt)
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+563
   - backtracking
  - http://kmjp.hatenablog.jp/entry/2012/12/09/1000
   - backtracking
  - http://purple-jwl.hatenablog.com/entry/20130120/1358700573
  - http://expnotes9.blog.fc2.com/blog-entry-30.html
 
 Summary:
  - 4^11 ≈4*10^6. Just simulate by BFS or DFS
 
 */

// O(4^D) time (if prune states by shortest path, this is reduced to O(R^2*C^2) time
vector< pair < int, int > >  moves = { {0,1},{1,0},{0,-1},{-1,0} };
class CoinsGameEasy {
  public:
  int minimalSteps(vector<string> B) {
    int R=SZ(B),C=SZ(B[0]);
    int a1=-1,a2=-1;
    REP(i,R)REP(j,C) if(B[i][j]=='o') {
      B[i][j]='.';
      if(a1==-1) a1=C*i+j;
      else a2=C*i+j;
    }
    assert(a1>=0&&a2>=0);
    queue<II> Q; Q.emplace(a1,a2);
    
    int d=0;
    while(SZ(Q)&&d<10) {
      ++d;
      int N=SZ(Q);
      REP(_,N) {
        auto p=Q.front(); Q.pop();
        int a1=p.first,a2=p.second;
        int i1=a1/C,j1=a1%C,i2=a2/C,j2=a2%C;
        FORR(m,moves) {
          int ii1=i1+m.first,jj1=j1+m.second;
          int ii2=i2+m.first,jj2=j2+m.second;
          
          bool fall1=ii1<0||ii1>=R||jj1<0||jj1>=C;
          bool fall2=ii2<0||ii2>=R||jj2<0||jj2>=C;
          
          if(!fall1&&B[ii1][jj1]=='#') ii1=i1,jj1=j1;
          if(!fall2&&B[ii2][jj2]=='#') ii2=i2,jj2=j2;

          // either falls
          if(fall1^fall2) return d;
          
          // both fall
          if(fall1&&fall2) continue;
          // ovarlap
          if(ii1==ii2&&jj1==jj2) continue;
          // stay
          if(ii1==i1&&jj1==j1&&ii2==i2&&jj2==j2) continue;
          
          Q.emplace(ii1*C+jj1,ii2*C+jj2);
        }
      }
    }
    
    return -1;
  }
};

// CUT begin
ifstream data("CoinsGameEasy.sample");

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
    CoinsGameEasy *instance = new CoinsGameEasy();
    int __result = instance->minimalSteps(board);
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
        int T = time(NULL) - 1514313557;
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
        cout << "CoinsGameEasy (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
