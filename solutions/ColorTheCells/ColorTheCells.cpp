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
 
 11/20/2017
 
 9:07-9:22 analysis
 9:22-9:42 implement and submit (513.61 pt)

 Editorial:
  - http://kmjp.hatenablog.jp/entry/2013/06/16/0930
  - http://emkcsharp.hatenablog.com/entry/SRM582/ColorTheCells
 
 Key:
  - brute force works
  - two positions to paint a cell
 
 Summary:
  - straightforward analysis to find brute force
  - a few bugs in implementation
 
 Submit solutions:
  - clean backtracking
    - https://community.topcoder.com/stat?c=problem_solution&rm=317745&rd=15502&pm=12581&cr=22934070
 
 */

// O(N!*2^7*N) time ≈5*10^6
int T[7];
class ColorTheCells {
  public:
  const int Inf=1e8;
  int mv(int st, int dest, int t) {
    int d=st<dest?1:-1;
    int cur=st;
    while(cur!=dest) {
      if(T[cur+d]<=t) ++t;
      else t=T[cur+d]+1;
      cur+=d;
    }
    return t;
  }
  int minimalTime(vector<int> D) {
    int N=SZ(D);
    VI ord;
    REP(i,N) ord.push_back(i);
    
    int res=Inf;
    do {
      // 1:r, 0:l
      REP(mask,1<<N) if((mask&1)&&(mask&(1<<(N-1)))==0) {
        ZERO(T);
        int t=0;
        int cur=0;
        REP(i,N) {
          int next=ord[i],dest=next;
          if((mask>>dest)&1) ++dest;
          else --dest;
          assert(0<=dest&&dest<N);
          t=mv(cur,dest,t); // move
          ++t; // paint
          T[next]=t+D[next];
          cur=dest;
        }
        res=min(res,t);
      }
    } while(next_permutation(ord.begin(),ord.end()));
    return res;
  }
};

// CUT begin
ifstream data("ColorTheCells.sample");

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

bool do_test(vector<int> dryingTime, int __expected) {
    time_t startClock = clock();
    ColorTheCells *instance = new ColorTheCells();
    int __result = instance->minimalTime(dryingTime);
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
        vector<int> dryingTime;
        from_stream(dryingTime);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(dryingTime, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1511197612;
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
        cout << "ColorTheCells (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
