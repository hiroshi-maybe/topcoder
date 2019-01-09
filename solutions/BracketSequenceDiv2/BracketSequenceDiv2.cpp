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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/28/2017
 
 9:19-9:55 time up
 
 18:00-18:35 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/04/06/0930
 - http://pekempey.hatenablog.com/entry/2016/03/29/174037
 
 Ok, there is a DP technique how to count unique subsequence of strings. Both articles are referring to related problems in AtCoder and CodeForces
 - http://tdpc.contest.atcoder.jp/tasks/tdpc_lexicographical
 - http://codeforces.com/problemset/problem/645/E
 
 18:35-19:00 understand DP to count unique subsequences
 - http://kmjp.hatenablog.jp/entry/2013/09/03/1000
 - http://garnacha.techblog.jp/archives/39854885.html
 
 DP to count unique subsequence for string `S`
 i)  if S[i]==c
    f(i,c) = 1+∑ {f(i+1,c), c∈all the characters}
 ii) if S[i]!=c
    f(i,c) = f(i+1,c)
 
 19:00-19:30 back to editorials again
 
 dp(i1,b+1) += dp(i,b), i1 is index of left-most '('
 dp(i2,b-1) += dp(i,b), i2 is index of left-most ')'
 
 19:30-19:50 add solution
 22:15-22:33 performance improvement by precomputing next position.
 
 22:35-22:34 read official editorial (same as above)
 - https://apps.topcoder.com/wiki/display/tc/SRM+686
 
 22:35- read submit solutions
 memoized recursion DP
 - https://community.topcoder.com/stat?c=problem_solution&rm=328393&rd=16690&pm=14211&cr=23302899
 - https://community.topcoder.com/stat?c=problem_solution&rm=328376&rd=16690&pm=14211&cr=23085056
 
 */

constexpr LL MOD = 1e9+7;
LL dp[101][101];
class BracketSequenceDiv2_org {
public:
  int count(string s) {
    int N=SZ(s);
    memset(dp, 0, sizeof dp);
    REP(i,N) if(s[i]=='(') {
      dp[i][1]=1;
      break;
    }
    
    REP(i,N) {
      int i1 = find(s.begin()+i+1,s.end(),'(')-s.begin();
      int i2 = find(s.begin()+i+1,s.end(),')')-s.begin();
      REP(b,N) {
        if(i1<N) (dp[i1][b+1]+=dp[i][b])%=MOD;
        if(i2<N&&b>0) (dp[i2][b-1]+=dp[i][b])%=MOD;
      }
    }
    
    LL res=0;
    REP(i,N) (res+=dp[i][0])%=MOD;
    return res;
  }
};

class BracketSequenceDiv2 {
public:
  int count(string s) {
    int N=SZ(s);
    memset(dp, 0, sizeof dp);
    REP(i,N) if(s[i]=='(') {
      dp[i][1]=1;
      break;
    }
    
    // precompute next position
    int next[1001][2];
    int is[2]={N,N};
    for(int i=N-1; i>=0; --i) {
      next[i][0]=is[0], next[i][1]=is[1];
      is[s[i]!='('] = i;
    }
    
    REP(i,N) {
      int i1=next[i][0], i2=next[i][1];
      REP(b,N) {
        if(i1<N) (dp[i1][b+1]+=dp[i][b])%=MOD;
        if(i2<N&&b>0) (dp[i2][b-1]+=dp[i][b])%=MOD;
      }
    }
    
    LL res=0;
    REP(i,N) (res+=dp[i][0])%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("BracketSequenceDiv2.sample");

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

bool do_test(string s, int __expected) {
    time_t startClock = clock();
    BracketSequenceDiv2 *instance = new BracketSequenceDiv2();
    int __result = instance->count(s);
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
        string s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501258736;
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
        cout << "BracketSequenceDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
