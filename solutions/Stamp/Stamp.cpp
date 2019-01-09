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
 
 1/4/2017
 
 9:22-9:40 pause
 10:25-10:38 analysis
 10:43 Sample #4,5 don't pass
 10:47 Fixed a bug and submit. System test passed.
 
 f(N,_) = 0
 f(x,c) = Inf if x>=N-L
 f(x,c) = Inf if ∃i∈{x..x+L-1} s.t. S[i]!='*' AND S[i]!=c
 f(x,c) = min { 1+f(x+i,c) : i=1..L-1 } ∪ { 1+f(x+L,c') : c'∈{R,G,B} }

 res = min { C1*L+C2*f(0,c) : L∈{1..N}, c∈{R,G,B} }
 
 Running time: O(N^3) time
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+558
  - http://kmjp.hatenablog.jp/entry/2012/10/19/0900
  - http://topcoder.g.hatena.ne.jp/hotoku/20121021/1350784917
  - http://mayokoex.hatenablog.com/entry/2016/07/11/204550
 
 Key:
  - Brute-force possible L
  - For each L, compute minimum number of times to push stamps by DP
 
 Summary:
  - In actual contest, only 7 people solved though, analysis was straightforward for me
  - I misunderstood problem again
   - When I started a problem, I misunderstood that we can create stamps with different length
   - Once figuring out L is single, brute-forcing all the L was a good first step
 
 */
int memo[51][3];
class Stamp {
  public:
  const int Inf=1e3;
  int N;
  int L;
  VI S;
  int f(int x, int c) {
    int &res=memo[x][c];
    if(res>=0) return res;
    if(x==N) return res=0;
    res=Inf;
    if(x>N-L) return res;
    FOR(i,x,x+L) if(S[i]!=3&&S[i]!=c) return res;
    FOR(i,1,L) res=min(res,1+f(x+i,c));
    REP(cc,3) res=min(res,1+f(x+L,cc));
    return res;
  }
  int getMinimumCost(string desiredColor, int C1, int C2) {
    this->N=SZ(desiredColor);
    REP(i,N) {
      char c=desiredColor[i];
      int a=3;
      if(c=='R')a=0;
      if(c=='G')a=1;
      if(c=='B')a=2;
      S.push_back(a);
    }
    int res=1e9;
    FOR(L,1,N+1) {
      MINUS(memo);
      this->L=L;
      REP(c,3) res=min(res,C1*L+C2*f(0,c));
    }
    return res;
  }
};

// CUT begin
ifstream data("Stamp.sample");

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

bool do_test(string desiredColor, int stampCost, int pushCost, int __expected) {
    time_t startClock = clock();
    Stamp *instance = new Stamp();
    int __result = instance->getMinimumCost(desiredColor, stampCost, pushCost);
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
        string desiredColor;
        from_stream(desiredColor);
        int stampCost;
        from_stream(stampCost);
        int pushCost;
        from_stream(pushCost);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(desiredColor, stampCost, pushCost, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515086553;
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
        cout << "Stamp (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
