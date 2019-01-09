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
 
 12/14/2017
 
 8:39-8:56 analysis
 8:57-9:40 submit (192.46 pt)
 
 12/17/2017
 
 Read editorial and add simpler solution
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+572
  - http://kmjp.hatenablog.jp/entry/2013/03/13/1100
  - http://d.hatena.ne.jp/kusano_prog/20130307/1362679444
  - http://pushl.hatenablog.com/entry/2013/03/06/231720
 
 Solution in simple intersection logic
 - https://community.topcoder.com/stat?c=problem_solution&rm=316517&rd=15492&pm=12454&cr=23141403
 
 Two approaches:
  1. classify by direction and intervals (my solution and official editorial's first solution)
  2. figure out that A[i]-B[i] and A[j]-B[j] (i!=j) never intersections
 
 Key:
  - catch invalid cases by finding intersection or one path is between another in even same direction
  - figure out simple intersection condition
 
 Summary:
  - Analysis was not so hard though, detecting invalid case with simple condition was tough
  - It may have been easier to review conditions formally? 🤔
 - Approach #2 is cool. Once I find out it, I cannot understand why I could not come up with it 😄
  - Another step of abstraction from approach #1 may have helped
  - Or writing arrow from horizontal segments of A to the one of B may have helped
 
 */

class NextOrPrev {
public:
  int getMinimum(int next, int pre, string A, string B) {
    int N=SZ(A),res=0;
    REP(j,N)REP(i,j) {
      if(A[i]<A[j]&&B[i]>B[j]) return -1;
      if(A[i]>A[j]&&B[i]<B[j]) return -1;
    }
    REP(i,N) {
      //      dump2(A[i]-'a',B[i]-'a');
      res+=(A[i]-B[i]<0?next:pre)*abs(A[i]-B[i]);
    }
    return res;
  }
};

class NextOrPrev_org {
  public:
  int getMinimum(int next, int pre, string A, string B) {
    int N=SZ(A),res=0;
    REP(j,N)REP(i,j) {
      int l1=A[i]-'a',r1=B[i]-'a',l2=A[j]-'a',r2=B[j]-'a';
      if(l1>r1) swap(l1,r1);
      if(l2>r2) swap(l2,r2);
      int l3=max(l1,l2),r3=min(r1,r2);
//      dump4(A[i],B[i],A[j],B[j]);
//      dump4(l1,r1,l2,r2);
      if(r3-l3<0) continue;
      
      l1=A[i]-'a',r1=B[i]-'a',l2=A[j]-'a',r2=B[j]-'a';
      if(l1<l2&&l2<=r1&&r1<r2) continue;
      if(l2<l1&&l1<=r2&&r2<r1) continue;
      if(l1>l2&&l2>=r1&&r1>r2) continue;
      if(l2>l1&&l1>=r2&&r2>r1) continue;
      return -1;
    }
    REP(i,N) {
//      dump2(A[i]-'a',B[i]-'a');
      res+=(A[i]-B[i]<0?next:pre)*abs(A[i]-B[i]);
    }
    return res;
  }
};

// CUT begin
ifstream data("NextOrPrev.sample");

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

bool do_test(int nextCost, int prevCost, string start, string goal, int __expected) {
    time_t startClock = clock();
    NextOrPrev *instance = new NextOrPrev();
    int __result = instance->getMinimum(nextCost, prevCost, start, goal);
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
        int nextCost;
        from_stream(nextCost);
        int prevCost;
        from_stream(prevCost);
        string start;
        from_stream(start);
        string goal;
        from_stream(goal);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(nextCost, prevCost, start, goal, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513269535;
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
        cout << "NextOrPrev (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
