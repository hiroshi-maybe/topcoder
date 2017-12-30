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
 
 12/29/2017
 
 12:49-13:38 analysis
 13:39-14:00 time up and take a look at editorial
 15:28-15:55 kee up my original approach and system test passed
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+561
  - http://kmjp.hatenablog.jp/entry/2012/11/23/0900
  - http://torus711.hatenablog.com/entry/20121120/p1
 
 There are only two sizes. It's impossible to assign different sizes to one problem.
 It's possible to brute-force size assignemnts to each problem in 2^14.
 Once they are assigned, it seems to be hard to do DP in 50*5000 time (TLE).
 We need to find greedy assignment of baloon colors.
 (Since I couldn't solve this subproblem greedily, I could not solve by myself)
 
 Cost of color assignment is free ONLY when free color is assigned.
 So we want to assign one color to one problem. This is strong constraint.
 Suppose we have colors Q and problems R.
 Ideal situation is..
 
 ∀i, Q[i]>=R[i]
 
 In this case cost is `0` because we don't need to re-paint any baloons.
 Assigning color whose number is few to a problem of more solvers causes more costs to repaint.
 Thus assignment of color of more baloons to more solvers gives less chance to repaint.
 We can sort baloons and problems in descendnet order and map one by one.
 If number of corresponding color is not enough, we can repaint and reuse from extra baloons.
 
 Key:
  - Number of problems is small (N=14). We can brute-force size assignment in 2^14
  - Cost is 0 ONLY when free color is available
 
 Summary:
  - I had an idea of 2^14 approach though, I could not analyze subproblem correctly
  - Subproblem to compute minimum cost to assign X baloons to Y problems was key
  - My understanding of baloon assignment was not enough
   - Zero cost assignment is possible ONLY when free color is available
   - Otherwise we need to pay to reuse them to other problems
   - We want to map one color to one problem as many as possible
  - Also I should analyze by focusing on what case is optimal
 
 Submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=314849&rd=15183&pm=12314&cr=22897691
    - clean implementation by subtracting min(Q[i],R[i])
 
 */
class ICPCBalloons {
  public:
  const int Inf=5001;
  int f(VI Q, VI R) {
    int rem=0;
    
    while(SZ(Q)<SZ(R)) Q.push_back(0);
    while(SZ(Q)>SZ(R)) rem+=Q.back(), Q.pop_back();

    assert(SZ(Q)==SZ(R));
    
    int debt=0;
    REP(i,SZ(R)) {
      if(R[i]>Q[i]) {
        debt+=R[i]-Q[i];
        continue;
      }
      if(R[i]<Q[i]) {
        rem+=Q[i]-R[i];
      }
    }

    return debt>rem?Inf:debt;
  }
  
  int minRepaintings(vector<int> B, string S, vector<int> A) {
    VI Q[2];
    REP(i,SZ(B)) {
      Q[S[i]=='M'].emplace_back(B[i]);
    }
    REP(i,2) sort(Q[i].rbegin(),Q[i].rend());

    int res=Inf;
    int N=SZ(A);
    REP(mask,1<<N) {
      VI R[2];
      REP(i,N) R[(mask&(1<<i))!=0].emplace_back(A[i]);
      REP(i,2) sort(R[i].rbegin(),R[i].rend());
      
//      if(mask==((1<<3)+(1<<4)+(1<<5))) dump4(SZ(R[0]),SZ(Q[0]),SZ(R[1]),SZ(Q[1]));
      
      int l=f(Q[0],R[0]);
      int m=f(Q[1],R[1]);
      
//      if(mask==(1<<3)+(1<<4)+(1<<5)) dump3(mask,l,m);
      
      res=min(res,l+m);
    }
    
    return res==Inf?-1:res;
  }
};

// CUT begin
ifstream data("ICPCBalloons.sample");

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

bool do_test(vector<int> balloonCount, string balloonSize, vector<int> maxAccepted, int __expected) {
    time_t startClock = clock();
    ICPCBalloons *instance = new ICPCBalloons();
    int __result = instance->minRepaintings(balloonCount, balloonSize, maxAccepted);
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
        vector<int> balloonCount;
        from_stream(balloonCount);
        string balloonSize;
        from_stream(balloonSize);
        vector<int> maxAccepted;
        from_stream(maxAccepted);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(balloonCount, balloonSize, maxAccepted, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514580545;
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
        cout << "ICPCBalloons (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
