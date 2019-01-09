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
 
 12/12/2017
 
 8:35-8:46 analysis
 8:47-8:54 submit 1WA (358.92 pt)
 missed a corner case that  B**** (no reverse needed) orz
 9:45-9:47 fixed a bug and ACC
 
 What we can do is only below:
  - Drop head or tail
  - Reverse
 
 So we can transform A to B only when 1) B or 2) reversed(B) is substring of A.
 
 My analysis of greedy:
 
 1) B is substring of A
  A = XBY, |X|=a, |Y|=b
 
  We can try to drop X and Y in different orders (X,Y) and (Y,X)
 
  1-1) X->Y
   1 (reverse: Y'B'X') + a (drop X': Y'B') + 1 (reverse: BY) + b (drop Y: B)
     => a+b+2
  1-2) Y->X
   b (drop Y: XB) + 1 (reverse: B'X') + a (drop X': B') + 1 (reverse: B)
     => a+b+2
   There is a corner case in this case. If X is empty (a=0), step is only dropping Y => b (1WA)
 
  So in either step, step is a+b+2 (b if a=0)
 
 2) reversed(B) is substring of A
  A = XB'Y, |X|=a, |Y|=b
 
  2-1) X->Y
   b (drop Y: XB') + 1 (reverse: BX') + a (drop X': B)
     => a+b+1
  2-2) Y->X
   1 (reverse: Y'BX') + a (drop X': Y'B) + 1 (reverse: B'Y) + b (drop Y: B') + 1 (reverse: B)
     => a+b+3
 
  So X->Y is better. We can take a+b+1. It's same even when a=0 or b=0.
 
 Since there is a state loop due to A=reverse(reverse(A)), DP is not applicable.
 However reverse or drop character operation is always one operation.
 We can build graph with unit distance. Vertices are different strings.
 There are at most 2*C(10,2) (=90) vertices.
 Now problem is reduced to single source shortest distance in unit distance graph.
 This can be solved by BFS.
 
 17:00-17:15 add BFS solution
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+574
   - BFS, greedy, brute-force (backtracking)
  - http://kmjp.hatenablog.jp/entry/2013/03/26/1030
   - greedy
  - http://purple-jwl.hatenablog.com/entry/20130326/1364304233
   - backtracking
  - http://sucrose.hatenablog.com/entry/2013/03/26/021628
   - greedy
 
 Summary:
  - 1WA due to missing analysis of corner case (no head or tail)
  - BFS solution is neat
 
 */

// BFS, O(LA^3) time, note that O(LA) for reversing string is part of it.
class TheNumberGameDiv2 {
public:
  int minimumMoves(int AA, int BB) {
    string A=to_string(AA),B=to_string(BB);
//    const int Inf=100;
    unordered_map<string,int> dist;
    dist[A]=0;
    queue<string> Q; Q.emplace(A);
    while(SZ(Q)) {
      string s=Q.front(); Q.pop();
      int d=dist[s];
      int d2=d+1;
      
      // reverse
      string t1=s;
      reverse(t1.begin(),t1.end());
      if(dist.count(t1)==0||dist[t1]>d2) {
        dist[t1]=d2;
        Q.emplace(t1);
      }
      
      if(SZ(s)==1) continue;
      
      // drop tail
      string t2=s;
      t2.pop_back();
      if(dist.count(t2)==0||dist[t2]>d2) {
        dist[t2]=d2;
        Q.emplace(t2);
      }
    }
    
    return dist.count(B)==0?-1:dist[B];
  }
};

// greedy, O(LA) time
class TheNumberGameDiv2_greedy {
  public:
  int minimumMoves(int AA, int BB) {
    string A=to_string(AA),B1=to_string(BB),B2=B1;
    reverse(B2.begin(),B2.end());
    int LA=SZ(A),LB=SZ(B1);
    
    const int Inf=100;
    int res=Inf;
    REP(i,LA) {
      string sa=A.substr(i,LB);
      int a=i,b=LA-a-LB;
      if(sa==B1) res=min(res,a>0?a+b+2:b);
      if(sa==B2) res=min(res,a+b+1);
    }
    return res==Inf?-1:res;
  }
};

// CUT begin
ifstream data("TheNumberGameDiv2.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int A, int B, int __expected) {
    time_t startClock = clock();
    TheNumberGameDiv2 *instance = new TheNumberGameDiv2();
    int __result = instance->minimumMoves(A, B);
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513096484;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheNumberGameDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
