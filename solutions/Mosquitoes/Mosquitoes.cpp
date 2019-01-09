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
 
 2/21/2018
 
 10:09-10:50 analysis
 10:51-11:01 implement and submit. However 1WA
 11:02-11:21 resubmit and ACC
 
 # My solution
 
 There are two parameters to search. time `t` and position `x` to put a bomb.
 If t is pinned, position of mosquitoes are determined in O(N).
 Also we can count maximum number of mosquitoes to be killed in O(N*lg N) by sorting and two pointers.
 The largest `t` when two mosquitoes meet is at most 200.
 x0=-100, v0=2, x1=100, v1=1
 => -100+2*t=100+t => t=200
 
 So we can iterate t from 0 to 200. However t may not be integer.
 What I used to avoid computation of real number is "coordinate expansion".
 Denominator of fraction is in [1,200].
 I expanded x by them and found maximal value.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+528
  - http://kmjp.hatenablog.jp/entry/2014/01/09/0930
  - https://topcoder.g.hatena.ne.jp/firewood/20111231/1325330436
  - http://sucrose.hatenablog.com/entry/20111229/p1
  - http://d.hatena.ne.jp/rintpsy/20111229/1325191076
 
 Official editorial of this problem is kind of fun.
 It contains two of lemmas, which are highly suggestive to me.
 
 # Lemma 1. One of time when two mosquitoes meet is optimal

 This lemma captures a snapshot when two mosquitoes intersect.
 
 Note that we should pin one edge to one mosquito to maximize chance to capture mosquitoes.
 Having loose space at left (or right) is waste of limited 2*R interval.

 t=t0     : 6 mosquitoes (Timing in lemma 1)
 |<----- 2R ------>|
 |L  @ R    L   R  |
     ^ intersect

 Two mosquitoes go further after intersection.
 If optimal solution includes those two mosquitoes, this is the best time to capture other mosquitoes as well.
 Algorithm brute-forces pairs of mosquitoes s.t. they are part of an optimal solution.
 
 # Lemma 2. One of time when two mosquitoes are both on the edge of an interval is optimal
 
 This lemma captures a snapshot when two mosquitoes are on the edge of intervals.
 
 t=t1(>t0): still 6 mosquitoes (Timing in lemma 2)
 |L  L R R  L     R|

 If optimal solution exists, there should be an interval of time p<=t<=q which keeps maximal number of mosquitoes `M`.
 If t<p or t>q, at least one of mosquitoes is going out of the 2*R interval
 
 f(t) = M-1 if t<p
        M   if p<=t<=q
        M-1 if t>q
 
 If optimal solution with M>=2 exists for differnt velocity, such `p` or `q` should exist.
 We can brute-force `t` s.t. two mosquitoes are on the boundary of optimal solution.
 
 # High level summary of lemmas
 
 Exact time to be captured by Lemma1 and Lemma2 may be different but should be very close.
 Thus both capture same number of mosquitoes.
 Also both lemmas are showing that one of necessary conditions is sufficient.
 Lemma 1 approach is kind of extension of special case. Brute-forcing potential necessary conditions.
 Lemma 2 is moving backward from optimal final state. Time interval keeps invariant of optimal state.
 Lemma is searching such boundary condition.
 
 Key:
  - How to upperbound search space of time is the key
 
 Summary:
  - Idea of coordinate expansion was good. However 1WA in case that mosquitoes meet at t=147/189
  - Formula conversion to form with only multiplication (instead of division) in official editorial is nice technique
 
 */

// O(200*40000*N*lg N) time
class Mosquitoes {
  public:
  int R,N;
  VI X,V;
  int f(int t) {
    VI Y(N);
    REP(i,N) Y[i]=X[i]+t*V[i];
    
    sort(Y.begin(),Y.end());
    int res=0;
    
    /*
    REP(i,N) {
      int cnt=1;
      FOR(j,i+1,N) {
        if(Y[j]-Y[i]<=2*R) ++cnt;
        else break;
      }
      res=max(res,cnt);
    }*/
    
    int l=0;
    REP(r,N) {
      while(l<r&&Y[r]-Y[l]>2*R) ++l;
      res=max(res,r-l+1);
    }
    
    return res;
  }
  int getMaximum(vector<int> _X, vector<int> V, int _R) {
    this->N=SZ(_X);
    this->V=V;
    
    int res=0;
    FORE(r,1,200) {
      int t=0;
      X.clear();
      REP(i,N) X.push_back(_X[i]*r);
      this->R=_R*r;
      while(t<4001) res=max(res,f(t++));
    }
    
    return res;
  }
};

// CUT begin
ifstream data("Mosquitoes.sample");

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

bool do_test(vector<int> xInit, vector<int> v, int R, int __expected) {
    time_t startClock = clock();
    Mosquitoes *instance = new Mosquitoes();
    int __result = instance->getMaximum(xInit, v, R);
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
        vector<int> xInit;
        from_stream(xInit);
        vector<int> v;
        from_stream(v);
        int R;
        from_stream(R);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(xInit, v, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519236574;
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
        cout << "Mosquitoes (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
