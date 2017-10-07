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
 
 10/6/2017
 
 9:43-10:43 give up
 
 17:20-17:40 read editorials:
  - http://kmjp.hatenablog.jp/entry/2014/05/05/1230
  - https://apps.topcoder.com/wiki/display/tc/SRM+619
 
 17:41-17:44 add solution
 
 if we don't hire anyone, we start from negative balance (debt): ∑{-E(i,j) : i<j }
 analyze what happens if we hire people....
 
 look at two employees i and j. there are 4 cases by hiring/skipping them.

 (i,j) -> profit (o: hire, x: skip)
 
 (x,x) -> +        0
 (o,x) -> +   E(i,j)
 (x,o) -> +   E(i,j)
 (o,o) -> + 2*E(i,j)

 thus whenever we hire person `i`, we get E(i,j) profit regardless of hiring state of other people.
 when hiring person i, it costs C(i).
 If profit P(i) by hiring person i dominates its cost, we can hire him/her greedily.
 => If B(i)=P(i)-C(i) > 0, res += B(i), P(i) = ∑ { E(i,j) : j=0..<N }
 => res = ∑ { max(B(i),0) : i=0..<N }
 
 key:
  - translate problem into N independent subproblem
   - start from debt. prof = -E(i,j) (i<j)
   - if we hire person i, we'll earn + ∑{E(i,j)} - V(i) from debt state regardless of hiring of other people
     - if ∑{E(i,j)} - V(i) > 0, we can hire person i greedily
 
 summary:
  - I tried some approaches though, no luck 👎
  - It turned out #3 is expected solution.
    1. translate to graph problem
    2. build recurrence relation for DP though
    3. translate problem into some easier problem leveraging earning(i,j) statement
  - possible process to come up with this greedy idea
   - probably I should have focused on initial state. then we start from debt.
   - analyze how states change if we hire people
   - from initial state, we can figure out that we can independently add profit E(i,j) due to statement of profit condition of {-E(i,j),0,+E(i,j)}
 
 */
class EmployManager {
  public:
  int maximumEarnings(vector<int> C, vector<string> E) {
    int N=SZ(C);
    int res=0;
    REP(j,N) REP(i,j) res-=E[i][j]-'0';
    REP(i,N) {
      int dif=-C[i];
      REP(j,N) dif+=E[i][j]-'0';
      if(dif>0) res+=dif;
    }
    return res;
  }
};

// CUT begin
ifstream data("EmployManager.sample");

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

bool do_test(vector<int> value, vector<string> earning, int __expected) {
    time_t startClock = clock();
    EmployManager *instance = new EmployManager();
    int __result = instance->maximumEarnings(value, earning);
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
        vector<int> value;
        from_stream(value);
        vector<string> earning;
        from_stream(earning);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(value, earning, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507308175;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "EmployManager (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
