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
 
 11/10/2017
 
 8:45-9:40,9:50-9:55 pause
 10:00-10:12 analysis
 10:24-10:46 a little bit TLE (2.44 sec)...
 It turned out that runtime of my algorithm is O(N^3*D) ≈8*10^9 rather than O(N^2*D)...
 
 17:45-18:10 accepted
 
 Define S = { i : kid `i` is in team 1 } and f(S) = ∑ { s[i] : i ∈ S }
 Problem statement is asking to satisfy...
 f(S) > f(U-S) AND f(S)-x<f(U-S)+ min { s[i] : i ∈ S }
 
 If tot = ∑ { s[i] : i=0..N-1 }..
  f(U-S) = tot - f(S)

 f(S) > f(U-S) AND f(s)-x<f(U-S)+x
 => f(S)>tot-f(S), f(s)-x<tot-f(S)+x
 => 0 < 2*f(S)-tot < 2*min { s[i] : i ∈ S }
 
 Solving subset sum along with index of minimum value is O(N^3*D) time ≈8*10^9
 min { s[i] : i ∈ S } is not easy to handle.
 However if we sort `s`, we can easily divide to subproblems with minimum value x in S.
 Let's define sub problem P1(i,sum): computing number of S when sum=∑ s[j] : j=i..N-1 }
 ∑ { T(P1(i,k) : k=0..N*D } = O(N^2*D)
 Just solving P1(i,k) for each i (i=0..N-1) is not still sufficient as below:
 T(P) = ∑ { T(P1(i,k)) : i=0..N-1,k=0..N*D } = O(N^3*D)
 
 This problem can be solved by finding recurrence relation between P1(i,sum+s[i]) and P1(i+1,sum) as shown in editorial.
 P1(i,sum+s[i])+=P1(i+1,sum)
 We can iterate i in order N-1..0. Then at each `i`, s[i] is guaranteed to be minimum.
 Thus if f(S)=sum+s[i] satisfies 0<(2*sum+s[i])-tot<2*s[i], res+=P1(i+1,sum)

 Eventually T(P) = O(N^2*D)
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+591
  - http://kmjp.hatenablog.jp/entry/2013/09/22/1000
  - http://emkcsharp.hatenablog.com/entry/SRM591/YetAnotherTwoTeamsProblem

 Summary:
  - I made a mistake in Back-of-the-envelope calculation of running time analysis 👎
  - Basic process of analysis was close. However I could not checkmate in the last step 😂
 
 */
const int Inf=50*60000;
LL dp[Inf+1];
class YetAnotherTwoTeamsProblem {
public:
  long long count(vector<int> s) {
    int N=SZ(s);
    ZERO(dp);

    sort(s.begin(),s.end());
    int tot=accumulate(s.begin(),s.end(),0);
    
    LL res=0;
    dp[0]=1;
    for(int i=N-1; i>=0; --i) for(int sum=Inf; sum>=0; --sum) {
      if(sum+s[i]>Inf) continue;
      dp[sum+s[i]]+=dp[sum];
      LL a=2*(sum+s[i])-tot;
      if(0<a&&a<2LL*s[i]) res+=dp[sum];
    }
    return res;
  }
};

class YetAnotherTwoTeamsProblem_TLE {
  public:
  const int Inf=50*60000+1;
  long long count(vector<int> s) {
    int N=SZ(s);
    sort(s.begin(),s.end());
    int tot=accumulate(s.begin(),s.end(),0);
    LL res=0;
    REP(i,N) {
      ZERO(dp);
      dp[s[i]]=1;
      FOR(j,i+1,N) for(int sum=Inf-1; sum>=0; --sum) if(sum+s[j]<Inf) {
        dp[sum+s[j]]+=dp[sum];
      }
      REP(sum,Inf+1) if(dp[sum]>0) {
        int a=2*sum-tot;
        if(a>0&&a<2*s[i]) res+=dp[sum];
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("YetAnotherTwoTeamsProblem.sample");

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

bool do_test(vector<int> skill, long long __expected) {
    time_t startClock = clock();
    YetAnotherTwoTeamsProblem *instance = new YetAnotherTwoTeamsProblem();
    long long __result = instance->count(skill);
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
        vector<int> skill;
        from_stream(skill);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(skill, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510332294;
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
        cout << "YetAnotherTwoTeamsProblem (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
