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
 
 11/18/2017 SRM 723
 
 9:11-9:32 system test passed (345.35 pt)
 
 11/29/2017
 
 Read editorial and add greedy solution
 
 Editorial and solutions:
  - http://kmjp.hatenablog.jp/entry/2017/11/21/0900
  - https://community.topcoder.com/stat?c=problem_solution&rm=330719&rd=17027&pm=14737&cr=40509829
  - https://community.topcoder.com/stat?c=problem_solution&rm=330679&rd=17027&pm=14736&cr=40020549
  - https://community.topcoder.com/stat?c=problem_solution&rm=330674&rd=17027&pm=14736&cr=22263204
 
 There is a greedy solution that is applicable to div1 easy constraint (N<=50) as well.
 
 There are 4 patterns of state of i-th bits
 
 case 1. 0,0,0
  A: 0xxx
  B: 0xxx
  C: 0xxx
 
 res[i] = 0. We can never have 1
 
 case 2. 0,0,1
  A: 1xxx
  B: 0xxx
  C: 0xxx

 res[i] = 1. We need to select A.
 
 case 3. 0,1,1
  A: 1xxx
  B: 1xxx
  C: 0xxx

 res[i] = 1. We can select A or B.
 If we select A, B[i-1..0] can be arbitrary number.
 That means all the following columns are `1`
  => res[i-1..0] = 1..1
 
 case 4. 1,1,1
  A: 1xxx
  B: 1xxx
  C: 1xxx
 
 Same as case 3.
 
 Thus we can classify i-th bit from more significant bit to less.
 If we get case 3 or 4, following less significant bits are all `1`.
 
 Summary:
  - solved by DP in the contest
  - I tried greedy by myself though, I couldn't figure out which one should be selected in case 2 or 3
   - It turned out that either one gives optimal solution 😄
   - It's interesting. We make some choice to get optimal result though, we don't need to make choice in this case.
 
 */

// 31*3 time
class TopXorerEasy {
public:
  int maximalRating(int A, int B, int C) {
    int res=0;
    for(int i=30; i>=0; --i) {
      int cnt=0;
      if((A>>i)&1) ++cnt;
      if((B>>i)&1) ++cnt;
      if((C>>i)&1) ++cnt;
      if(cnt>=2) {
        res|=(1<<(i+1))-1;
        return res;
      }
      if(cnt==1) {
        res|=1<<i;
      }
    }
    return res;
  }
};

// 31*2^6 time
int memo[32][2][2][2];
class TopXorerEasy_org {
  public:
  int A,B,C;
  int f(int i, int anya, int anyb, int anyc) {
    if(i==-1) return 0;
    int &res=memo[i][anya][anyb][anyc];
    if(res>=0) return res;
    res=0;
    int a=(A>>i)&1,b=(B>>i)&1,c=(C>>i)&1;
    REP(x,2)REP(y,2)REP(z,2) {
      bool aok=anya||x<=a,bok=anyb||y<=b,cok=anyc||z<=c;
      if(aok&&bok&&cok) {
        int xyz=(x^y)^z;
        res=max(res,(xyz<<i)|f(i-1,anya||x<a,anyb||y<b,anyc||z<c));
      }
    }
    return res;
  }
  int maximalRating(int A, int B, int C) {
    this->A=A,this->B=B,this->C=C;
    MINUS(memo);
    return f(30,0,0,0);
  }
};

// CUT begin
ifstream data("TopXorerEasy.sample");

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

bool do_test(int A, int B, int C, int __expected) {
    time_t startClock = clock();
    TopXorerEasy *instance = new TopXorerEasy();
    int __result = instance->maximalRating(A, B, C);
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        int C;
        from_stream(C);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, C, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1511025053;
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
        cout << "TopXorerEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
