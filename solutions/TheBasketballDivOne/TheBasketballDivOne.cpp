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
 
 9/13/2018
 
 13:57-14:37 AC. Too slow 😡
 
 http://apps.topcoder.com/wiki/display/tc/SRM+453
 
 I tried to solve by brute-forcing partition number.
 However I figured out that it cannot satisfy sample #3.
 I switched to brute-force solution.
 
 */
class TheBasketballDivOne_org {
  public:
  int N,M;
  int res=0;
  void dfs_wrong(int cur, int i, VI &A) {
    if(i==N) {
      if(cur==N*(N-1)){
      ++res;
        dumpAR(A);
      }
      return;
    }
    REPE(w,A.back()) {
      A.push_back(w);
      dfs_wrong(cur+w,i+1,A);
      A.pop_back();
    }
  }
  set<VI> ans;
  void dfs(int i, VI &cur) {
    if(i==N-1) {
//      dumpAR(cur);
      sort(cur.rbegin(),cur.rend());
      if(cur[0]==M) ans.emplace(cur);
      return;
    }
    int L=N-i-1;
    REP(mask1,1<<L) REP(mask2,1<<L) {
      VI cur2=cur;
      REP(l,L) {
        if((mask1>>l)&1) cur2[i+1+l]++;
        else cur2[i]++;
        if((mask2>>l)&1) cur2[i+1+l]++;
        else cur2[i]++;
      }
      dfs(i+1,cur2);
      /*
      REP(l,L) {
        if((mask1>>l)&1) cur[i+1+l]--;
        else cur[i]--;
        if((mask2>>l)&1) cur[i+1+l]--;
        else cur[i]--;
      }*/
    }
  }
  int find(int N, int M) {
    this->N=N,this->M=M;
    VI cur(N,0);
    dfs(0,cur);
    return SZ(ans);
  }
};

class TheBasketballDivOne {
public:
  int find(int N, int M) {
    int L=N*(N-1);
    set<VI> S;
    REP(mask,1<<L) {
      VI W(N,0);
      int k=0;
      REP(i,N)REP(j,N) if(i!=j) {
        if((mask>>k)&1) W[i]++;
        else W[j]++;
        ++k;
      }
      assert(k==L);
      assert(accumulate(W.begin(),W.end(),0)==L);
      sort(W.rbegin(),W.rend());
      if(W[0]==M) {
        S.emplace(W);
      }
    }
    return SZ(S);
  }
};

// CUT begin
ifstream data("TheBasketballDivOne.sample");

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

bool do_test(int n, int m, int __expected) {
    time_t startClock = clock();
    TheBasketballDivOne *instance = new TheBasketballDivOne();
    int __result = instance->find(n, m);
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
        int n;
        from_stream(n);
        int m;
        from_stream(m);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536871627;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheBasketballDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
