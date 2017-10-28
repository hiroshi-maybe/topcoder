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
 
 8:37-8:48 understand problem
 8:48-9:22 implement
 9:22-9:26 debug (216.82 pt)
 
 Editorials:
  - simple O(N^5) solution
   - https://apps.topcoder.com/wiki/display/tc/SRM+605
   - http://torus711.hatenablog.com/entry/20140121/p2
  - O(N^4) solution with DP
   - http://kmjp.hatenablog.jp/entry/2014/01/22/0930
 
 Key:
  - pre-counting number of same cells in DP is best practice in grid area problem
  - problem of sum can be often reduced to subtraction like 2d cumulative sum
 
 Summary:
  - too slow to implement incremental area update
  - similar approach as TheMatrix in SRM 610 div2 medium works though, it didn't come up with me
  - solving by width and height may be a good practice to solve grid area problem
 
 Submit solutions in contest
  - clean O(N^4) solution
   - https://community.topcoder.com/stat?c=problem_solution&rm=320283&rd=15838&pm=12821&cr=23133613
   - https://community.topcoder.com/stat?c=problem_solution&rm=320286&rd=15838&pm=12821&cr=22877671
   - https://community.topcoder.com/stat?c=problem_solution&rm=320303&rd=15838&pm=12821&cr=23031909
 
 Algorithm to compute in O(R*C) time
  http://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/
 
 */

int cum[51][51];
class AlienAndGame {
public:
  int getNumber(vector<string> B) {
    int R=SZ(B),C=SZ(B[0]);
    ZERO(cum);
    REP(i,R) {
      cum[i][0]=1;
      FOR(j,1,C) {
        if(B[i][j-1]==B[i][j]) cum[i][j]=cum[i][j-1]+1;
        else cum[i][j]=1;
      }
    }
    
    int res=1;
    REP(r,R)REP(c,C) for(int w=1; r+w<=R&&c+w<=C; ++w) {
      int ok=true;
      REP(i,w) if(cum[r+i][c+w-1]<w) ok=false;
      if(ok) res=max(res,w*w);
    }
    return res;
  }
};

// O(N^4) time
class AlienAndGame_org {
  public:
  int getNumber(vector<string> board) {
    int R=SZ(board),C=SZ(board[0]);
    vector<vector<int>> B(R,VI(C,0));
    REP(i,R)REP(j,C) B[i][j]=board[i][j]=='W';
    
    int res=1;
    REP(r,R) REP(c,C) {
      int N=min(R-r,C-c);
//      dump3(r,c,N);
      vector<int> ff(N,0);
      REP(l,N) ff[l]=1^B[r+l][c];
//      dumpAR(ff);
      int area=0;
      REP(l,N) {
        REP(j,l) area+=ff[l]?(1^B[r+l][c+j]):B[r+l][c+j];
        REP(i,l+1) area+=ff[i]?(1^B[r+i][c+l]):B[r+i][c+l];
//        dump4(r,c,l,area);
        if(area!=(l+1)*(l+1)) break;
        res=max(res,(l+1)*(l+1));
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("AlienAndGame.sample");

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
    AlienAndGame *instance = new AlienAndGame();
    int __result = instance->getNumber(board);
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
        int T = time(NULL) - 1509118647;
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
        cout << "AlienAndGame (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
