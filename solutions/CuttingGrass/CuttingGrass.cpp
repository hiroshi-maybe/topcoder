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
 
 3/5/2018
 
 15:43-16:21 pause
 18:20-18:35 analysis
 18:36-19:00 I tried greedy without proof though, id didn't pass. give up
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+517
  - http://d.hatena.ne.jp/kusano_prog/20110912/1315855524
  - http://area.hateblo.jp/entry/2013/09/03/024333
  - https://topcoder.g.hatena.ne.jp/firewood/20111015/1318653741
  - http://kmjp.hatenablog.jp/entry/2014/01/16/0900
 
 21:10-22:27 read editorials
 22:40-23:09 implement and ACC
 
 1. Cutting same grass twice is not better choice
 
 Suppose I[i] = 0 for i=0..N-1.
 If we cannot get sum of height H for this state,
 We never have chance to get H.
 
 Cutting all the grasses gives same base line as above.
 So we can cut each grass at most once.
 
 2. Cutting in ascendent order of grouth is optimal
 
 We are cutting i and j at t=t1 and t=t2 respectively where t1<t2
 Suppose D[i]>D[j] gives optimal result to show contradiction.
 
 at t=t2, we are getting height h = h(t=t1)+(t2-t1)*D[i].
 However if we cut D[j] at t=t1, h' = h(t=t1)+(t2-t1)*D[j] and h'<h
 This contradicts that cutting `i` first gives optimal result.
 Thus cutting grasses in ascendent order of growth gives optimal result.
 
 3. DP
 
 Brute-forcing cutting grass costs O(2^N) which is too large.
 We can compute min height for d-th day by DP as blow:
 
 // we don't cut `i` at d-th day
 dp[i+1][d] = min(_, dp[i][d])
 // we cut `i` at d-th day
 dp[i+1][d+1] = min(_, dp[i][d]+∑{D[i]}-(d+1)*D[i]-I[i])
 
 res = min { d : dp[N][d]<=H }
 
 Another approach is computing maximum amount of cut by similar DP.
 Total length without any cut at d-th day is trivial to compute.
 We can subtract max cut from it.
 
 We are computing min value with limited cost. This is kind of knapsack problem.
 
 Key:
  - Three creative steps to solve
   - Cutting same one twice does not better choice => res is upper-bounded by N ✅
   - Cutting in ascendent order of grouth is optimal ✅
   - Problem is reduced to knapsack problem DP ❌
 
 Summary:
  - If value range is small, brute-force is the primary option 👎
  - Fixing one of conditions is always helpful to go into deep analysis 👎👎
  - Deeper and deepr analysis is needed
    - Greedy analysis of two properties + dp
    - I figured out the properties and tried DP though, no luck to find cucurrence relation 👎👎👎👎
 
 */

int dp[55][55];
class CuttingGrass {
  public:
  int H;
  bool ok(VI &X) {
    return accumulate(X.begin(),X.end(),0)<=H;
  }
  int theMin(vector<int> I, vector<int> D, int H) {
    this->H=H;
    vector<II> A;
    int N=SZ(I);
    if(ok(I)) return 0;
    REP(i,N) A.emplace_back(D[i],I[i]);
    sort(A.begin(),A.end());

    const int Inf=1e7;
    REPE(i,N)REPE(j,N) dp[i][j]=Inf;
    int det=accumulate(D.begin(),D.end(),0);
    dp[0][0]=accumulate(I.begin(),I.end(),0);
    REP(i,N) REPE(d,N) {
      SMIN(dp[i+1][d],dp[i][d]);
      SMIN(dp[i+1][d+1],dp[i][d]+det-(d+1)*A[i].first-A[i].second);
    }
    
    REPE(d,N) if(dp[N][d]<=H) return d;
    return -1;
    /*
     // incorrect greedy doesn't work
     const int Inf=100;
     int res=Inf;
    REPE(s,N) {
      VI X(N);
      REP(i,N) X[i]=A[i].second;
      for(int t=0; t<N&&s+t<N; ++t) {
        REP(i,N) X[i]+=A[i].first;
        X[s+t]=0;
//        dump2(s,t);
//        dumpAR(X);
        if(ok(X)) {
          dump(t+1);
          SMIN(res,t+1);
          break;
        }
      }
    }
    
    return res>N?-1:res;*/
  }
};

// CUT begin
ifstream data("CuttingGrass.sample");

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

bool do_test(vector<int> init, vector<int> grow, int H, int __expected) {
    time_t startClock = clock();
    CuttingGrass *instance = new CuttingGrass();
    int __result = instance->theMin(init, grow, H);
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
        vector<int> init;
        from_stream(init);
        vector<int> grow;
        from_stream(grow);
        int H;
        from_stream(H);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(init, grow, H, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520293412;
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
        cout << "CuttingGrass (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
