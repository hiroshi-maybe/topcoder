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
 
 2/28/2018
 
 22:17-22:23 analysis
 22:30 (409.47 pt)
 
 3/1/2018
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+520
  - greedy
   - http://d.hatena.ne.jp/kusano_prog/20111004/1317752837
   - http://topcoder.g.hatena.ne.jp/blu_ray/20111006/1317887939
   - https://chngng.blogspot.jp/2013/10/srm-520-div1-easy-srmcodingphase.html
   - http://hos0lyric.blog89.fc2.com/blog-entry-46.html
  - brute-force
   - http://tubo28.me/blog/post/2015/08/08/srm520-d1e/
   - http://purple-jwl.hatenablog.com/entry/20121103/1351928350
   - http://mayokoex.hatenablog.com/entry/2015/08/07/221823
 
 My solution used next_permutation to simulate all the possible orders.
 Suppose T[0]>75 and T[1]<=75. In this case, solving in order 1,0 is optimal.
 
 However order doesn't matter in terms of sum of time because time to solve each problem is independent.
 We can iterate subset of problems to be solved in 2^3 cases rather than 3! cases.
 
 This analysis is ignoring how to assign luck.
 Suppose all the problems can be solved within 75 mins without luck.
 In this extreme case, assigning more luck to harder problem gives more point.
 cost without luck: ∑T[i]
 cost with luck: 2*(T[0]-z)+4*(T[1]-y)+8*(T[2]-x) = ∑T[i]-(2*x+4*y+8*z) (z>=y>=x)
 Also constraint of T[i]-x>0 does not affect this strategy.
 
 This is just necessary condition so far because we are assuming a special case that all the problems are solvable within 75 mins.
 Suppose consuming all the luck to T[2] does not fit in 75 mins.
 In this case, obviously we should not assign any luck to T[2].
 Optimal cost should be T[0]-2*x+T[1]-4*y < T[0]+T[1] (y>=x)
 This case can be actually covered if we iterate all the subsets of solving problem.
 If some of problems does not fit even if assigning maximal luck, this is same as the case that we don' solve it.
 So iterating all the subsets cover those unhappy cases.
 Thus we can prove that strategy to assign more luck to harder problem is sufficient.
 We can solve with greedy algorithm.
 
 10:49-11:58 add greedy solution
 
 Summary:
  - Nice to figure out brute-force quickly 👍
  - I haven't found greedy solution. It's nice stuff to learn greedy process
   - Strategy works in extreme special case
   - Show the necessary condition is actually sufficient
 
 */

class SRMCodingPhase {
public:
  int countScore(vector<int> P, vector<int> T, int L) {
    int C[3]={2,4,8};
    int res=0;
    REP(mask,1<<3) {
      int sumt=0,x=0,LL=L;
      for(int i=2; i>=0; --i) if((mask>>i)&1) {
        int t=max(1,T[i]-LL);
        x+=P[i]-C[i]*t;
        sumt+=t;
        LL-=T[i]-t;
      }
      if(sumt>75) continue;
      SMAX(res,x);
    }
    return res;
  }
};

// O(3!*L^3*3) time
class SRMCodingPhase_org {
  public:
  int countScore(vector<int> P, vector<int> T, int L) {
    VI perm(3,0);
    REP(i,3) perm[i]=i;
    int C[3]={2,4,8};
    int res=0;
    do {
      REPE(a,L)REPE(b,L) if(a+b<=L){
        int c=L-a-b;
        int LL[3]={};
        LL[0]=a,LL[1]=b,LL[2]=c;
        int x=0,tsum=0;
        REP(i,3) {
          int t=max(1,T[perm[i]]-LL[i]);
          if(tsum+t>75) break;
          x+=P[perm[i]]-C[perm[i]]*t;
          tsum+=t;
        }
        SMAX(res,x);
      }
      
    } while(next_permutation(perm.begin(),perm.end()));
    return res;
  }
};

// CUT begin
ifstream data("SRMCodingPhase.sample");

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

bool do_test(vector<int> points, vector<int> skills, int luck, int __expected) {
    time_t startClock = clock();
    SRMCodingPhase *instance = new SRMCodingPhase();
    int __result = instance->countScore(points, skills, luck);
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
        vector<int> points;
        from_stream(points);
        vector<int> skills;
        from_stream(skills);
        int luck;
        from_stream(luck);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(points, skills, luck, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519885009;
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
        cout << "SRMCodingPhase (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
