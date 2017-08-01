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
typedef pair<int,int> II;

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
 
 7/31/2017
 
 8:39-9:14 failed system test (261.46 pt)
 17:55-18:05 retry and passed system test
 
 23:40-24:07 read editorials
 - https://apps.topcoder.com/wiki/display/tc/SRM+683
 
 24:08-24:16 add simpler and more efficient solution inspired by editorial
  - same solution
    - https://community.topcoder.com/stat?c=problem_solution&rm=328151&rd=16653&pm=14182&cr=23328790
 
 Key
 - moving from left or from right doesn't matter. that means we can modify b[i] keeping problem condition.
 - if we can modify b[i], we can assume that a[0..i-1] and b[0..i-1] always equal by managing moving debt.
 - cost happens every time debt is moving
  - we can calculate cost and current balance at the same time
 
 Summary
 - figured out a greedy solution though, couldn't fix bug due to complex queue manipulation
 - cost calculation for every move vs delay it until the debt is paid
 - it was easier if I found out that cost always happens for moving debt
 - don't be in rush. complex solution sometimes shoots my own foot.
 - actually found simpler solution than editorial
  - moved debt can be applied to a[i], which simulates moved stones stay at a[i].
 
 */

// O(N) time, simpler than official editorial :)
class MoveStonesEasy {
public:
  int get(vector<int> a, vector<int> b) {
    int N=SZ(a), res=0, bal=0;
    REP(i,N) {
      res += abs(bal);
      a[i]+=bal;
      bal = a[i]-b[i];
    }
    
    return bal!=0 ? -1 : res;
  }
};

// O(N^2) time
class MoveStonesEasy_org {
public:
  int get(vector<int> a, vector<int> b) {
    int N=SZ(a), res=0;
    REP(i,N) {
      if(a[i]==b[i]) continue;
      int j=i+1;
      if(a[i]<b[i]) {
        while(j<N&&a[i]!=b[i]) {
          if(a[j]<=b[j]) { ++j; continue; }
          int del = min(abs(a[i]-b[i]), abs(a[j]-b[j]));
          a[i]+=del; a[j]-=del;
          res += (j-i)*del;
          ++j;
        }
        if(j==N&&a[i]!=b[i]) return -1;
      } else {
        while(j<N&&a[i]!=b[i]) {
          if(a[j]>=b[j]) { ++j; continue; }
          int del = min(abs(a[i]-b[i]), abs(a[j]-b[j]));
          a[i]-=del; a[j]+=del;
          res += (j-i)*del;
          ++j;
        }
        if(j==N&&a[i]!=b[i]) return -1;
      }
    }
    
    return res;
  }
};

class MoveStonesEasy_wrong {
  public:
  int get(vector<int> a, vector<int> b) {
    int N=SZ(a), res=0;
    
    queue<II> Q;
    REP(i,N) {
      int bal = a[i]-b[i];
      while(bal!=0) {
        if(Q.empty()) {
          Q.emplace(i, bal);
          break;
        }
        auto& p = Q.front();
        assert(p.second!=0);
        if(p.second*bal>0) {
          Q.emplace(i,bal);
          break;
        }
        
        int del = min(abs(bal), abs(p.second));
        res += (i-p.first)*del;
        if(p.second>0) del=-del;
        
        p.second += del; bal -= del;
        
        dump3(i,p.second, bal);
        if(p.second==0) Q.pop();
      }
    }

    dump(res);
    res= SZ(Q)==0 ? res : -1;
    
    while(SZ(Q)) {
      auto p=Q.front(); Q.pop();
      dump2(p.first, p.second);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("MoveStonesEasy.sample");

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

bool do_test(vector<int> a, vector<int> b, int __expected) {
    time_t startClock = clock();
    MoveStonesEasy *instance = new MoveStonesEasy();
    int __result = instance->get(a, b);
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501515583;
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
        cout << "MoveStonesEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
