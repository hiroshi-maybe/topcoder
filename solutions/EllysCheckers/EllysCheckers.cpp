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
 
 2/9/2018
 
 9:04-9:09 analysis
 9:10-9:16 implement (424.47 pt)
 
 Editorials:
  - greedy
   - https://apps.topcoder.com/wiki/display/tc/SRM+534
  - bit DP
   - http://mayokoex.hatenablog.com/entry/2016/03/10/002504
   - http://topcoder.g.hatena.ne.jp/peryaudo/20131107/1383804910
   - https://topcoder.g.hatena.ne.jp/jackpersel/20120303/1330849477
   - http://naoyat.hatenablog.jp/entry/2012/02/24/233000
   - http://kg86.hatenablog.com/entry/20130411/1365701406
   - http://rkx1209.hatenablog.com/entry/2012/11/08/231938
   - https://topcoder.g.hatena.ne.jp/firewood/20120225/1330153505
 
 Greedy:
  - https://community.topcoder.com/stat?c=problem_solution&rm=311746&rd=14727&pm=11791&cr=22921629
  - https://community.topcoder.com/stat?c=problem_solution&rm=311720&rd=14727&pm=11791&cr=22820015
  - https://community.topcoder.com/stat?c=problem_solution&rm=311721&rd=14727&pm=11791&cr=22856555
 
 a) Single checker
 
 Suppose there is a single checker as below
 
 ..X..|
 
 It takes 2 steps to move this checker X to right-most position at N-1.
 If N-1-i is odd, first player wins. Otherwise second player wins.
 
 .YX..|
 
 Even if we have another checker Y at i-1, Y cannot go beyond a as long as we don't have three consecutive checkers.
 So It needs N-1-(i-1) steps. Steps to move checkers are mutually independent.
 
 b) Three consecutive checkers
 
 XYZ..| => .YZX.| (1 step)
 
 As seen above, X goes right of Z. However three checkers stay in consecutive positions.
 In this case, parity of total number of steps does not actually change comparing with a case moving one by one.

 XYZ..| => .XYZ.| (3 step)

 From observation of a) and b), we can independently calcualte parity of necessary moves of each checker.
 That means no optimal strategy exists. The initial position determines the result.
 If sum of them is odd, first player wins. Otherwise second player wins.
 
 19:00-19:11 add greedy solution
 
 Summary:
  - Very straightforward game DP
  - I didn't come up with greedy at all
  - After knowing that there is a greedy strategy, I found it by myself 👍
 
 */

class EllysCheckers {
public:
  string yes="YES",no="NO";
  string getWinner(string B) {
    int N=SZ(B);
    int sum=0;
    REP(i,N) if(B[i]=='o') sum+=N-1-i;
    return sum%2==1?yes:no;
  }
};

// Grundy number, O(N*2^N) time
int G[1<<20];
class EllysCheckers_grundy {
public:
  string yes="YES",no="NO";
  int N;
  int f(int mask) {
    int &res=G[mask];
    if(res>=0) return res;
    if(mask&(1<<(N-1))) mask^=1<<(N-1);
    if(mask==0) return res=0;
    
    SETI GG;
    REP(i,N-1) if((mask>>i)&1) {
      if((mask&(1<<(i+1)))==0) {
        int mask2=mask;
        mask2^=1<<i;
        mask2^=1<<(i+1);
        GG.emplace(f(mask2));
      }
      if(i<N-3&&(mask&(1<<(i+3)))==0) {
        int mask2=mask;
        mask2^=1<<i;
        mask2^=1<<(i+3);
        GG.emplace(f(mask2));
      }
    }
    
    res=0;
    while(GG.count(res)) ++res;
    return res;
  }
  string getWinner(string B) {
    this->N=SZ(B);
    MINUS(G);
    int mask=0;
    REP(i,N) if(B[i]=='o') mask|=1<<i;
    return f(mask)==0?no:yes;
  }
};

// game turn DP, O(N*2^N) time
int memo[1<<20];
class EllysCheckers_org {
  public:
  string yes="YES",no="NO";
  int N;
  bool f(int mask) {
    int &res=memo[mask];
    if(res>=0) return res;
    res=0;
    if(mask&(1<<(N-1))) mask^=1<<(N-1);
    REP(i,N-1) if((mask>>i)&1) {
      if((mask&(1<<(i+1)))==0) {
        int mask2=mask;
        mask2^=1<<i;
        mask2^=1<<(i+1);
        res|=!f(mask2);
      }
      if(i<N-3&&(mask&(1<<(i+3)))==0) {
        int mask2=mask;
        mask2^=1<<i;
        mask2^=1<<(i+3);
        res|=!f(mask2);
      }
    }
    return res;
  }
  string getWinner(string B) {
    this->N=SZ(B);
    MINUS(memo);
    int mask=0;
    REP(i,N) if(B[i]=='o') mask|=1<<i;
    return f(mask)?yes:no;
  }
};

// CUT begin
ifstream data("EllysCheckers.sample");

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

bool do_test(string board, string __expected) {
    time_t startClock = clock();
    EllysCheckers *instance = new EllysCheckers();
    string __result = instance->getWinner(board);
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
        string board;
        from_stream(board);
        next_line();
        string __answer;
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
        int T = time(NULL) - 1518195854;
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
        cout << "EllysCheckers (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
