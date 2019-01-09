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
 
 9:07-9:55 give up
 
 10:30-11:30 read editorials
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+526.5
  - http://kmjp.hatenablog.jp/entry/2014/01/10/0900
  - http://area.hateblo.jp/entry/2013/09/28/153603
  - https://topcoder.g.hatena.ne.jp/firewood/20120106/1325873167
 
 19:00-19:30, 22:00-23:36 re-describe analysis in official editorial.
 
 This was really tough problem.
 I guessed that this is a DP problem though, I had no idea what to start with.
 What I just found is that S[i]<S[j] does not mean that S[i]S[j] is lexicographically small.
 
 There are 2^(N+1) pattens to divide string for N+1 division point.
 However exponential algorithm does not work due to constraint N<=50.
 
 We want to split given string as many times as possible.
 However if split strings can form more lexicographically smaller string, it's not valid move.
 Keep in mind that what we want now is some property that helps us decide if adding current string is valid or not.
 
 There are two things that we may need to know:
  - How to split the given string
  - How to confirm if given string is lexicographically smallest for split string
 
 Fixing some condition is a good start to find some important property.
 In this problem, we can start analysis by assuming that split strings are given.
 
 A = s[0]s[1]..s[N-1], s[i] ∈ S (split strings)
 
 Comparing strings with different length is not straightforward in this problem.
 However comparing string with the same length may be easier.
 
 If A is lexicographically smalleest for given S, s[i]s[i+1]<s[i+1]s[i] should hold.
 
 Proof:
 A  = X+s[i]s[i+1]+Y, X=s[0]..s[i-1], Y=s[i+2]..s[N-1]
 A' = X+s[i+1]s[i]+Y
 If s[i+1]s[i]<s[i]s[i+1], A>A' holds. That contradicts that A is smallest.
 
 We want to show that not only s[i]s[i+1] holds for all i, but also this relation is transitive.
 ok(s[i],s[i+1]) and ok(s[j],s[j+1]) where i<j <=> ok(s[i],s[j])
 
 The reason why transitivity is benefitial is that we don't need to check this property for all the preceding strings s[i] i=0..j-1.
 Suppose transitivity is proved. If so, we can build following solution works.
 
 A[0..j]=A[0..i]+A[i+1..j], j<N
 Let's find `k` which gives "good" split of `A` which satisfies A[k..i]A[i+1..j]<A[i+1..j]A[k..i] <=> ok(A[k..i],A[i+1..j])
 If ok(A[k..i],A[i+1..j]) holds, we are sure that A[i+1..j] is a good split to form lexicographically minimal.
 dp[i][j] = max(_, dp[k][i]+1)
 
 We are sure that this solution works if transitvity is proved.
 
 Proof:
 
 Let's map string to integer to show property of total order by homomorphism function.
 
 Define function `f` which maps string into integer
 f(s) = ∑ { c*26^i : i=0..|s| }

 Suppose we have x="abc" and y="defg".
 Then ok(x,y) <=> f(x+y) <= f(y+x)
 
 f(x+y) = f(x)*26^|y| + f(y)
 f(y+x) = f(y)*26^|x| + f(x)
 
     f(x+y)<=f(y+x)
 <=> f(x)*(26^|x|-1) <= f(y)*(26^|y|-1)
 
 Define h(x) = f(x)*(26^|x|-1)
 Then h(x) is a homomorphism function.
 
 Homomorphism function:
  - https://en.wikipedia.org/wiki/Homomorphism
 
 We can define total order for binary relation ok(x,y).
 That shows ∀i, ok(s[i],s[i+1]) => ok(s[i],s[j]) where i<=j
 This property is obtained by map from real number of h(x)
 
 Thus comparation of only last two strings shows lexicographically smallest string.
 
 23:37-23:50 implement and ACC
 
 Summary:
  - Very hard to find transitivity of lexicographically minimal string property by myself without any clue
  - However inferring preferred property from technique like greedy or dp... may be helpful. This can be a clue.
  - Preferred process to solve this problem:
   - I wish I could solve this problem by DP
   - We want to know if A[i..j] can be valid split to fill dp[i][j]
   - We know answer of dp[k][i]. If it's possible to validate A[k..i-1] with A[i..j], we can make recurrence relation in a form of dp[i][j] = f(dp[k][i])
   - This can be a good start to seek for some nice property which solves a problem
   - Ok. Let's analyze relation between two last strings more deeply so that `A` forms lexicographically smallest string
  - We may be able to guess property from technique and size constraint as shown in above preferred process
   - If it's dp and N=50, O(N^4) is maximum runtime
   - There should be something which helps us solve this problem by remembering only N^2 or N^3 states
  - If such property was not found, my analysis is not deep enough or different technique can be applicable

 */

int dp[51][51];
class MagicNaming {
  public:
  const int Inf=1e3;
  int maxReindeers(string A) {
    ZERO(dp);
    int N=SZ(A);
    REP(i,N) dp[0][i]=1;
    FOR(i,1,N) FORE(j,i+1,N) {
      dp[i][j]=-Inf;
      REP(k,i) {
        string x=A.substr(k,i-k);
        string y=A.substr(i,j-i);
        if(x+y<=y+x) SMAX(dp[i][j],dp[k][i]+1);
      }
    }
    int res=1;
    REP(i,N) SMAX(res,dp[i][N]);
    return res;
  }
};

// CUT begin
ifstream data("MagicNaming.sample");

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

bool do_test(string magicName, int __expected) {
    time_t startClock = clock();
    MagicNaming *instance = new MagicNaming();
    int __result = instance->maxReindeers(magicName);
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
        string magicName;
        from_stream(magicName);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(magicName, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519405638;
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
        cout << "MagicNaming (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
