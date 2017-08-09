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

/**
 
 8/7/2017
 
 14:25-15:48 give up
 
 23:40-24:50 read editorial
 - Keep events ONLY when direction changed
  - http://kmjp.hatenablog.jp/entry/2015/12/19/1030
   es = [(time of cur change, time of previous change+1)]
   i)  x (time of last action) < e.prev_t (< e.cur_t)
    => ++res, x = e.cur
   ii) e.prev_t <= x (time of last action) (< e.cur_t)
    => do nothing (cur change is processed in the last action)
 
 - Keep all the events:
  - https://apps.topcoder.com/wiki/display/tc/SRM+676
   es = [(time, direction, node)]
   i)  last_time(p) < x (time of last action) < e.t (time of current event)
    => event is free because current event is aleady processed in last action
       last_time(p) = e.t, dir(p) = e.d
   ii) x < last_time(p) < e.t
    ii-1) dir(p) != e.d (direction of current event)
      => ++action, x = e.t, dir(p) = e.d, last_time(p) = e.t
   ii-2) dir(p) == e.d
      => keep same direction. last_time(p) = e.t
 
 24:50-25:21 add solution
 
 Key:
 - Indexing of internal nodes
  - Indexing of binary heap by array or segment tree
    - root: 0, left child of i: 2*i+1, right child of i: 2*i+2
    - access each internal nodes by keeping left and right
 - sweep line of passing events.
 
 Summary:
  - My guess that necessary states to remember are below two was right
    - last time of node switch
    - current switch direction left/right
  - Completely in stuck due to node indexing 👎
 
 */

int SS[1<<18];
int TS[1<<18];
class RailroadSwitchOperator {
  public:
  int minEnergy(int N, vector<int> X, vector<int> T) {
    MINUS(TS);
    ZERO(SS);

    vector<II> es;
    
    REP(i,SZ(X)) {
      --X[i];
      int p2=0;
      int l=0, r=N;
      int t = T[i];
      while(l+1<r) {
         int mid=(l+r)/2;
         bool dir = X[i]>=mid;
         if (SS[p2]!=dir) es.emplace_back(t,TS[p2]+1);
         SS[p2]=dir;
         TS[p2]=t++;
         if (!dir) p2=2*p2+1, r=mid;
         else p2=2*p2+2, l=mid;
      }
    }
  
    sort(es.begin(),es.end());
    
    int res=0;
    int last=-1;
    FORR(e,es) if(e.second>last) ++res, last=e.first;
    return res;
  }
};

// CUT begin
ifstream data("RailroadSwitchOperator.sample");

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

bool do_test(int N, vector<int> x, vector<int> t, int __expected) {
    time_t startClock = clock();
    RailroadSwitchOperator *instance = new RailroadSwitchOperator();
    int __result = instance->minEnergy(N, x, t);
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
        int N;
        from_stream(N);
        vector<int> x;
        from_stream(x);
        vector<int> t;
        from_stream(t);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, x, t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502141118;
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
        cout << "RailroadSwitchOperator (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
