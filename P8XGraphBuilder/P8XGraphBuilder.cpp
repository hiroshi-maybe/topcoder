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
 
 2/22/2018
 
 8:40-8:54 analysis
 8:55-9:20 implement, bug fix and submit (245.16 pt)
 
 We need to build connected tree where there are N-1 edges.
 Thus there are total 2*(N-1) degrees.
 Each node should have at least one edge.
 We can subtract them first.
 Now we want to maximize score by assigning N-2 (=2*(N-1)-N) degrees.
 This is knapsack problem. DP works.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+527
  - http://www.vexorian.com/2011/12/srm-527-slooow.html
  - https://chngng.blogspot.com/2015/05/srm-527-div1-easy-p8xgraphbuilder.html
  - https://topcoder.g.hatena.ne.jp/jackpersel/20111222/1324570811
  - http://d.hatena.ne.jp/simezi_tan/20111219/1324303962
  - http://mayokoex.hatenablog.com/entry/2015/12/21/000833
  - http://kg86.hatenablog.com/entry/20130406/1365235758
  - http://purple-jwl.hatenablog.com/entry/20121022/1350911444
  - http://d.hatena.ne.jp/kusano_prog/20111217/1324152151

 It's not obvious that we can build a tree with arbitrary degrees.
 Official editorial has the proof of it.
 
 Summary:
  - interesting problem to reduce to knapsack problem
  - Only 68 people solved this problem during the contest
  - Some mistakes after analysis
   - I was confused N (number of vertices) with length of S 👎
   - Confused with dp of subset sum 👎👎
   - Mistakenly dp table was being initiated with zero 👎👎👎👎
 
 */

// dp, O(N^3) time
int dp[51][51];
class P8XGraphBuilder {
  public:
  int solve(vector<int> S) {
    int N=SZ(S)+1;
    MINUS(dp); // ZERO(dp) does not work. Initiate with -Inf works as well.
    dp[0][0]=0;
    REP(i,N) REPE(d,N) if(dp[i][d]>=0) REP(x,N-1) if(d+x<N) {
      SMAX(dp[i+1][d+x],dp[i][d]+S[x]);
    }
//    dump3(N,N-2,dp[N][N-2]);
    return dp[N][N-2];
  }
};

// CUT begin
ifstream data("P8XGraphBuilder.sample");

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

bool do_test(vector<int> scores, int __expected) {
    time_t startClock = clock();
    P8XGraphBuilder *instance = new P8XGraphBuilder();
    int __result = instance->solve(scores);
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
        vector<int> scores;
        from_stream(scores);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(scores, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519317624;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "P8XGraphBuilder (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
