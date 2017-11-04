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
 
 11/3/2017
 
 9:12-10:09 system test passed (400.97 pt)
 
 Proof of greedy:

 Lemma 1: smaller maximum move cannot win larger move (except first move)
 
 Suppose we have m1 and m2 (m1<m2) for maximum move without loosing generality.
 Also position of player 1 and player 2 is x1 and x2.
 A safe and closest position for player 1 is x2-m2-1.
 x1 = x2-m2-1, x2 = x2
 In one step, player 1 cannot reach player 2's position.
 Also player 2 can keep going further to playe 1.
 Thus obviously player 1 cannot win player 2.
 
 Lemma 2: player with larger maximum move can win opponent if it's move is more than opponent's maximum move.
 
 Suppose we have m1 and m2 (m1<=m2) for maximum move without loosing generality.
 Larger move has more advantage. We think player 2 always follows player 1 to capture.

 Suppose position of player 1 and player 2 is x1 and x2.
 A safe and closest position for player 2 is x1+m1+1.
 
 x1 = x1, x2 = x1+m1+1
 
 Player 1 is going away from player 2. In next iteration player 1's position x1' would be x1-m1.
 If x2 can canpture x1 in this step, x2-m2<=x1' should hold.
 
     x2-m2<=x1'
 <=> (x1+m1+1)-m2<=x1-m1
 <=> 2*m1 <= m2-1 < m2
 =>  2*m1 < m2
 
 So as long as 2*m1 < m2 is satisfied, player 2 (larger move) wins.
 Otherwise player 2 cannot be closer than x1+m1+1. Thus draw happens.
 
 From lemma 1 and lemma 2, either player wins if larger maximum move is more than twice except start of the game.
 
 Only corner case is start of the game.
 If Ciel can reach Liss in one step, Ciel wins regardless of m2.
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+598
  - http://kmjp.hatenablog.jp/entry/2013/12/01/0930
  - http://mayokoex.hatenablog.com/entry/2016/02/03/204514
  - http://emkcsharp.hatenablog.com/entry/SRM598/FoxAndFencingEasy
 
 Key:
  - First position of Liss affects result only when Ciel can reach Liss in one step
  - Otherwise, result is determined only by maximum moves
 
 Summary:
  - Honestly I didn't have idea of greedy without looking at submit rate in the contest
  - I was in stuck how to design state and representing value for "draw"
  - I should have changed mind of DP if it's tough to build recurrence relation
    - It's ok to go back and forth. Branch pruning in analysis is also important
 
 */
class FoxAndFencingEasy {
  public:
  string p1= "Ciel",p2="Liss",draw="Draw";
  string WhoCanWin(int m1, int m2, int d) {
    if(m1>=d) return p1;
    if(m1>m2*2) return p1;
    if(m2>m1*2) return p2;
    return draw;
  }
};

// CUT begin
ifstream data("FoxAndFencingEasy.sample");

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

bool do_test(int mov1, int mov2, int d, string __expected) {
    time_t startClock = clock();
    FoxAndFencingEasy *instance = new FoxAndFencingEasy();
    string __result = instance->WhoCanWin(mov1, mov2, d);
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
        int mov1;
        from_stream(mov1);
        int mov2;
        from_stream(mov2);
        int d;
        from_stream(d);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(mov1, mov2, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509725519;
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
        cout << "FoxAndFencingEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
