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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/14/2018
 
 15:42-16:07 submit and 1WA due to missing condition (158.11 pt)
 17:35-17:36 fixed and ACC
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+549
  - https://topcoder.g.hatena.ne.jp/hotoku/20120709/1341844306
   - dp
  - http://topcoder.g.hatena.ne.jp/agw/20120716/1342405574
  - http://kg86.hatenablog.com/entry/2014/08/31/184024
 
 24:00-24:15 add DP solution
 
 Summary:
  - I missed below problem statement 👎
  > Also, note that the total number of swaps in the game may be larger than numSwaps, because the magician may sometimes swap two hats that don't contain the ball.
 
 */
double P[3][1010];
class BallAndHats {
public:
  int getHat(string X, int M) {
    ZERO(P);
    int x=-1;
    REP(i,3) if(X[i]=='o') x=i;
    P[x][0]=1.0;
    
    for(int i = 1; i <= M; ++i){
      P[0][i] = 0.5*P[1][i-1];
      P[1][i] = P[0][i-1] + P[2][i-1];
      P[2][i] = 0.5*P[1][i-1];
    }
    dump3(P[0][M],P[1][M],P[2][M]);
    int res=0;
    REP(i,3) if(P[i][M]>P[res][M]) res=i;
    return res;
  }
};

class BallAndHats_org {
  public:
  int getHat(string X, int M) {
    int x=-1;
    REP(i,3) if(X[i]=='o') x=i;
    if(M==0) return x;
    if(x==1&&M%2==0) return 1;
    if((x==0||x==2)&&M%2==1) return 1; // I forgot to add x==2 in the first submission
    return 0;
  }
};

// CUT begin
ifstream data("BallAndHats.sample");

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

bool do_test(string hats, int numSwaps, int __expected) {
    time_t startClock = clock();
    BallAndHats *instance = new BallAndHats();
    int __result = instance->getHat(hats, numSwaps);
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
        string hats;
        from_stream(hats);
        int numSwaps;
        from_stream(numSwaps);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(hats, numSwaps, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515973354;
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
        cout << "BallAndHats (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
