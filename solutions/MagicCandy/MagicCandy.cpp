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
 
 2/23/2018
 
 8:30-9:01 analysis
 9:02-9:06 ACC after 1WA for n=2 (254.38 pt)
 
 In every iteration, floor(√x) numbers are removed until `x` gets `1`.
 It's possible to compute how many steps are needed in O(√N).
 I looked at the final state. If operation goes backward, below recurrence relation is obtained:
 
 x[0] = 1
 x[i] = x[i+1] - floor(√x[i+1])
 
 f(x) = x - √x is monotonically increasing function.
 It's possible to find x[i+1] by binary search in O(lg N).
 We can follow above recurrence relation in steps that we obtained in the first step.
 
 Editorial:
  - official
   - https://apps.topcoder.com/wiki/display/tc/SRM+526.5
  - cycle
   - http://isarentacs.hatenablog.com/entry/20111224/1324741844
   - http://d.hatena.ne.jp/simezi_tan/touch/20111231/1325310750
  - N - number of times that last is removed
   - http://rsujskf.blog32.fc2.com/blog-entry-2190.html
   - https://topcoder.g.hatena.ne.jp/firewood/20120106/1325873167
  - greedy + binary search
   - https://chngng.blogspot.com/2015/05/srm-5265-div1-easy-magiccandy.html
 
 Summary:
  - Analysis to focus on final state and go backward worked
  - Finding value with binary search is cool
 
 10/22/2018
 
 Very disappointing that I cannot solve now even though I solved by myself before. Even keeping in mind to solve in backward suggested in "How to solve it" 😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞😡😞
 
 Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known? Look at unknown. What is derived if unknown is known?
 
 Data: # of candies
 Condition: Candy whose label is x^2 is removed and new labels are assigned until only one element remains
 Unknown: original label
 
 Find the connection between the data and the unknown
  => We can connect unknown to the data by keep finding original label in the previous state
 You may be obliged to consider auxiliary problems if an immediate connection cannot be found
  => Finding previous label before removal happens need to be solved. This is auxiliary problem
 Have you seen it before?
  => I have even solved this problem by myself
 Have you seen the same problem in a slightly diffferent form?
  => I have solved this problem by myself
 Do you know a related problem?
  => I have solved this problem by myself
 Look at the unknown! And try to think of a familiar problem having the same or a similar unknown
 Could you restate the problem?
  => I should have restated to a problem to unwinding labels
 Go back to definitions
  => Definition of the operation is suggesting that next position can be found by x-sqrt(x)
 Could you solve a part of the problem? Keep only a part of the condition, drop the other part
  => This may not be necessary in this problem
 Could you derive something useful from the data?
  => I cannot in this problem
 Could you change the unknown or the data, or both if necessary, so that the new unknown and the new data are nearer to each other?
  => If I can find the label of previous state, I can be CLEARLY nearer to unknown
 
 */
class MagicCandy {
  public:
  int f(int a) {
    int good=a+1,bad=1e9+10;
    while(abs(good-bad)>1) {
      int mid=(good+bad)/2;
      if(mid-(int)floor(sqrt(mid))<=a-1) good=mid;
      else bad=mid;
    }
    return good+1;
  }
  int whichOne(int n) {
    if(n==1) return 1;
    if(n==2) return 2;
    n-=(int)floor(sqrt(n));
    int cnt=0;
    int a=1;
    while(n>1) {
      n-=(int)floor(sqrt(n));
      ++cnt;
      a=f(a);
    }
//    dump(cnt);
    return a;
  }
};

// CUT begin
ifstream data("MagicCandy.sample");

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

bool do_test(int n, int __expected) {
    time_t startClock = clock();
    MagicCandy *instance = new MagicCandy();
    int __result = instance->whichOne(n);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519403407;
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
        cout << "MagicCandy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
