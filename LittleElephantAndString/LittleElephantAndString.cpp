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
 
 11/4/2017
 
 17:05-17:32 analysis
 18:05 1WA (196.87 pt)
 18:14 give up
 
 11/5/2017
 
 9:50-11:03, 12:15- read editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+597
   - brute force x steps (x=0..N) and finding suffix in greedy manner
  - https://twitter.com/kinaba/status/403158608910626816
   - https://community.topcoder.com/stat?c=problem_solution&rm=319316&rd=15709&pm=12854&cr=22758647
   - brute force steps
  - http://kmjp.hatenablog.jp/entry/2013/11/21/0900
   - greedy
  - http://torus711.hatenablog.com/entry/20131120/p1
   - greedy

 As shown in example 3, in worst case we can keep selecting characters in B in backwards direction.

 I focused on making B's tail too much. Suppose following strings are given:
 A: ABCXY
 B: YCBAX
 
 I tried to move B first to make A and B in ?????X form like...
 A: YABCX
 B: YCBAX
 
 However this strategy has NO optimality because we need to move Y twice.
 A: YABCX->AYBCX->BAYCX->CBAYX->YCBAX (second move of Y)
 This would violate analysis that we can move each character at most once.
 
 Rather than that, we should rearrange ABC to CBA first. After that we can move Y.
 Thus my original strategy does not solve problem.
 I should have figured out it quickly in analysis process.
 
 However focusing tail of B is correct. Let's look at example above again.
 A: ABCXY
     ^^ ^
 B: YCBAX
 
 In order to build B, we find out that we need to anyway move Y, B and C.
 Also we can choose arbitrary order. In this case C->B->Y is optimal.
 That means we can go through B from tail to front.
 Suppose A[i]=B[j] and A[i-x]=B[j-1]. Then we need to move A[i-x+1..i-1].
 Result is number of elements which is being moved.
 
 Key:
  - We can make B in at most |B| turns
  - Arbitrary order to move is possible. So count number of elements which MUST be moved in A
 
 Summary:
  - This problem was tough for me in analysis perspective
  - Always prove OPTIMALITY in analysis process
   - Estimating upperbound of problem's answer sometimes help it
 
 */
class LittleElephantAndString {
public:
  int getNumber(string A, string B) {
    string AA=A,BB=B;
    sort(AA.begin(),AA.end());
    sort(BB.begin(),BB.end());
    if(AA!=BB) return -1;
    int N=SZ(A);
    int j=N-1;
    int res=0;
    for(int i=N-1; i>=0; --i) {
      if(A[i]==B[j]) --j;
      else ++res;
    }
    return res;
  }
};


class LittleElephantAndString_wrong {
  public:
  int f(string A, string B) {
//    dump2(A,B);
//    dump2(SZ(A),SZ(B));
//    assert(SZ(A)==SZ(B));
    int N=SZ(A);
    if(N==0) return 0;
    int l=-1;
    for(int i=N-1; i>=0; --i) {
      if(A[i]==B[N-1]) {
        l=i;
        break;
      }
    }
//    dump2(l,N-l-1);
    if(l==-1) return -1;
    VI viz(N,0);
    string AA="";
    for(int j=N-1; j>=0; --j) {
      FOR(i,l+1,N) if(!viz[i]&&A[i]==B[j]) {
        viz[i]=true;
        AA.push_back(B[j]);
        break;
      }
    }
    
//    dump(accumulate(viz.begin(),viz.end(),0));
//    if(accumulate(viz.begin(),viz.end(),0)<N-l-1) return -1;
    reverse(AA.begin(),AA.end());
    int x=f(AA+A.substr(0,l), B.substr(0,N-1));
    return x==-1?-1:x+N-l-1;
  }
  int getNumber(string A, string B) {
    return f(A,B);
  }
};

// CUT begin
ifstream data("LittleElephantAndString.sample");

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

bool do_test(string A, string B, int __expected) {
    time_t startClock = clock();
    LittleElephantAndString *instance = new LittleElephantAndString();
    int __result = instance->getNumber(A, B);
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
        string A;
        from_stream(A);
        string B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509840323;
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
        cout << "LittleElephantAndString (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
