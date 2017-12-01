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
 
 11/20/2017
 
 8:34-8:54 analysis
 8:54-9:06 system test passed (272.66 pt)
 
 # Solution 1
 
 Range of possible fatigue is [1,100*100].
 Suppose we have fatigue x. Then it's possible to figure out if it's possible or not in O(N) time.
 So it's possible to find minimum x in 10000*N step
 Or it's even possible to compute by bynary search in O(N*lg 10000) time, which solves div1 easy.
 
 # Solution 2

 Enemy is at most 10000. Let's process enemies in descendent order of its strength.
 We can greedily pick up a girl k = { j : Fatigue[j] is minimum AND j ∈ { i : enemy<=A[i] } }
 Enemy's strength is getting lower. Choosing stronger girl whose fatigue is smallest is best choice.
 
 Informal proof:
 
 Sort girls with its descendent order first. Suppose we are processing enemy whose strength is `e`.
 If enemy can be defeated, we'll find `k` = max { i : A[i]>= e }
 Then we can choose a girl in range [0,k].
 Since strength of next enemy <=`e`, it does not make sense to save strong girl for future choice.
 Thus simply picking up a girl whose fatigue is minimum is the best choice.
 
 Editorial:
  - O(N*∑B[i]*C[i]) time greedy solution
    - http://torus711.hatenablog.com/entry/20130615/p1
    - http://emkcsharp.hatenablog.com/entry/SRM582/SpaceWarDiv2
 
 Summary:
  - Analysis is still slow though, reached algorithm was sufficient enough to solve div1 easy 👍
  - Greedy solution is neat too!
 
 Submit solutions:
  - Binary search
    - https://community.topcoder.com/stat?c=problem_solution&rm=317724&rd=15502&pm=12605&cr=22879157
 
 */

class SpaceWarDiv2 {
public:
  int minimalFatigue(vector<int> A, vector<int> B, vector<int> C) {
    int N=SZ(A);
    sort(A.rbegin(),A.rend());
    VI es;
    REP(i,SZ(B)) REP(_,C[i]) es.emplace_back(B[i]);
    sort(es.rbegin(),es.rend());
    VI F(N,0);
    FORR(e, es) {
      int k=-1;
      REP(i,N) if(A[i]>=e) {
        if(k==-1||F[i]<F[k]) k=i;
      }
      if(k==-1) return -1;
      ++F[k];
    }
    return *max_element(F.begin(),F.end());
  }
};

class SpaceWarDiv2_org {
  public:
  VI A,B,CC;
  bool ok(int cnt) {
    VI C=CC;
    int N=SZ(A),M=SZ(B);
    int j=0;
    REP(i,N) {
      int x=cnt;
      while(x>0&&j<M&&A[i]>=B[j]) {
        int d=min(C[j],x);
        x-=d;
        C[j]-=d;
        if(C[j]==0) ++j;
      }
    }
    return j==M;
  }
  
  int minimalFatigue(vector<int> A, vector<int> B, vector<int> C) {
    sort(A.begin(),A.end());
    vector<II> xs; REP(i,SZ(B)) xs.emplace_back(B[i],C[i]);
    sort(xs.begin(),xs.end());
    this->A=A;
    REP(i,SZ(B)) this->B.emplace_back(xs[i].first);
    REP(i,SZ(B)) this->CC.emplace_back(xs[i].second);
    for(int x=1; x<=10000; ++x) if(ok(x)) return x;
    return -1;
  }
};

// CUT begin
ifstream data("SpaceWarDiv2.sample");

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

bool do_test(vector<int> magicalGirlStrength, vector<int> enemyStrength, vector<int> enemyCount, int __expected) {
    time_t startClock = clock();
    SpaceWarDiv2 *instance = new SpaceWarDiv2();
    int __result = instance->minimalFatigue(magicalGirlStrength, enemyStrength, enemyCount);
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
        vector<int> magicalGirlStrength;
        from_stream(magicalGirlStrength);
        vector<int> enemyStrength;
        from_stream(enemyStrength);
        vector<int> enemyCount;
        from_stream(enemyCount);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(magicalGirlStrength, enemyStrength, enemyCount, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1511195638;
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
        cout << "SpaceWarDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
