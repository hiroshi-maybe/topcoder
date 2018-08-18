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
 
 8/15/2018 SRM 736
 
 8:32-9:00 give up
 
 8/18/2018
 
 13:40-14:40 read editorials
 
 Editorials:
  - http://kmjp.hatenablog.jp/entry/2018/08/16/0930
 
 Tweets:
  - https://togetter.com/li/1257026
  - https://twitter.com/HIR180/status/1029769285202149376
  - https://twitter.com/natsugir/status/1029769715839684608
  - https://twitter.com/snuke_/status/1029769763566710784
  - https://twitter.com/yosupot/status/1029768860696629248
  - https://twitter.com/beet_aizu/status/1029768470102126592
  - https://twitter.com/natsugir/status/1029769715839684608

 Very clean implementation by rng_58
  - http://community.topcoder.com/stat?c=problem_solution&rm=331581&rd=17242&pm=14951&cr=22692969

 i) K=0
 
 -> ALL
 
 Singe vertex holds 0-dense
 
 ii) N<K+1 or M<K*(K+1)/2

 -> NONE
 
 K+1 perfect graph forms K-dense. Below condition is needed to form K+1 perfect graph:
  - at least K+1 nodes
  - at least K*(K+1)/2 edges
 
 iii) K-dense exists
 
 K-perfect graph (G1): K*(K-1)/2 edges, K vertices
 Others (G2): N-K vertices
 
 N-K vertices in G2 should not have K degrees. Thus total # of edges <= (N-K)*(K-1)
 
 a) M <= edges(G1)+edges(max{G2}) = K*(K-1)/2 + (N-K)*(K-1)
 
 -> SOME
 
 b) otherwise
 
 -> ALL
 
 Summary:
  - Hard math
 
 */

const string all="ALL",some="SOME",none="NONE";
class MinDegreeSubgraph {
  public:
  string exists(int N, long long M, int K) {
    if(K==0) return all;
    if(N<K+1) return none;
    if(M<1LL*K*(K+1)/2) return none;
    
    LL x=1LL*K*(K-1)/2+(1LL*N-K)*(K-1);
    return M<=x?some:all;
  }
};

// CUT begin
ifstream data("MinDegreeSubgraph.sample");

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

bool do_test(int n, long long m, int k, string __expected) {
    time_t startClock = clock();
    MinDegreeSubgraph *instance = new MinDegreeSubgraph();
    string __result = instance->exists(n, m, k);
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
        long long m;
        from_stream(m);
        int k;
        from_stream(k);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1534347168;
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
        cout << "MinDegreeSubgraph (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
