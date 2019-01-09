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
 
 1/7/2018
 
 10:43-11:23 pause
 12:15-12:29 analysis
 12:29-12:35 implement and submit. but 1WA for "10"
 12:35-12:40 fixed a bug and system test passed.
 
 f(i,l) = min(S[N-i-1]+f(i+1,l+1), f(i+1,l)+S[N-i-1))
 // ⚠️ note that '0' cannot be head of result
 f(N,_) = ""
 
 res=f(0,0)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+556
   - Interesting. There is a greedy solution.
  - http://d.hatena.ne.jp/kusano_prog/20120914/1347595939
   - dp
 
 Greedy solution in official editorial is interesting.
 There are two constraints that we should satisfy:
  1. '0' cannot be head
  2. Keep prepending or appending digits
 
 DP solution is keeping #2 and checking if #1 is not violated.
 However greedy solution first ensures #1 and build result greedily.
 
 If a=S[i] is head of the result.
 Following digits must be appended to the tail. Thus result string should be as below:
 
  res = a + A + B, A ∈ { S[0],..,S[i-1] }, B ∈ { S[i+1],..,S[N-1] }
 
 It's possible to build A and B separatedly in greedy manner as well.
 Suppose we currently have string `S` and putting a.
 
 There are two choices to put a
 1) S + a
 2) a + S
 
 Without looking at following string, we can make an optimal choice.
 Just take min(S+a, a+S)
 We can apply this algorithm to both S[0..i-1] and S[i+1..N-1].
 
 Key:
  - The last digit must be located at head or tail
  - Keep putting digits backward to keep optimal substructure
 
 Summary:
  - If going-forward doesn't work, going-backward sometimes works
  - I should have tried different approach earlier
 
 */

// O(N^3) time
string memo[51][51];
class LeftRightDigitsGame {
  public:
  int N;
  string S;
  string f(int i, int l) {
    string &res=memo[i][l];
    if(res!="#") return res;
    if(i==N) return res="";
    
    char c=S[N-i-1];
    string a=c+f(i+1,l+1),b=f(i+1,l)+c;
    if(l==0&&c=='0') a="~";
    if(l==0&&i==N-1&&c=='0') b="~";
    return res=min(a,b);
  }
  string minNumber(string A) {
    this->N=SZ(A),this->S=A;
    REP(i,N+1) REP(j,N+1) memo[i][j]="#";
    return f(0,0);
  }
};

// CUT begin
ifstream data("LeftRightDigitsGame.sample");

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

bool do_test(string digits, string __expected) {
    time_t startClock = clock();
    LeftRightDigitsGame *instance = new LeftRightDigitsGame();
    string __result = instance->minNumber(digits);
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
        string digits;
        from_stream(digits);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(digits, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515350603;
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
        cout << "LeftRightDigitsGame (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
